#ifndef BOOK_OLDCONFIGBYHANDSTATE_HPP
#define BOOK_OLDCONFIGBYHANDSTATE_HPP

#include "State.hpp"
#include "Configuration.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class ConfigByHandState : public State
{
public:
	ConfigByHandState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	void printConfig();
	bool convertConfig();

private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	sf::String userInput;
	sf::Text sValue;

	bool isDone;
	int iCounter;

	Config_Struct Config;

	sf::Time mTimer;

	std::vector<sf::Text> mOptions;
	std::vector<std::string> mValues;
	std::size_t mOptionIndex;
};

#endif // BOOK_OLDCONFIGBYHANDSTATE_HPP
