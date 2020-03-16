#include <cstring>
#include "c++/udp.h"

/*
 *  只需要定义监听的端口即可以使用
 *  通过调用类的方法来设定参数
 */

int main(int argc, char** argv)
{
	ModuleUdp reader(8080);
	
	while(1)
	{
		char buff[MODULE_UDP_MAX_BUFFER_SIZE] = "";
		reader.readFrom(buff); //等待接收
		printf("recv:%s\n", buff);
		
		char ip[20];
		unsigned int port;
		reader.getSource(ip, &port); // 获取消息来源的ip和port
		printf("%s:%d\n", ip, port);
		
		reader.setDestination("192.168.137.1", 8080); // 设置发送目标的ip和port
		memcpy(buff, "8080", 4);
		reader.sendTo(buff, 4); //发送
		
	}
	return 0;
}