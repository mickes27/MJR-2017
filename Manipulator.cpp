#include "Manipulator.hpp"
#include <map>
#include <iostream>
#include <Windows.h>
#include <cmath>

#define delay_sygnalu 100 // [micro sec.], >5

CManipulator::CManipulator()
{
	bConfigured = false;
}

void CManipulator::ConfigureManipulator(Config_Struct config)
{
	resetConfiguration();
	//--- Taka chamska mapa dostêpnych pinów

	std::map <int, bool> pin_map;
	pin_map[18] = 0;
	pin_map[23] = 0;
	pin_map[24] = 0;
	pin_map[25] = 0;
	pin_map[8] = 0;
	pin_map[7] = 0;
	pin_map[12] = 0;
	pin_map[16] = 0;
	pin_map[20] = 0;
	pin_map[21] = 0;
	pin_map[19] = 0;
	pin_map[26] = 0;

	//--- Koniec mapy

	configName = config.sName;

	for (int i = 0; i < config.iServoNum; i++) {


		//--- Sprawdzanie czy pin jest dozwolony

		bool check = true;

		while (check) {

			if (pin_map.find(config.ServoPins[i]) == pin_map.end()) {
				std::cout << "Pin niedozwolony!\n";
			}
			else {
				if (pin_map[config.ServoPins[i]] == 1) {
					std::cout << "Pin zajety!\n";
				}
				else {
					std::cout << "Pin git\n";
					check = false;
				}
			}

		}

		//--- Koniec sprawdzania pinu


		pin_map[config.ServoPins[i]] = 1;

		CServo servo(config.ServoPins[i], (config.UpperLimits[i] + config.LowerLimits[i]) / 2, config.UpperLimits[i], config.LowerLimits[i], config.StepSizes[i], connection);

		vServos.push_back(new CServo(servo));

	}

	for (int i = 0; i < config.iStepEngineNum; i++) {

		//--- Sprawdzanie czy pin jest dozwolony

		bool check = true;

		while (check) {

			if (pin_map.find(config.StepEnginePuls[i]) == pin_map.end()) {
				std::cout<< "Pin niedozwolony!\n";
			}
			else {
				if (pin_map[config.StepEnginePuls[i]] == 1) {
					std::cout<< "Pin zajety!\n";
				}
				else {
					std::cout<< "Pin git\n";
					check = false;
				}
			}

		}

		pin_map[config.StepEnginePuls[i]] = 1;

		check = true;

		while (check) {

			if (pin_map.find(config.StepEngineDirs[i]) == pin_map.end()) {
				std::cout<< "Pin niedozwolony!\n";
			}
			else {
				if (pin_map[config.StepEngineDirs[i]] == 1) {
					std::cout<< "Pin zajety!\n";
				}
				else {
					std::cout<< "Pin git\n";
					check = false;
				}
			}

		}

		pin_map[config.StepEngineDirs[i]] = 1;

		//--- Koniec sprawdzania

		CStepEngine engine(config.StepEnginePuls[i], config.StepEngineDirs[i], config.Microsteps[i], config.Speeds[i], connection);

		vStepEngines.push_back(new CStepEngine(engine));

	}

	bConfigured = true;
}

CManipulator::~CManipulator()
{
	for (auto Servo : vServos) {
		Servo->~CServo();
	}
	for (auto StepEngine : vStepEngines) {
		StepEngine->~CStepEngine();
	}
}

void CManipulator::MoveManipulator(int MotorNumber, bool MotorDir, bool isServo, int Velocity)
{
	
	if (isServo == false) {
		Package pack;
		pack.Command = "engine";
		pack.Pul = MotorNumber;
		if (MotorDir) {
			pack.Dir = true;
		}
		else {
			pack.Dir = false;
		}
		int DelayVal = round((-1750 / 85) * Velocity + (196250 / 85));
		std::cout << "VELOCITY: " << Velocity<< "DELAY: " << DelayVal << std::endl;
		pack.Delay = DelayVal;
		connection->sendPacket(pack);
	}
	else {				//--- Jeœli to serwomechanizm - BYDZIE PONIJ
					/*int Sign = 0;
		int Number = MotorNumber - 5;
				if (MotorDir == 1) {
			Sign = 1;
		}
		else if (MotorDir == 0) {
			Sign = -1;
		}
			int Width = vServos[Number]->GetCurrentPulseWidth() + vServos[Number]->GetStepSize()*Sign;	//--- Wyliczenie wype³nienia dla zadanego po³o¿enia
		vServos[Number]->SetPulseWidth(Width);			//--- Aktywowanie PWM i ustawienie pozycji*/
		
		//Sleep(1);
	}
	
}

void CManipulator::setConnection(CUDP * conn)
{
	connection = conn;
}

void CManipulator::TestManipulator()
{
	/*printw("Testowania serwomechanizmow...\n\n");
	refresh();

	for (auto Servo : vServos) {
		Servo->SetPulseWidth(Servo->GetLowerLimit());
		sleep(0.5);
		Servo->SetPulseWidth(Servo->GetUpperLimit());
		sleep(0.5);
	}

	printw("Testowania silnikow krokowych...\n\n");
	refresh();

	for (auto Engine : vStepEngines) {
		Engine->UpdateDir(1);
		usleep(delay_sygnalu);
		Engine->UpdatePulseWidth(Engine->CalculateFreq(1), 30);
		sleep(5);
		Engine->UpdatePulseWidth(Engine->CalculateFreq(1), 0);
		sleep(1);
		Engine->UpdateDir(0);
		usleep(delay_sygnalu);
		Engine->UpdatePulseWidth(Engine->CalculateFreq(1), 30);
		sleep(5);
		Engine->UpdatePulseWidth(Engine->CalculateFreq(1), 0);
		sleep(1);
	}

	printw("Zakonczono testowanie\n");
	refresh();
	sleep(1);*/
}

void CManipulator::resetConfiguration()
{
	configName.clear();
	vServos.clear();
	vStepEngines.clear();
	bConfigured = false;
}
