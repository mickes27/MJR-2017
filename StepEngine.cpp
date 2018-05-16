#include "StepEngine.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>


CStepEngine::CStepEngine(int pul, int dir, int microsteps, int speed, CUDP* conn)
{
	iPul = pul;
	iDir = dir;
	iSpeed = speed;
	iMicroSteps = microsteps;
	connection = conn;
}

CStepEngine::~CStepEngine()
{
}

void CStepEngine::SetPul(int pul)
{
	iPul = pul;
}

void CStepEngine::SetDir(int dir)
{
	iDir = dir;
}

void CStepEngine::SetSpeed(int speed)
{
	iSpeed = speed;
}

void CStepEngine::SetMicroSteps(int microsteps)
{
	iMicroSteps = microsteps;
}

void CStepEngine::UpdateDir(int state)
{
	//std::string SSHCommand;
	//SSHCommand = "sudo pigs w " + std::to_string(iDir);
	//SSHCommand += " ";
	//SSHCommand += std::to_string(state);
	//std::cout << "Komenda: " << SSHCommand.c_str() << std::endl;

	//if (connection->executeCommand(SSHCommand) == SSH_ERROR) {
	//	std::cout << "Blad zmiany Dira" << std::endl;
	//}
	//else {
	//	std::cout<<"Zmieniono"<<std::endl;
	//}
}

int CStepEngine::CalculateFreq(int speed)
{

	int freq = 0;

	freq = iMicroSteps * speed;

	return freq;
}

void CStepEngine::MoveEngine(int speed)
{
	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
	using std::chrono::system_clock;
	int c = 0;
	
	while (1) {
		std::cout << c << std::endl;
		//connection->executeCommand("sudo pigs w 23 1"); 
		sleep_for(20us);
		//connection->executeCommand("sudo pigs w 23 0");
		sleep_for(20us);
		c++;
		system("cls");
	}
}

int CStepEngine::UpdatePulseWidth(int freq, int width)
{
	//std::string SSHCommand;
	//SSHCommand = "sudo pigs pfs " + std::to_string(iPul);
	//SSHCommand += " ";
	//SSHCommand += std::to_string(freq);
	//std::cout << "Komenda: " << SSHCommand.c_str() << std::endl;

	//if (connection->executeCommand(SSHCommand) == SSH_ERROR) {
	//	//std::cout << "Walnelo przy czestotliwosci" << std::endl;
	//	return -1;
	//}
	//else {
	//	SSHCommand = "sudo pigs p " + std::to_string(iPul);
	//	SSHCommand += " ";
	//	SSHCommand += std::to_string(width);
	//	//std::cout << "Komenda: " << SSHCommand.c_str() << std::endl;
	//
	//	if (connection->executeCommand(SSHCommand) == SSH_ERROR) {
	//		std::cout << "Walnelo przy wypelnieniu" << std::endl;
	//		return -1;
	//	}
	//	else {
	//		return 0;
	//	}
	//}
	/*
	if (gpioSetPWMfrequency(iPul, freq) < 0) {
		printw("Cos nie styklo przy czestotliwosci\n");
		refresh();
		return -1;
	}
	else {
		if (gpioPWM(iPul, width) < 0) {
			printw("Cos nie styklo przy wypelnieniu\n");
			refresh();
			return -1;
		}
		else {
			return 0;
		}
	}*/
	return 0;
}