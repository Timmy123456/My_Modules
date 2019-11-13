#include "wiring_serial.h"

WiringSerial::WiringSerial(char *dev, int baudrate)
{
	serial_fd = serialOpen(dev, baudrate);
	
	if (serial_fd == -1)
	{
		printf("Fail to open %s, error:%s.\n", dev, strerror(errno));
		exit(0);
	}
	
	if (wiringPiSetup() == -1)
	{
		printf("Unable to start wiringPi: %s\n", strerror(errno));
		exit(0);
	}
	
	printf("Open device %s\n", dev);
}

WiringSerial::~WiringSerial()
{
	serialClose(serial_fd);
}

int WiringSerial::sendTo(char* buff, int len)
{
	unsigned int i = 0;
	do
	{
		serialPutchar(serial_fd, buff[i++]);
	} while (i < len);
	
	return i;
}

int WiringSerial::readFrom(char* buff, int len)
{
	unsigned int i = 0;
	memset(buff, 0, len);
	do
	{
		int tmp = serialGetchar(serial_fd);
		if (tmp == -1)
		{
			continue;
		}
		buff[i++] = tmp;
	} while (serialDataAvail(serial_fd) > 0);
	return i;
}
