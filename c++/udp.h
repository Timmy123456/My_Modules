#ifndef __UDP_H__
#define __UDP_H__

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

#define MODULE_UDP_MAX_BUFFER_SIZE 1024 //加入类名以免在引用时重定义

using namespace std;

typedef struct
{
	struct sockaddr_in peeraddr;
	socklen_t peerlen;
} UdpAddr;

class ModuleUdp
{
public:
	ModuleUdp(int _port); //创建服务器
	ModuleUdp(string _target_ip, int _port); //创建客户端
	~ModuleUdp();
	
	int getSockfd()
	{
		return this->sock_fd;
	}
	
	/* 通用接口 */
	UdpAddr addr_arg;
	int sendTo(char* buff, int size, int flag = 0);
	int readFrom(char* buff, unsigned int size = MODULE_UDP_MAX_BUFFER_SIZE, int flag = 0);
	
	void setDestination(const char *_ip, unsigned int _port)
	{
		this->addr_arg.peeraddr.sin_family = AF_INET;
		this->addr_arg.peeraddr.sin_port = htons(_port);
		this->addr_arg.peeraddr.sin_addr.s_addr = inet_addr(_ip);
		this->addr_arg.peerlen = sizeof(struct sockaddr_in);
	}
	
	void getSource(char *_ip, unsigned int *_port)
	{
		memcpy(_ip, inet_ntoa(this->addr_arg.peeraddr.sin_addr), 17);
		*_port = ntohs(this->addr_arg.peeraddr.sin_port);
	}
	
protected: 
	int sock_fd;
};

#endif