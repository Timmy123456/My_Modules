#include <string.h>
#include "c++/tcp.h"

int main(int argc, char** argv)
{
	ModuleTcp client(8080, "192.168.3.217");
	client.connectToServer();
	
	while(1)
	{
		char buf[1024] = "";
		client.readFrom((char*)buf);
		printf("%s\n", buf);
		usleep(100000);
	}
	return 0;
}