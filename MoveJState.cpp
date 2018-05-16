#include "MoveJState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MoveJState::MoveJState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
	, sState()
	, sVelocity()
{

	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);


	mBackgroundSprite.setTexture(texture);

	wasZeroed = true;

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Silnik 1");
	playOption.setCharacterSize(60);
	playOption.setOutlineThickness(2);
	centerOrigin(playOption);
	playOption.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, -400.f));
	mOptions.push_back(playOption);

	sf::Text configOption;
	configOption.setFont(font);
	configOption.setString("Silnik 2");
	configOption.setCharacterSize(60);
	configOption.setOutlineThickness(2);
	centerOrigin(configOption);
	configOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 0.f));
	mOptions.push_back(configOption);

	sf::Text authorsOption;
	authorsOption.setFont(font);
	authorsOption.setString("Silnik 3");
	authorsOption.setCharacterSize(60);
	authorsOption.setOutlineThickness(2);
	centerOrigin(authorsOption);
	authorsOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 0.f));
	mOptions.push_back(authorsOption);

	sState.setFont(font);
	sState.setString("STOP");
	sState.setCharacterSize(60);
	sState.setOutlineThickness(2);
	centerOrigin(sState);
	sState.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, 460.f));

	sVelocity.setFont(font);
	sVelocity.setString(L"Prêdkoœæ: 0");
	sVelocity.setCharacterSize(60);
	sVelocity.setOutlineThickness(2);
	centerOrigin(sVelocity);
	sVelocity.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, 400.f));



	try
	{
		mTextures.load(Textures::Gear, "Resources/Textures/gear.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(1);
	}

	mTextures.get(Textures::Gear).setSmooth(true);

	mGear.setTexture(mTextures.get(Textures::Gear));
	mGear.setScale(2.f, 2.f);
	centerOrigin(mGear);
	mGear.setPosition(1920 / 2, context.window->getSize().y / 2);
}


void MoveJState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);

	centerOrigin(sState);
	window.draw(sState);

	centerOrigin(sVelocity);
	window.draw(sVelocity);

	window.draw(mOptions[mOptionIndex]);

	window.draw(mGear);
}

bool MoveJState::update(sf::Time dt)
{
	float Velocity = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	int Turbo;

	if (sf::Joystick::isButtonPressed(0, 4)) {
		if (sf::Joystick::isButtonPressed(0, 5)) {
			Turbo = 2;
			sState.setFillColor(sf::Color::Red);
			sState.setString("TURBO!!!");
		}
		else {
			Turbo = 1;
			sState.setFillColor(sf::Color::White);
			sState.setString("Ruch manipulatora");
		}

		if (Velocity < 15 && Velocity >= -15) {
			Velocity = 0;
			sState.setFillColor(sf::Color::White);
			sState.setString("STOP");
		}
		mGear.rotate(Velocity*Turbo*dt.asSeconds());
		bool Direction;
		if (Velocity >= 15) {
			Direction = true;
		}
		else {
			Direction = false;
			Velocity = -Velocity;
		}
		std::string Val = "Predkosc: " + toString(Velocity);
		sVelocity.setString(Val);
		

		std::cout << "Silnik: " << mOptionIndex + 1 << " na predkosc: " << Velocity << std::endl;
		getContext().manipulator->MoveManipulator(getContext().manipulator->GetStepEngineVector()[mOptionIndex]->GetPul(), Direction, false, Velocity);
		
	}
	else {
		sState.setString("STOP");
	}

	return true;
}

bool MoveJState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if ((event.type != sf::Event::JoystickMoved) && (event.type != sf::Event::JoystickButtonPressed) && (event.type != sf::Event::KeyPressed)) {
		return false;
	}
	
	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {
		if (event.joystickButton.button == 8) {
			requestStackPush(States::Pause);
		} else if (event.key.code == sf::Keyboard::Up) {
			if (mOptionIndex > 0)
				mOptionIndex--;
			else
				mOptionIndex = mOptions.size() - 1;

		}
		else if (event.key.code == sf::Keyboard::Down) {
			if (mOptionIndex < mOptions.size() - 1)
				mOptionIndex++;
			else
				mOptionIndex = 0;

		}
	}

	return true;
}

