#include "MenuState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"
#include <iostream>
#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mOptions()
	, mOptionIndex(0)
{

	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	sf::Font& font = context.fonts->get(Fonts::Main);

	wasZeroed = true;

	mBackgroundSprite.setTexture(texture);

	try
	{
		mTextures.load(Textures::ConnectionIcon, "Resources/Textures/Connection.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(1);
	}


	mTextures.get(Textures::ConnectionIcon).setSmooth(true);
	mConnection.setTexture(mTextures.get(Textures::ConnectionIcon));
	centerOrigin(mConnection);
	mConnection.setPosition(1880.f, 40.f);
	mConnection.setColor(sf::Color::Blue);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Ruszaj manipulatorem");
	playOption.setCharacterSize(60);
	playOption.setOutlineThickness(2);
	centerOrigin(playOption);
	playOption.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, 60.f));
	mOptions.push_back(playOption);

	sf::Text configOption;
	configOption.setFont(font);
	configOption.setString("Konfiguruj manipulator");
	configOption.setCharacterSize(60);
	configOption.setOutlineThickness(2);
	centerOrigin(configOption);
	configOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 60.f));
	mOptions.push_back(configOption);

	sf::Text authorsOption;
	authorsOption.setFont(font);
	authorsOption.setString("Autorzy");
	authorsOption.setCharacterSize(60);
	authorsOption.setOutlineThickness(2);
	centerOrigin(authorsOption);
	authorsOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 120.f));
	mOptions.push_back(authorsOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Wyjscie");
	exitOption.setCharacterSize(60);
	exitOption.setOutlineThickness(2);
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 180.f));
	mOptions.push_back(exitOption);

	sf::Text testOption;
	testOption.setFont(font);
	testOption.setString("Test");
	testOption.setCharacterSize(60);
	testOption.setOutlineThickness(2);
	centerOrigin(testOption);
	testOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 240.f));
	mOptions.push_back(testOption);

	updateOptionText();

	//conn = this->connFunc(); //TODO

}

MenuState::~MenuState()
{
	//conn.join();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);
	window.draw(mConnection);

	FOREACH(const sf::Text& text, mOptions)
		window.draw(text);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if ((event.type != sf::Event::JoystickMoved) && (event.type != sf::Event::JoystickButtonPressed) && (event.type != sf::Event::KeyPressed)) {
		return false;
	}

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {

		if (event.joystickButton.button == 1 || event.key.code == sf::Keyboard::Return)
		{
			if (mOptionIndex == Play)
			{
				requestStackPop();
				requestStackPush(States::MoveJ);
			} 
			else if (mOptionIndex == Config)
			{
				requestStackPop();
				requestStackPush(States::ConfigIntro);
			}
			else if (mOptionIndex == Authors)
			{
				requestStackPop();
				requestStackPush(States::Authors);
			}
			else if (mOptionIndex == Exit)
			{
				// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
				requestStackPop();
			}
			else if (mOptionIndex == Test)
			{
				requestStackPop();
				requestStackPush(States::Test);
			}
		}
		else if (event.key.code == sf::Keyboard::Up) {
			if (mOptionIndex > 0)
				mOptionIndex--;
			else
				mOptionIndex = mOptions.size() - 1;

			updateOptionText();
		}
		else if (event.key.code == sf::Keyboard::Down) {
			if (mOptionIndex < mOptions.size() - 1)
				mOptionIndex++;
			else
				mOptionIndex = 0;

			updateOptionText();
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

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text& text, mOptions)
		text.setColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}
