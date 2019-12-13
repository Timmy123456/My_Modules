#include <iostream>
#include <string.h>
#include "c++/tcp.h"

using namespace std;

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
			continue;
		}
		client.sendTo("hello", 6);
		cout << "hello" << endl;
		char buf[1024] = "";
		client.readFrom((char*)buf);
		printf("%s\n", buf);
		client.sendTo(buf, strlen(buf));
		usleep(100000);
	}
	return 0;
}