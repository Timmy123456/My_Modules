#include <string.h>
#include "c++/tcp.h"

int main(int argc, char** argv)
{
	ModuleTcp client(4001, "192.168.137.1");
	client.connectToServer();
	while(1)
	{
		if (!client.tcp_is_connected()) //检测是否断开
		{
			printf("TCP disconnect!\n");
			sleep(3);
			client.reInitTcp();
			client.connectToServer();
		}
		char buf[1024] = "";
		client.readFrom((char*)buf);
		printf("%s\n", buf);
		usleep(100000);
	}
	return 0;
}