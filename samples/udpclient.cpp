#include <iostream>
#include <cstring>
#include "c++/udp.h"

/*
 *  初始化时定义监听的端口和发送的ip和port
 *  通过直接给结构体赋值来给参数赋值
 */

int main(int argc, char** argv)
{
	ModuleUdp reader("192.168.137.1", 8080);
	
	while(1)
	{
		reader.sendTo("hello udp", strlen("hello udp"));
		
		char buff[MODULE_UDP_MAX_BUFFER_SIZE] = "";
		reader.readFrom(buff);
		printf("recv:%s\n", buff);
	}
	return 0;
}