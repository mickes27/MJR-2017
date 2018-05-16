#ifndef BOOK_CONFIGINTROSTATE_HPP
#define BOOK_CONFIGINTROSTATE_HPP

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class ConfigIntroState : public State
{
public:
	ConfigIntroState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

	void updateOptionText();

private:
	enum OptionNames
	{
		File,
		Manual,
	};

private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	std::vector<sf::Text> mOptions;
	std::size_t mOptionIndex;
	bool wasZeroed;

};

#endif // BOOK_CONFIGINTROSTATE_HPP
