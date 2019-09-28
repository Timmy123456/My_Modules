#ifndef __TCP_H__
#define __TCP_H__

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
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
	void connectToServer();
	
	/* 服务器接口 */
	void waitConnect();
	void waitConnectAndThread();
	
	/* 通用接口 */
	int sendTo(char* buff, int len);
	int readFrom(char* buff);

private:
	int sock_fd;
	int port;
	string server_ip;
	int wr_fd;
	
	struct sockaddr_in servaddr;
	
	char sendBuff[MODULE_TCP_MAX_BUFFER_SIZE];
	char readBuff[MODULE_TCP_MAX_BUFFER_SIZE];
};

#endif
