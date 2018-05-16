#include "Servo.hpp"




CServo::CServo(int pin, int pulsewidth, int upperlimit, int lowerlimit, int stepsize, CUDP* conn)
{
	iPin = pin;
	iPulseWidth = pulsewidth;
	iUpperLimit = upperlimit;
	iLowerLimit = lowerlimit;
	iStepSize = stepsize;
	connection = conn;

}


CServo::~CServo()
{
}


int CServo::UpdatePulseWidth()
{
	//connection->executeCommand("ls"); // Tu komenda ruchu
	/*if (gpioServo(iPin, iPulseWidth) == 0) {
		return 0;
	}
	else {
		return -1;
	}*/
	return 0;
}


int CServo::SetPulseWidth(int pulseWidth)
{

	if (pulseWidth < iLowerLimit) {
		return -1;
	}
	else if (pulseWidth > iUpperLimit) {
		return -1;
	}

	iPulseWidth = pulseWidth;

	if (UpdatePulseWidth() == -1) {
		return -1;
	}

	return 0;
}