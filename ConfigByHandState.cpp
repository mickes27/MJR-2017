#include "ConfigByHandState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>


ConfigByHandState::ConfigByHandState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, Config()
	,mName()
	,mServosNum()
	,mEnginesNum()
	,mServosPins()
	,mServosUpperLimit()
	,mServosLowerLimit()
	,mServosSteps()
	,mEnginesPuls()
	,mEnginesDirs()
	,mEnginesMicrosteps()
	,mEnginesSpeeds()
	, mOptionIndex(0)
	, userInput()
	, sState()
	, mTimer(sf::Time::Zero)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	isDone = false;
	wasZeroed = true;
	isError = false;
	isChanged = false;

	sState.setFont(context.fonts->get(Fonts::Main));
	sState.setString(L"");
	sState.setCharacterSize(60);
	sState.setOutlineThickness(2);
	centerOrigin(sState);
	sState.setPosition((context.window->getView().getSize() / 2.f) + sf::Vector2f(0.f, 360.f));

	//--- Nazwa konfiguracji
	sf::Text NameInfo;
	NameInfo.setFont(context.fonts->get(Fonts::Main));
	NameInfo.setString(L"Nazwa konfiguracji:");
	NameInfo.setOutlineThickness(2);
	NameInfo.setCharacterSize(60);
	NameInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(NameInfo);

	mName.setFont(context.fonts->get(Fonts::Main));
	mName.setString(context.manipulator->GetCurrentConfigName());
	mName.setCharacterSize(60);
	mName.setOutlineThickness(2);
	mName.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 30.f));

	//--- Info o serwach
	sf::Text ServosNumInfo;
	ServosNumInfo.setFont(context.fonts->get(Fonts::Main));
	ServosNumInfo.setString(L"Liczba u¿ywanych serw:");
	ServosNumInfo.setOutlineThickness(2);
	ServosNumInfo.setCharacterSize(60);
	ServosNumInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 150.f));
	mOptions.push_back(ServosNumInfo);

	mServosNum.setFont(context.fonts->get(Fonts::Main));
	mServosNum.setString(toString(context.manipulator->GetServoVector().size()));
	mServosNum.setCharacterSize(60);
	mServosNum.setOutlineThickness(2);
	mServosNum.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 150.f));

	//--- Info o serwach
	sf::Text ServosPinsInfo;
	ServosPinsInfo.setFont(context.fonts->get(Fonts::Main));
	ServosPinsInfo.setString(L"Piny serw:");
	ServosPinsInfo.setOutlineThickness(2);
	ServosPinsInfo.setCharacterSize(60);
	ServosPinsInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 210.f));
	mOptions.push_back(ServosPinsInfo);

	mServosPins.setFont(context.fonts->get(Fonts::Main));
	std::string temp;
	for (auto Pin : context.manipulator->GetServoVector()) {
		temp += toString(Pin->GetPin()) + "\t";
	}
	mServosPins.setString(temp);
	mServosPins.setCharacterSize(60);
	mServosPins.setOutlineThickness(2);
	mServosPins.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 210.f));

	sf::Text ServosUpperLimitInfo;
	ServosUpperLimitInfo.setFont(context.fonts->get(Fonts::Main));
	ServosUpperLimitInfo.setString(L"Górna granica:");
	ServosUpperLimitInfo.setOutlineThickness(2);
	ServosUpperLimitInfo.setCharacterSize(60);
	ServosUpperLimitInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 270.f));
	mOptions.push_back(ServosUpperLimitInfo);

	mServosUpperLimit.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetServoVector()) {
		temp += toString(Pin->GetUpperLimit()) + "\t";
	}
	mServosUpperLimit.setString(temp);
	mServosUpperLimit.setCharacterSize(60);
	mServosUpperLimit.setOutlineThickness(2);
	mServosUpperLimit.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 270.f));

	sf::Text ServosLowerLimitInfo;
	ServosLowerLimitInfo.setFont(context.fonts->get(Fonts::Main));
	ServosLowerLimitInfo.setString(L"Dolna granica:");
	ServosLowerLimitInfo.setOutlineThickness(2);
	ServosLowerLimitInfo.setCharacterSize(60);
	ServosLowerLimitInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 330.f));
	mOptions.push_back(ServosLowerLimitInfo);

	mServosLowerLimit.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetServoVector()) {
		temp += toString(Pin->GetLowerLimit()) + "\t";
	}
	mServosLowerLimit.setString(temp);
	mServosLowerLimit.setCharacterSize(60);
	mServosLowerLimit.setOutlineThickness(2);
	mServosLowerLimit.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 330.f));

	sf::Text ServosStepsInfo;
	ServosStepsInfo.setFont(context.fonts->get(Fonts::Main));
	ServosStepsInfo.setString(L"Kroki serw:");
	ServosStepsInfo.setOutlineThickness(2);
	ServosStepsInfo.setCharacterSize(60);
	ServosStepsInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 390.f));
	mOptions.push_back(ServosStepsInfo);

	mServosSteps.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetServoVector()) {
		temp += toString(Pin->GetStepSize()) + "\t";
	}
	mServosSteps.setString(temp);
	mServosSteps.setCharacterSize(60);
	mServosSteps.setOutlineThickness(2);
	mServosSteps.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 390.f));

	//--- Info o silnikach
	sf::Text EnginesNumInfo;
	EnginesNumInfo.setFont(context.fonts->get(Fonts::Main));
	EnginesNumInfo.setString(L"Liczba u¿ywanych silników:");
	EnginesNumInfo.setOutlineThickness(2);
	EnginesNumInfo.setCharacterSize(60);
	EnginesNumInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 510.f));
	mOptions.push_back(EnginesNumInfo);

	mEnginesNum.setFont(context.fonts->get(Fonts::Main));
	mEnginesNum.setString(toString(context.manipulator->GetStepEngineVector().size()));
	mEnginesNum.setCharacterSize(60);
	mEnginesNum.setOutlineThickness(2);
	mEnginesNum.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 510.f));

	sf::Text EnginesPulsInfo;
	EnginesPulsInfo.setFont(context.fonts->get(Fonts::Main));
	EnginesPulsInfo.setString(L"Piny Pul silników:");
	EnginesPulsInfo.setOutlineThickness(2);
	EnginesPulsInfo.setCharacterSize(60);
	EnginesPulsInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 570.f));
	mOptions.push_back(EnginesPulsInfo);

	mEnginesPuls.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetStepEngineVector()) {
		temp += toString(Pin->GetPul()) + "\t";
	}
	mEnginesPuls.setString(temp);
	mEnginesPuls.setCharacterSize(60);
	mEnginesPuls.setOutlineThickness(2);
	mEnginesPuls.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 570.f));

	sf::Text EnginesDirsInfo;
	EnginesDirsInfo.setFont(context.fonts->get(Fonts::Main));
	EnginesDirsInfo.setString(L"Piny Dir silników:");
	EnginesDirsInfo.setOutlineThickness(2);
	EnginesDirsInfo.setCharacterSize(60);
	EnginesDirsInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 630.f));
	mOptions.push_back(EnginesDirsInfo);

	mEnginesDirs.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetStepEngineVector()) {
		temp += toString(Pin->GetDirection()) + "\t";
	}
	mEnginesDirs.setString(temp);
	mEnginesDirs.setCharacterSize(60);
	mEnginesDirs.setOutlineThickness(2);
	mEnginesDirs.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 630.f));

	sf::Text EnginesMicrostepsInfo;
	EnginesMicrostepsInfo.setFont(context.fonts->get(Fonts::Main));
	EnginesMicrostepsInfo.setString(L"Microsteps silników:");
	EnginesMicrostepsInfo.setOutlineThickness(2);
	EnginesMicrostepsInfo.setCharacterSize(60);
	EnginesMicrostepsInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 690.f));
	mOptions.push_back(EnginesMicrostepsInfo);

	mEnginesMicrosteps.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetStepEngineVector()) {
		temp += toString(Pin->GetMicroSteps()) + "\t";
	}
	mEnginesMicrosteps.setString(temp);
	mEnginesMicrosteps.setCharacterSize(60);
	mEnginesMicrosteps.setOutlineThickness(2);
	mEnginesMicrosteps.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 690.f));

	sf::Text EnginesSpeedsInfo;
	EnginesSpeedsInfo.setFont(context.fonts->get(Fonts::Main));
	EnginesSpeedsInfo.setString(L"Prêdkoœæ silników:");
	EnginesSpeedsInfo.setOutlineThickness(2);
	EnginesSpeedsInfo.setCharacterSize(60);
	EnginesSpeedsInfo.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(0.f, 750.f));
	mOptions.push_back(EnginesSpeedsInfo);

	mEnginesSpeeds.setFont(context.fonts->get(Fonts::Main));
	temp.clear();
	for (auto Pin : context.manipulator->GetStepEngineVector()) {
		temp += toString(Pin->GetSpeed()) + "\t";
	}
	mEnginesSpeeds.setString(temp);
	mEnginesSpeeds.setCharacterSize(60);
	mEnginesSpeeds.setOutlineThickness(2);
	mEnginesSpeeds.setPosition((context.window->getView().getSize() / 12.f) + sf::Vector2f(850.f, 750.f));

	updateOptionText();

	//--- Taka chamska mapa dostêpnych pinów

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
}

void ConfigByHandState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);

	FOREACH(const sf::Text& text, mOptions)
		window.draw(text);

	centerOrigin(sState);
	sState.setPosition((getContext().window->getView().getSize() / 2.f) + sf::Vector2f(0, 450.f));
	window.draw(sState);

	window.draw(mName);

	window.draw(mServosNum);
	window.draw(mServosPins);
	window.draw(mServosUpperLimit);
	window.draw(mServosLowerLimit);
	window.draw(mServosSteps);

	window.draw(mEnginesPuls);
	window.draw(mEnginesDirs);
	window.draw(mEnginesMicrosteps);
	window.draw(mEnginesSpeeds);
	window.draw(mEnginesNum);
}

bool ConfigByHandState::update(sf::Time dt)
{
	if (isDone) {
		mTimer += dt;

		if (mTimer >= sf::seconds(3.0f))
		{
			if (convertConfig() && checkPins(Config.ServoPins) && checkPins(Config.StepEnginePuls) && checkPins(Config.StepEngineDirs)) {
				std::cout << "Konfiguracja zmieniona" << std::endl;
				sState.setColor(sf::Color::Green);
				sState.setString(L"Zapisano zmiany");
				mTimer = sf::Time::Zero;
				isDone = false;
				isChanged = true;
			}
			else {
				std::cout << "Blad podczas ladowania konfiguracji" << std::endl;
				sState.setColor(sf::Color::Red);
				sState.setString(L"B³¹d konfiguracji");
				mTimer = sf::Time::Zero;
				isDone = false;
				isError = true;
			}
		}
	}
	else if (isError) {
		mTimer += dt;

		if (mTimer >= sf::seconds(3.0f))
		{
			requestStackPop();
			requestStackPush(States::ConfigIntro);
		}
	}
	else if (isChanged) {
		mTimer += dt;

		if (mTimer >= sf::seconds(3.0f))
		{
			printConfig();
			getContext().manipulator->ConfigureManipulator(Config);
				requestStackPop();
				requestStackPush(States::Menu);
		}
	}
	return true;
}

bool ConfigByHandState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::TextEntered)
	{
		switch (mOptionIndex) {
		case 0:
			userInput = mName.getString();
			break;
		case 1:
			userInput = mServosNum.getString();
			break;
		case 2:
			userInput = mServosPins.getString();
			break;
		case 3:
			userInput = mServosUpperLimit.getString();
			break;
		case 4:
			userInput = mServosLowerLimit.getString();
			break;
		case 5:
			userInput = mServosSteps.getString();
			break;
		case 6:
			userInput = mEnginesNum.getString();
			break;
		case 7:
			userInput = mEnginesPuls.getString();
			break;
		case 8:
			userInput = mEnginesDirs.getString();
			break;
		case 9:
			userInput = mEnginesMicrosteps.getString();
			break;
		case 10:
			userInput = mEnginesSpeeds.getString();
			break;
		}
	

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

		switch (mOptionIndex) {
		case 0:
			mName.setString(userInput);
			break;
		case 1:
			mServosNum.setString(userInput);
			break;
		case 2:
			mServosPins.setString(userInput);
			break;
		case 3:
			mServosUpperLimit.setString(userInput);
			break;
		case 4:
			mServosLowerLimit.setString(userInput);
			break;
		case 5:
			mServosSteps.setString(userInput);
			break;
		case 6:
			mEnginesNum.setString(userInput);
			break;
		case 7:
			mEnginesPuls.setString(userInput);
			break;
		case 8:
			mEnginesDirs.setString(userInput);
			break;
		case 9:
			mEnginesMicrosteps.setString(userInput);
			break;
		case 10:
			mEnginesSpeeds.setString(userInput);
			break;
		}

	}

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {


		if (event.joystickButton.button == 1 || event.key.code == sf::Keyboard::Return)
		{
			sState.setColor(sf::Color::Green);
			sState.setString(L"Trwa zapisywanie konfiguracji");
			isDone = true;
		}
		else if (event.key.code == sf::Keyboard::Up) {
			if (mOptionIndex > 0)
				mOptionIndex--;
			else
				mOptionIndex = mOptions.size() - 1;

			userInput.clear();
			updateOptionText();
		}
		else if (event.key.code == sf::Keyboard::Down) {
			if (mOptionIndex < mOptions.size() - 1)
				mOptionIndex++;
			else
				mOptionIndex = 0;

			userInput.clear();
			updateOptionText();
		}
		else if (event.key.code == sf::Keyboard::Escape) {
			requestStackPop();
			requestStackPush(States::ConfigIntro);
		}
	}
	else if (event.type == sf::Event::JoystickMoved) {

		if ((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position <= -15))
		{

			if (wasZeroed == true) {
				// Decrement and wrap-around
				if (mOptionIndex > 0)
					mOptionIndex--;
				else
					mOptionIndex = mOptions.size() - 1;

				updateOptionText();
				wasZeroed = false;
			}
		}

		else if ((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position >= 15))
		{
			if (wasZeroed == true) {
				// Increment and wrap-around
				if (mOptionIndex < mOptions.size() - 1)
					mOptionIndex++;
				else
					mOptionIndex = 0;

				updateOptionText();
				wasZeroed = false;
			}
		}
		else if (((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position <= 15)) || ((event.joystickMove.axis == sf::Joystick::Y) && (event.joystickMove.position >= -15))) {
			wasZeroed = true;
		}
	}

	return true;
}

void ConfigByHandState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text& text, mOptions)
		text.setColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}

bool ConfigByHandState::convertConfig()
{
	Config.sName = mName.getString();
	Config.iServoNum = atoi(mServosNum.getString().toAnsiString().c_str());

	//--- Znowu odpierdalam chujnie, potem sie zamieni
	std::vector<int> servosPins;
	std::string p = mServosPins.getString();
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
	p = mServosUpperLimit.getString();
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
	p = mServosLowerLimit.getString();
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
	p = mServosSteps.getString();
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

	Config.iStepEngineNum = atoi(mEnginesNum.getString().toAnsiString().c_str());


	std::vector<int> enginePuls;
	p = mEnginesPuls.getString();
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
	p = mEnginesDirs.getString();
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
	p = mEnginesMicrosteps.getString();
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
	p = mEnginesSpeeds.getString();
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

bool ConfigByHandState::checkPins(std::vector<int> pinVector)
{
	size_t i = 0;
	bool check = true;

	for(auto Pin : pinVector){

		if (pin_map.find(Pin) == pin_map.end()) {
			std::cout << "Pin niedozwolony!\n";
			check = false;
		}
		else {
			if (pin_map[Pin] == 1) {
				std::cout << "Pin zajety!\n";
				check = false;
			}
			else {
				std::cout << "Pin git\n";
				pin_map[Pin] = 1;
			}
		}

	}

	return check;
}
