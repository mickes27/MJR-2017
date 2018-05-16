#include "ConfigByHandState.hpp"
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


ConfigByHandState::ConfigByHandState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, userInput()
	, sValue()
	, mOptions()
	, mValues()
	, mOptionIndex(0)
	, mTimer(sf::Time::Zero)
{
	isDone = false;

	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setString(L"Określ parametry manipulatora:");
	mText.setOutlineThickness(2);
	mText.setCharacterSize(60);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize().x / 2.f, 60.f);

	//--- Tutaj można pokombinować z pętlą, ale muszę ogarnąć łączenie stringów, żeby zachować polskie znaki
	sf::Text sState;
	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Nazwa konfiguracji:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Ilość używanych serw:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Piny serw:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Górne granice serw:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Dolne granice serw:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Kroki serw:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Ilość używanych silników\nkrokowych:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Piny Pul silników:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Piny Dir silników:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Microsteps:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"Prędkość silników:");
	sState.setOutlineThickness(2);
	sState.setCharacterSize(60);
	sState.setPosition((context.window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(sState);

	//--- Koniec tej mañany

	sValue.setString(L"none");
	sValue.setFont(context.fonts->get(Fonts::Main));
	sValue.setCharacterSize(60);
	sValue.setOutlineThickness(2);

}

void ConfigByHandState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	sValue.setPosition((getContext().window->getView().getSize() / 7.f) + sf::Vector2f(850.f, 180.f));
	window.draw(sValue);
	window.draw(mText);

	mOptions[mOptionIndex].setPosition((getContext().window->getView().getSize() / 7.f) + sf::Vector2f(0.f, 180.f));
	window.draw(mOptions[mOptionIndex]);

}

bool ConfigByHandState::update(sf::Time dt)
{
	if (isDone) {
		mTimer += dt;

		if (mTimer >= sf::seconds(3.0f))
		{
			//OBSLUGA
		}
	}
	return true;
}

bool ConfigByHandState::handleEvent(const sf::Event& event)
{

	if (event.type == sf::Event::TextEntered)
	{

		userInput = sValue.getString();


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


		sValue.setString(userInput);


	}

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {


		if (event.joystickButton.button == 1 || event.key.code == sf::Keyboard::Return)
		{
			mValues.push_back(sValue.getString());
			if (mOptionIndex < mOptions.size() - 1) {
				mOptionIndex++;
			}
			else {
				if (convertConfig()) {
					printConfig();
					system("PAUSE");
					//TODO
				}
				else {
					requestStackPop();
					requestStackPush(States::ConfigByHand);
				}
			}
		}
	}

	return true;
}

void ConfigByHandState::printConfig()
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

bool ConfigByHandState::convertConfig()
{
	Config.sName = mValues[0];

	Config.iServoNum = atoi(mValues[1].c_str());

	//--- Znowu odpierdalam chujnie, potem sie zamieni
	std::vector<int> servosPins;
	std::string p = mValues[2];
	int j = Config.iServoNum;
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

	Config.ServoPins = servosPins;


	std::vector<int> servosUp;
	p = mValues[3];
	j = Config.iServoNum;
	char *end1;

	for (int i = std::strtol(p.c_str(), &end1, 10); p.c_str() != end1; i = std::strtol(p.c_str(), &end1, 10))
	{
		p = end1;
		if (errno == ERANGE) {
			errno = 0;
		}
		if (j > 0) {
			servosUp.push_back(i);
			j--;
		}
	}

	if (j > 0) {
		return false;
	}

	Config.UpperLimits = servosUp;


	std::vector<int> servosDown;
	p = mValues[4];
	j = Config.iServoNum;
	char *end2;

	for (int i = std::strtol(p.c_str(), &end2, 10); p.c_str() != end2; i = std::strtol(p.c_str(), &end2, 10))
	{
		p = end2;
		if (errno == ERANGE) {
			errno = 0;
		}
		if (j > 0) {
			servosDown.push_back(i);
			j--;
		}
	}

	if (j > 0) {
		return false;
	}

	Config.LowerLimits = servosDown;


	std::vector<int> servosSteps;
	p = mValues[5];
	j = Config.iServoNum;
	char *end3;

	for (int i = std::strtol(p.c_str(), &end3, 10); p.c_str() != end3; i = std::strtol(p.c_str(), &end3, 10))
	{
		p = end3;
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

	Config.StepSizes = servosSteps;


	Config.iStepEngineNum = atoi(mValues[6].c_str());


	std::vector<int> enginePuls;
	p = mValues[7];
	j = Config.iStepEngineNum;
	char *end4;

	for (int i = std::strtol(p.c_str(), &end4, 10); p.c_str() != end4; i = std::strtol(p.c_str(), &end4, 10))
	{
		p = end4;
		if (errno == ERANGE) {
			errno = 0;
		}
		if (j > 0) {
			enginePuls.push_back(i);
			j--;
		}
	}

	if (j > 0) {
		return false;
	}

	Config.StepEnginePuls = enginePuls;


	std::vector<int> engineDirs;
	p = mValues[8];
	j = Config.iStepEngineNum;
	char *end5;

	for (int i = std::strtol(p.c_str(), &end5, 10); p.c_str() != end5; i = std::strtol(p.c_str(), &end5, 10))
	{
		p = end5;
		if (errno == ERANGE) {
			errno = 0;
		}
		if (j > 0) {
			engineDirs.push_back(i);
			j--;
		}
	}

	if (j > 0) {
		return false;
	}

	Config.StepEngineDirs = engineDirs;


	std::vector<int> engineMicros;
	p = mValues[9];
	j = Config.iStepEngineNum;
	char *end6;

	for (int i = std::strtol(p.c_str(), &end6, 10); p.c_str() != end6; i = std::strtol(p.c_str(), &end6, 10))
	{
		p = end6;
		if (errno == ERANGE) {
			errno = 0;
		}
		if (j > 0) {
			engineMicros.push_back(i);
			j--;
		}
	}

	if (j > 0) {
		return false;
	}

	Config.Microsteps = engineMicros;


	std::vector<int> engineSpeeds;
	p = mValues[10];
	j = Config.iStepEngineNum;
	char *end7;

	for (int i = std::strtol(p.c_str(), &end7, 10); p.c_str() != end7; i = std::strtol(p.c_str(), &end7, 10))
	{
		p = end7;
		if (errno == ERANGE) {
			errno = 0;
		}
		if (j > 0) {
			engineSpeeds.push_back(i);
			j--;
		}
	}

	if (j > 0) {
		return false;
	}

	Config.Speeds = engineSpeeds;

	return true;
}
