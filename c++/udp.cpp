#include <iostream>
#include <cstring>
#include "udp.h"

//========================================================================================
/* 服务器部分代码 */
ModuleUdp::ModuleUdp(int _port)
{
	cout << "Start UDP server" << endl;
	//定义sockfd
    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		return;
	}
    
    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
	memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(_port);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //bind，成功返回0，出错返回-1
    if(bind(sock_fd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind");
		return;
    }
	
	// 设置addr_arg的默认值
	addr_arg.peerlen = sizeof(struct sockaddr_in);
}

//========================================================================================
/* 客户端部分代码 */
ModuleUdp::ModuleUdp(string _server_ip, int _port)
{
	cout << "Start UDP client" << endl;
	//定义sockfd
    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (sock_fd < 0)
	{
		perror("socket");
		return;
	}
	
	int on=1;
	setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR | SO_BROADCAST,&on,sizeof(on));
	
	//定义sockaddr_in
    struct sockaddr_in sockaddr;
	memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(_port);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //bind，成功返回0，出错返回-1
    if(bind(sock_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1)
    {
        perror("bind");
		return;
    }
	setDestination(_server_ip.c_str(), _port);
}

ModuleUdp::~ModuleUdp()
{
	close(sock_fd);
}

int ModuleUdp::sendTo(char* buff, int size, int flag)
{
	int ret = -1;
	ret = sendto(sock_fd, buff, size, flag, (struct sockaddr *)&addr_arg.peeraddr, addr_arg.peerlen);
	if (ret == -1)
	{
		perror("sendto");
	}
	return ret;
}

int ModuleUdp::readFrom(char* buff, unsigned int size, int flag)
{
	int ret = -1;
	ret = recvfrom(sock_fd, buff, size, flag, (struct sockaddr *)&addr_arg.peeraddr, &addr_arg.peerlen);
	if (ret == -1)
	{
		perror("recvfrom");
	}
	return ret;
}
