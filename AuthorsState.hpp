#ifndef BOOK_AUTHORSSTATE_HPP
#define BOOK_AUTHORSSTATE_HPP

#include "State.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class AuthorsState : public State
{
public:
	AuthorsState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);


private:
	sf::Sprite			mBackgroundSprite;
	sf::Sprite			mLogo;
	sf::Text			mKierownik;
	sf::Text			mElektronicy;
	sf::Text			mMechanicy;

	TextureHolder mTextures;
};

#endif // BOOK_TITLESTATE_HPP
