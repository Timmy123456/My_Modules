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
	char* send_buff;
	char* recv_buff;
	int size;
	int flag;
	struct sockaddr_in peeraddr;
	socklen_t peerlen;
} UdpRWArg;

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
	UdpRWArg rw_arg;
	int sendTo();
	int readFrom();
	
	void setSendBuffer(char * buff, unsigned int size)
	{
		this->rw_arg.send_buff = buff;
		this->rw_arg.size = size;
	}
	
	char *getSendBuffer()
	{
		return this->rw_arg.send_buff;
	}
	
	void setRecvBuffer(char * buff, unsigned int size)
	{
		this->rw_arg.recv_buff = buff;
		this->rw_arg.size = size;
	}
	
	char *getRecvBuffer()
	{
		return this->rw_arg.recv_buff;
	}
	
	void setBufferSize(unsigned int size)
	{
		this->rw_arg.size = size;
	}
	
	void setFlag(int flag)
	{
		this->rw_arg.flag = flag;
	}
	
	void setDestination(const char *_ip, unsigned int _port)
	{
		this->rw_arg.peeraddr.sin_family = AF_INET;
		this->rw_arg.peeraddr.sin_port = htons(_port);
		this->rw_arg.peeraddr.sin_addr.s_addr = inet_addr(_ip);
		this->rw_arg.peerlen = sizeof(struct sockaddr_in);
	}
	
	void getSource(char *_ip, unsigned int *_port)
	{
		memcpy(_ip, inet_ntoa(this->rw_arg.peeraddr.sin_addr), 17);
		*_port = ntohs(this->rw_arg.peeraddr.sin_port);
	}
	
protected: 
	int sock_fd;
};

#endif