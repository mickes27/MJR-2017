#include "TestState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <iostream>

#include <chrono>
#include <thread>

#include <SFML/Graphics/RenderWindow.hpp>

TestState::TestState(StateStack& stack, Context context)
	: State(stack, context)
	, mText()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	mText.setFont(context.fonts->get(Fonts::Main));
	mText.setOutlineThickness(2);
	mText.setString(L"Testowanie komend");
	mText.setCharacterSize(60);
	centerOrigin(mText);
	mText.setPosition(context.window->getView().getSize() / 2.f);

	mValue = 1;

}

void TestState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);
		window.draw(mText);
}

bool TestState::update(sf::Time dt)
{
	
	return true;
}

bool TestState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickMoved || event.type == sf::Event::KeyPressed)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}