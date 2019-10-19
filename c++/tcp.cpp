#include <iostream>
#include <string.h>
#include "tcp.h"

//=======================================================================================
/* 客户端部分代码 */
ModuleTcp::ModuleTcp(int _port, string _server_ip)
{
	cout << "Start TCP Client" << endl;
	port = _port;
	server_ip = _server_ip;
	///定义sockfd
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
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

void ModuleTcp::connectToServer()
{
	cout << "Connecting port:" << port << " ip:" << server_ip << endl;
	//连接服务器，成功返回0，错误返回-1
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    cout << "Connect to server success!" << endl;
	wr_fd = sock_fd;
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
        exit(1);
    }
}

int ModuleTcp::waitConnect()
{   
    cout << "listen port:" << port << endl;
    //listen，成功返回0，出错返回-1
    if(listen(sock_fd, 20) == -1)
    {
        perror("listen");
        exit(1);
    }

	//客户端套接字
    socklen_t length = sizeof(client_addr);
    
    printf("Waiting for client........\n");
    //成功返回非负描述字，出错返回-1
    int conn = accept(sock_fd, (struct sockaddr*)&client_addr, &length);
    if(conn<0)
    {
        perror("connect");
        exit(1);
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
		exit(0);
	}
}

ModuleTcp::~ModuleTcp()
{
	close(wr_fd);
	close(sock_fd);
}