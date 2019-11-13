#ifndef __WIRING_SERIAL_H__
#define __WIRING_SERIAL_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <wiringSerial.h>
#include <wiringPi.h>

class WiringSerial
{
public:
	WiringSerial(char *dev, int baudrate);
	~WiringSerial();
	
	/* 通用接口 */
	int sendTo(char* buff, int len);
	int readFrom(char* buff, int len);
	
protected:
	int serial_fd;

private:
};

#endif