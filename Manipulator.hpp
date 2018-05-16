#pragma once

#include <vector>
#include <string>
#include "Servo.hpp"
#include "StepEngine.hpp"
#include "Configuration.hpp"
#include "UDP.hpp"
#include "Structs.hpp"

class CManipulator
{
public:
	CManipulator();
	~CManipulator();
	void ConfigureManipulator(Config_Struct config);
	void TestManipulator();
	void resetConfiguration();

private:
	std::vector <CServo*> vServos;
	std::vector <CStepEngine*> vStepEngines;
	std::string configName;
	bool bConfigured;
	CUDP* connection;
public:
	inline std::vector <CServo*> GetServoVector() const { return vServos; }
	inline std::vector <CStepEngine*> GetStepEngineVector() const { return vStepEngines; }
	inline bool IsConfigured() const { return bConfigured; }
	inline std::string GetCurrentConfigName() const { return configName; }
	void MoveManipulator(int const MotorNumber, bool MotorDir, bool isServo, int Velocity);
	void setConnection(CUDP* conn);
};