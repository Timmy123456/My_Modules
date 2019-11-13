#include "c++/wiring_serial.h"

int main(int argc, char** argv)
{
	WiringSerial serial((char*)"/dev/ttyUSB0", 115200);
	
	char buff[10] = "";
	serial.readFrom(buff, 10);
	serial.sendTo(buff, 10);
	return 0;
}