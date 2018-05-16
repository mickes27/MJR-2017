#ifndef BOOK_CONFIGBYHANDSTATE_HPP
#define BOOK_CONFIGBYHANDSTATE_HPP

#include "State.hpp"
#include "Configuration.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include <map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class ConfigByHandState : public State
{
public:
	ConfigByHandState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

	void updateOptionText();
	bool convertConfig();
	void printConfig();
	bool checkPins(std::vector<int> pinVector);

private:
	enum OptionNames
	{
		NameInfo,
		ServosNumInfo,
		EnginesNumInfo,
		ServosPinsInfo,
		ServosUpperLimitInfo,
		ServosLowerLimitInfo,
		ServosStepsInfo,
		EnginesPulsInfo,
		EnginesDirsInfo,
		EnginesMicrostepsInfo,
		EnginesSpeedsInfo
	};

private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mName;

	sf::Text			mServosNum;
	sf::Text			mEnginesNum;

	sf::Text			mServosPins;
	sf::Text			mServosUpperLimit;
	sf::Text			mServosLowerLimit;
	sf::Text			mServosSteps;

	sf::Text			mEnginesPuls;
	sf::Text			mEnginesDirs;
	sf::Text			mEnginesMicrosteps;
	sf::Text			mEnginesSpeeds;

	sf::String userInput;
	sf::Text sState;

	std::size_t mOptionIndex;
	std::vector<sf::Text> mOptions;

	sf::Time			mTimer;

	Config_Struct Config;

	bool wasZeroed;
	bool isDone;
	bool isError;
	bool isChanged;

	std::map <int, bool> pin_map;
};

#endif // BOOK_CONFIGBYHANDSTATE_HPP
