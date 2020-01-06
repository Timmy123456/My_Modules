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
	
	// 设置rw_arg的默认值
	rw_arg.send_buff = (char *)malloc(MODULE_UDP_MAX_BUFFER_SIZE);
	memset(rw_arg.send_buff, 0, MODULE_UDP_MAX_BUFFER_SIZE);
	rw_arg.recv_buff = (char *)malloc(MODULE_UDP_MAX_BUFFER_SIZE);
	memset(rw_arg.recv_buff, 0, MODULE_UDP_MAX_BUFFER_SIZE);
	rw_arg.size = MODULE_UDP_MAX_BUFFER_SIZE;
	rw_arg.flag = 0;
	rw_arg.peerlen = sizeof(struct sockaddr_in);
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
	
	// 设置rw_arg的默认值
	rw_arg.send_buff = (char *)malloc(MODULE_UDP_MAX_BUFFER_SIZE);
	memset(rw_arg.send_buff, 0, MODULE_UDP_MAX_BUFFER_SIZE);
	rw_arg.recv_buff = (char *)malloc(MODULE_UDP_MAX_BUFFER_SIZE);
	memset(rw_arg.recv_buff, 0, MODULE_UDP_MAX_BUFFER_SIZE);
	rw_arg.size = MODULE_UDP_MAX_BUFFER_SIZE;
	rw_arg.flag = 0;
}

ModuleUdp::~ModuleUdp()
{
	close(sock_fd);
	free(rw_arg.send_buff);
	free(rw_arg.recv_buff);
}

int ModuleUdp::sendTo()
{
	int ret = -1;
	ret = sendto(sock_fd, rw_arg.send_buff, rw_arg.size, rw_arg.flag, (struct sockaddr *)&rw_arg.peeraddr, rw_arg.peerlen);
	if (ret == -1)
	{
		perror("sendto");
	}
	return ret;
}

int ModuleUdp::readFrom()
{
	int ret = -1;
	ret = recvfrom(sock_fd, rw_arg.recv_buff, rw_arg.size, rw_arg.flag, (struct sockaddr *)&rw_arg.peeraddr, &rw_arg.peerlen);
	if (ret == -1)
	{
		perror("recvfrom");
	}
	return ret;
}
