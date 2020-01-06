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
		reader.setDestination("192.168.137.1", 8080);
		memcpy(reader.rw_arg.send_buff, "hello udp", strlen("hello udp"));
		reader.rw_arg.size = strlen("hello udp");
		reader.sendTo();
		
		reader.readFrom();
		printf("recv:%s\n", reader.rw_arg.recv_buff);
	}
	return 0;
}