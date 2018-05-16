#ifndef BOOK_CONFIGURATION_HPP
#define BOOK_CONFIGURATION_HPP

#include <vector>
#include <string>

struct Config_Struct
{
	std::string sName;
	int iServoNum;
	int iStepEngineNum;
	std::vector<int> ServoPins;
	std::vector<int> UpperLimits;
	std::vector<int> LowerLimits;
	std::vector<int> StepSizes;

	std::vector<int> StepEnginePuls;
	std::vector<int> StepEngineDirs;
	std::vector<int> Microsteps;
	std::vector<int> Speeds;
};
#endif // BOOK_CONFIGURATION_HPP