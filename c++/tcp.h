#ifndef __TCP_H__
#define __TCP_H__

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MODULE_TCP_MAX_BUFFER_SIZE 1024 //加入类名以免在引用时重定义

using namespace std;

class ModuleTcp
{
public:
	ModuleTcp(int _port);  //构造server
	ModuleTcp(int _port, string _server_ip);  //构造client
	~ModuleTcp();
	
	/* 客户端接口 */
	int connectToServer();
	int reInitTcp();
	
	/* 服务器接口 */
	int waitConnect();
	void waitConnectAndThread();
	
	/* 通用接口 */
	int sendTo(char* buff, int size, int flag = MSG_DONTWAIT);
	int readFrom(char* buff, unsigned int size = MODULE_TCP_MAX_BUFFER_SIZE, int flag = MSG_DONTWAIT);
	int setKeepAlive(int idle, int cnt, int intv);
	int tcp_is_connected();
	
	int readSockfd()
	{
		return this->sock_fd;
	}

protected: 
	int sock_fd;
	int port;
	string server_ip;
	int wr_fd;

private: //只有private中的成员不能被继承的子类访问
	char sendBuff[MODULE_TCP_MAX_BUFFER_SIZE];
	char readBuff[MODULE_TCP_MAX_BUFFER_SIZE];
	
	struct sockaddr_in server_addr, client_addr;
};

#endif
