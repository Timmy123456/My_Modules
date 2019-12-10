#include <iostream>
#include <string.h>
#include "tcp.h"

ModuleTcp::ModuleTcp(int _port, string _server_ip)
{
	cout << "Start TCP Client" << endl;
	port = _port;
	server_ip = _server_ip;
	///定义sockfd
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		return;
	}

	//设置端口复用
	int reuse = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) == -1)
	{
		std::cout << "setsockopt " << SO_REUSEADDR << "failed" << std::endl;
		return;
	}
    
    ///定义sockaddr_in
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);  ///服务器端口
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());  ///服务器ip
}

//=======================================================================================
/* 客户端部分代码 */
int ModuleTcp::connectToServer()
{
	cout << "Connecting port:" << port << " ip:" << server_ip << endl;
	//连接服务器，成功返回0，错误返回-1
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        return -1;
    }
    cout << "Connect to server success!" << endl;
	wr_fd = sock_fd;
	return 0;
}

int ModuleTcp::reInitTcp()
{
	cout << "Start TCP Client reconnect" << endl;
	close(sock_fd); //关闭先前的句柄
	///定义sockfd
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		return sock_fd;
	}

	//设置端口复用
	int reuse = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) == -1)
	{
		std::cout << "setsockopt " << SO_REUSEADDR << "failed" << std::endl;
		return -1;
	}
    
    ///定义sockaddr_in
    memset(&(server_addr), 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);  ///服务器端口
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());  ///服务器ip
	return 0;
}

//========================================================================================
/* 服务器部分代码 */
ModuleTcp::ModuleTcp(int _port)
{
	cout << "Start TCP server" << endl;
	port = _port;
	//定义sockfd
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	int reuse = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) == -1)
	{
		std::cout << "setsockopt " << SO_REUSEADDR << "failed" << std::endl;
		return;
	}
    
    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //bind，成功返回0，出错返回-1
    if(bind(sock_fd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind");
        //exit(1);
		return;
    }
}

int ModuleTcp::waitConnect()
{   
    cout << "listen port:" << port << endl;
    //listen，成功返回0，出错返回-1
    if(listen(sock_fd, 20) == -1)
    {
        perror("listen");
        //exit(1);
		return -1;
    }

	//客户端套接字
    socklen_t length = sizeof(client_addr);
    
    printf("Waiting for client........\n");
    //成功返回非负描述字，出错返回-1
    int conn = accept(sock_fd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        //exit(1);
		return -1;
    }
    printf("A client connected\n");	
	wr_fd = conn;
	return conn;
}

void ModuleTcp::waitConnectAndThread()
{}

void ModuleTcp::sendTo(char* buff, int len)
{
	if (send(wr_fd, buff, len, 0) == -1)
	{
		perror("send");
	}
}

void ModuleTcp::readFrom(char* buff)
{
	if (recv(wr_fd, buff, MODULE_TCP_MAX_BUFFER_SIZE, 0) == 0)
	{
		cout << "connect stop" << endl;
		//exit(0);
	}
}

ModuleTcp::~ModuleTcp()
{
	close(wr_fd);
	close(sock_fd);
}

int ModuleTcp::setKeepAlive(int idle, int cnt, int intv)
{  
    int alive;
    /*int flag, idle, cnt, intv;  */
 
    /* Set: use keepalive on fd */  
    alive = 1;  
    if (setsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE, &alive,  sizeof alive) != 0)  
    {  
        perror("Set keepalive fail");  
        return -1;  
    }  
 
    /* idle秒钟无数据，触发保活机制，发送保活包 */  
    /*idle = 10;  */
    if (setsockopt (sock_fd, SOL_TCP, TCP_KEEPIDLE, &idle, sizeof idle) != 0)  
    {  
        perror("Set keepalive idle fail");  
        return -1;  
    }  
 
    /* 如果没有收到回应，则intv秒钟后重发保活包 */  
    /*intv = 5;  */
    if (setsockopt (sock_fd, SOL_TCP, TCP_KEEPINTVL, &intv, sizeof intv) != 0)  
    {  
        perror("Set keepalive intv fail");  
        return -1;  
    }  
 
    /* 连续cnt次没收到保活包，视为连接失效 */  
    /*cnt = 3;  */
    if (setsockopt (sock_fd, SOL_TCP, TCP_KEEPCNT, &cnt, sizeof cnt) != 0)  
    {  
        perror("Set keepalive cnt fail");  
        return -1;  
    }  
 
    return 0;  
}

int ModuleTcp::tcp_is_connected()
{
    struct tcp_info info;
    int len = sizeof(info);
 
    if (sock_fd <= 0) return 0;
 
    getsockopt(sock_fd, IPPROTO_TCP, TCP_INFO, &info, (socklen_t *)&len);
    /*if (info.tcpi_state == TCP_ESTABLISHED) */
    if (info.tcpi_state == 1)  // Is connected
        return 1;
    else  // Losed
        return 0;
}