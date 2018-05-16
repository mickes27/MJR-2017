#include "ConfigFromFileState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cerrno>
#include <cstdlib>

#include <SFML/Graphics/RenderWindow.hpp>


ConfigFromFileState::ConfigFromFileState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, sFile()
	, sFile2()
	, sState()
	, userInput()
	, mTimer(sf::Time::Zero)
{
	isFile = false;

	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString(L"Wpisz nazwê pliku w katalogu 'Configs':");
	mText.setOutlineThickness(2);
	mText.setCharacterSize(60);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize().x / 2.f, 60.f);

	sFile.setFont(context.fonts->get(Fonts::Main));
	sFile.setString(L"Nazwa pliku:");
	sFile.setOutlineThickness(2);
	sFile.setCharacterSize(60);
	sFile.setPosition((context.window->getView().getSize() / 5.f) + sf::Vector2f(0.f, 180.f));

	sFile2.setString(L"default.cfg");
	sFile2.setFont(context.fonts->get(Fonts::Main));
	sFile2.setCharacterSize(60);
	sFile2.setOutlineThickness(2);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"");
	sState.setCharacterSize(60);
	sState.setOutlineThickness(2);
	centerOrigin(sState);
	sState.setPosition((context.window->getView().getSize() / 2.f) + sf::Vector2f(0.f, 360.f));

}

void ConfigFromFileState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	window.draw(sFile);

	sFile2.setPosition((getContext().window->getView().getSize() / 5.f) + sf::Vector2f(350.f, 180.f));
	window.draw(sFile2);
	window.draw(mText);

	centerOrigin(sState);
	sState.setPosition((getContext().window->getView().getSize() / 2.f) + sf::Vector2f(0, 360.f));
	window.draw(sState);

}

bool ConfigFromFileState::update(sf::Time dt)
{
	if (isFile) {
		mTimer += dt;

		if (mTimer >= sf::seconds(3.0f))
		{
			if (readFile(sFile2.getString())) {
				printConfig();
				getContext().manipulator->ConfigureManipulator(Config);
				
					requestStackPop();
					requestStackPush(States::Menu);
				
			} else {
				std::cout << "Blad podczas ladowania konfiguracji" << std::endl;
			}
		}
	}
	return true;
}

bool ConfigFromFileState::handleEvent(const sf::Event& event)
{

	if (event.type == sf::Event::TextEntered)
	{
		
		userInput = sFile2.getString();
	

		if (event.text.unicode == '\b') {
			if (userInput.getSize() > 0) {
				userInput.erase(userInput.getSize() - 1, 1);
			}
		}
		else if (event.text.unicode == '\n' || event.text.unicode == '\r') {
			
		}
		else if (event.text.unicode < 128) {
			userInput += event.text.unicode;
		}

		
		sFile2.setString(userInput);


	}

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {


		if (event.joystickButton.button == 1 || event.key.code == sf::Keyboard::Return)
		{
			if (checkFile(sFile2.getString())) {
				//OBSLUGA PLIKU
				sState.setColor(sf::Color::Green);
				sState.setString(L"Plik istnieje, zaczynam ³adowanie konfiguracji");
				isFile = true;
			}
			else {
				//BRAK PLIKU
				sState.setColor(sf::Color::Red);
				sState.setString(L"B³¹d otwierania pliku.\nSprawdŸ czy plik istnieje oraz uprawnienia");
			}
		}
	}

	return true;
}

bool ConfigFromFileState::readFile(std::string name) //--- Redundancja Wydzia³u Chemii Uniwersytetu Jagielloñskiego
{

	std::ifstream file;
	std::string file_path = "Configs/" + name;
	file.open(file_path);

	if (file.good() == true)
	{
		//--- Zmienna œmieciowa
		std::string temp;

		//--- Nazwa configu
		std::string configName;
		std::getline(file, configName);

		//--- Iloœæ serw
		int servosNum;
		file >> servosNum;

		//--- Piny serw
		while (temp.empty()) {
			std::getline(file, temp);
		}

		std::string p;
		p = temp;
		temp.clear();

		std::vector<int> servosPins;
		int j = servosNum;
		char *end;

		for (int i = std::strtol(p.c_str(), &end, 10); p.c_str() != end; i = std::strtol(p.c_str(), &end, 10))
		{
			p = end;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				servosPins.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Górne granice serw
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();

		std::vector<int> upperLimits;
		j = servosNum;
		char *end5;

		for (int i = std::strtol(p.c_str(), &end5, 10); p.c_str() != end5; i = std::strtol(p.c_str(), &end5, 10))
		{
			p = end5;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				upperLimits.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Dolne granice serw
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();

		std::vector<int> lowerLimits;
		j = servosNum;
		char *end6;

		for (int i = std::strtol(p.c_str(), &end6, 10); p.c_str() != end6; i = std::strtol(p.c_str(), &end6, 10))
		{
			p = end6;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				lowerLimits.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Kroki serw
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();

		std::vector<int> servosSteps;
		j = servosNum;
		char *end7;

		for (int i = std::strtol(p.c_str(), &end7, 10); p.c_str() != end7; i = std::strtol(p.c_str(), &end7, 10))
		{
			p = end7;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				servosSteps.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Liczba silnikow krokowych
		int enginesNum;
		file >> enginesNum;

		//--- Pule silnikow krokowych
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();
		std::vector<int> enginesPins;
		j = enginesNum;
		char *end2;

		for (int i = std::strtol(p.c_str(), &end2, 10); p.c_str() != end2; i = std::strtol(p.c_str(), &end2, 10))
		{
			p = end2;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				enginesPins.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Diry silników krokowych
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();
		std::vector<int> enginesDirs;
		j = enginesNum;
		char *end3 = NULL;

		for (int i = std::strtol(p.c_str(), &end3, 10); p.c_str() != end3; i = std::strtol(p.c_str(), &end3, 10))
		{
			p = end3;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				enginesDirs.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Microstepy silników krokowych
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();
		std::vector<int> microsteps;
		j = enginesNum;
		char *end4 = NULL;

		for (int i = std::strtol(p.c_str(), &end4, 10); p.c_str() != end4; i = std::strtol(p.c_str(), &end4, 10))
		{
			p = end4;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				microsteps.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		//--- Predkosci silników krokowych
		while (temp.empty()) {
			std::getline(file, temp);
		}

		p = temp;
		temp.clear();
		std::vector<int> speeds;
		j = enginesNum;
		char *end8 = NULL;

		for (int i = std::strtol(p.c_str(), &end8, 10); p.c_str() != end8; i = std::strtol(p.c_str(), &end8, 10))
		{
			p = end8;
			if (errno == ERANGE) {
				errno = 0;
			}
			if (j > 0) {
				speeds.push_back(i);
				j--;
			}
		}

		if (j > 0) {
			return false;
		}

		Config.sName = configName;
		Config.iServoNum = servosNum;
		Config.UpperLimits = upperLimits;
		Config.LowerLimits = lowerLimits;
		Config.StepSizes = servosSteps;
		Config.iStepEngineNum = enginesNum;
		Config.ServoPins = servosPins;
		Config.StepEnginePuls = enginesPins;
		Config.StepEngineDirs = enginesDirs;
		Config.Microsteps = microsteps;
		Config.Speeds = speeds;

		file.close();
	}

	return true;
}

bool ConfigFromFileState::checkFile(std::string name)
{
	std::ifstream file;
	std::string file_path = "Configs/" + name;
	file.open(file_path);

	if (file.good() == true)
	{
		file.close();
		return true;
	}
	else {
		return false;
	}
}

void ConfigFromFileState::printConfig()
{
	std::cout << "Nazwa konfiguracji:\t" << Config.sName.c_str() << std::endl << std::endl;

	std::cout << "Ilosc serw:\t" << Config.iServoNum << std::endl;
	std::cout << "Piny:\t\t";
	for (auto Pin : Config.ServoPins) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n";
	std::cout << "Gorne granice:\t";
	for (auto Pin : Config.UpperLimits) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n";
	std::cout << "Dolne granice:\t";
	for (auto Pin : Config.LowerLimits) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n";
	std::cout << "Kroki:\t\t";
	for (auto Pin : Config.StepSizes) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n\n";

	std::cout << "Ilosc silnikow:\t" << Config.iStepEngineNum << std::endl;
	std::cout << "Pul:\t\t";
	for (auto Pin : Config.StepEnginePuls) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n";
	std::cout << "Dir:\t\t";
	for (auto Pin : Config.StepEngineDirs) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n";
	std::cout << "Microsteps:\t";
	for (auto Pin : Config.Microsteps) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n";
	std::cout << "Speed:\t\t";
	for (auto Pin : Config.Speeds) {
		std::cout << Pin << "\t";
	}
	std::cout << "\n\n";
}
