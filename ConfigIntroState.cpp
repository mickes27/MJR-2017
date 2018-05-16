#include "ConfigIntroState.hpp"
#include "Utility.hpp"
#include "Foreach.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


ConfigIntroState::ConfigIntroState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
	, mOptions()
	, mOptionIndex(0)
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setOutlineThickness(2);
	mText.setString(L"Wybierz tryb konfiguracji manipulatora");
	mText.setCharacterSize(60);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize().x / 2.f, 60.f);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(context.fonts->get(Fonts::Main));
	playOption.setString(L"Konfiguracja z pliku");
	playOption.setCharacterSize(60);
	playOption.setOutlineThickness(2);
	centerOrigin(playOption);
	playOption.setPosition((context.window->getView().getSize() / 2.f) - sf::Vector2f(0.f, 60.f));
	mOptions.push_back(playOption);

	sf::Text configOption;
	configOption.setFont(context.fonts->get(Fonts::Main));
	configOption.setString(L"Konfiguracja rêczna");
	configOption.setCharacterSize(60);
	configOption.setOutlineThickness(2);
	centerOrigin(configOption);
	configOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 60.f));
	mOptions.push_back(configOption);


	updateOptionText();
}

void ConfigIntroState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);
	window.draw(mText);

	sf::Text Configured;
	
	if (getContext().manipulator->IsConfigured() != false) {
		Configured.setColor(sf::Color::Green);
		Configured.setString(L"Manipulator skonfigurowany");
	}
	else {
		Configured.setColor(sf::Color::Red);
		Configured.setString(L"Brak konfiguracji manipulatora");
	}

	Configured.setFont(getContext().fonts->get(Fonts::Main));
	Configured.setCharacterSize(60);
	Configured.setOutlineThickness(2);
	centerOrigin(Configured);
	Configured.setPosition(getContext().window->getView().getSize() / 2.f + sf::Vector2f(0.f, 360.f));

	window.draw(Configured);

	FOREACH(const sf::Text& text, mOptions)
		window.draw(text);

}

bool ConfigIntroState::update(sf::Time dt)
{
	return true;
}

bool ConfigIntroState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if ((event.type != sf::Event::JoystickMoved) && (event.type != sf::Event::JoystickButtonPressed) && (event.type != sf::Event::KeyPressed)) {
		return false;
	}

	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::KeyPressed) {

		if (event.joystickButton.button == 1 || event.key.code == sf::Keyboard::Return)
		{
			if (mOptionIndex == Manual)
			{
				requestStackPop();
				requestStackPush(States::ConfigByHand);
			}
			else if (mOptionIndex == File)
			{
				requestStackPop();
				requestStackPush(States::ConfigFromFile);
			}			
		}
		else if (event.key.code == sf::Keyboard::Up) { //--- Odkomentowac po dodaniu konfigu recznego
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
		else if (event.key.code == sf::Keyboard::Escape || event.joystickButton.button == 3) {
			requestStackPop();
			requestStackPush(States::Menu);
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

void ConfigIntroState::updateOptionText()
{
	if (mOptions.empty())
		return;

	// White all texts
	FOREACH(sf::Text& text, mOptions)
		text.setColor(sf::Color::White);

	// Red the selected text
	mOptions[mOptionIndex].setColor(sf::Color::Red);
}
