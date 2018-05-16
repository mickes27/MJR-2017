#ifndef BOOK_CONFIGFROMFILESTATE_HPP
#define BOOK_CONFIGFROMFILESTATE_HPP

#include "State.hpp"
#include "Configuration.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class ConfigFromFileState : public State
{
public:
	ConfigFromFileState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	bool readFile(std::string name);
	bool checkFile(std::string name);
	void printConfig();

private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mText;

	sf::String userInput;
	sf::Text sFile;
	sf::Text sFile2;
	sf::Text sState;

	bool isFile;

	Config_Struct Config;

	sf::Time mTimer;
};

#endif // BOOK_CONFIGFROMFILESTATE_HPP
