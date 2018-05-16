#include "AuthorsState.hpp"
#include "Utility.hpp"
#include "ResourceHolder.hpp"
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>


AuthorsState::AuthorsState(StateStack& stack, Context context)
	: State(stack, context)
	, mKierownik()
	, mElektronicy()
	, mMechanicy()
{
	mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

	try
	{
		mTextures.load(Textures::Logo, "Resources/Textures/Logo.png");
	}
	catch (std::runtime_error& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
		exit(1);
	}

	mTextures.get(Textures::Logo).setSmooth(true);
	mLogo.setTexture(mTextures.get(Textures::Logo));
	centerOrigin(mLogo);
	mLogo.setPosition(context.window->getView().getSize().x / 2.f, 254 / 2.f + 100);

	mKierownik.setFont(context.fonts->get(Fonts::Main));
	mKierownik.setString(L"Kierownik:\nDamian Brzoza\nMicha³ Czuba");
	mKierownik.setCharacterSize(60);
	mKierownik.setOutlineThickness(2);
	centerOrigin(mKierownik);
	mKierownik.setPosition(context.window->getView().getSize().x / 2.f, context.window->getView().getSize().y / 2.f);

	mElektronicy.setFont(context.fonts->get(Fonts::Main));
	mElektronicy.setString(L"Lider: Filip Adamcewicz\nMicha³ Zawiœlak\nKacper Krej\nWiktor Paluch");
	mElektronicy.setCharacterSize(60);
	mElektronicy.setOutlineThickness(2);
	centerOrigin(mElektronicy);
	mElektronicy.setPosition(context.window->getView().getSize().x / 4.f, context.window->getView().getSize().y / 2.f + 280);

	mMechanicy.setFont(context.fonts->get(Fonts::Main));
	mMechanicy.setString("Lider: Kamil Gryglicki\nAdam Szwedor\nWojciech Chimowicz");
	mMechanicy.setCharacterSize(60);
	mMechanicy.setOutlineThickness(2);
	centerOrigin(mMechanicy);
	mMechanicy.setPosition(3 * context.window->getView().getSize().x / 4.f, context.window->getView().getSize().y / 2.f + 280);
}

void AuthorsState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.draw(mBackgroundSprite);
	window.draw(mLogo);

	window.draw(mKierownik);
	window.draw(mElektronicy);
	window.draw(mMechanicy);
}

bool AuthorsState::update(sf::Time dt)
{

	return true;
}

bool AuthorsState::handleEvent(const sf::Event& event)
{
	// If key is pressed, trigger the next screen
	if ((event.type == sf::Event::JoystickButtonPressed && event.joystickButton.button == 3) || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
		requestStackPush(States::Menu);
	}

	return true;
}