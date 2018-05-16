#include "PauseState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mBackgroundSprite()
	, mPausedText()
	, mInstructionText()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.window->getView().getSize();

	mPausedText.setFont(font);
	mPausedText.setString("PAUSE");
	mPausedText.setCharacterSize(140);
	mPausedText.setOutlineThickness(2);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString(L"Wci�nij przycisk 10 aby powr�ci�\ndo menu g��wnego");
	mInstructionText.setCharacterSize(60);
	mInstructionText.setOutlineThickness(2);
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(120, 120, 120, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::JoystickButtonPressed)
		return false;

	if (event.joystickButton.button == 8)
	{
		// Escape pressed, remove itself to return to the game
		requestStackPop();
	}

	if (event.joystickButton.button == 9)
	{
		// Escape pressed, remove itself to return to the game
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return false;
}