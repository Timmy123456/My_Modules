#include <string.h>
#include "tcp.h"

int main(int argc, char** argv)
{
	ModuleTcp server(8080);
	server.waitConnect();
	
	while(1)
	{
		char buf[1024] = "";
		server.readFrom((char*)buf);
		printf("%s\n");
		usleep(100000);
	}
	return 0;
}