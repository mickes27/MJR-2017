#include "Application.hpp"
#include "UDP.hpp"
#include <SFML/Audio.hpp>

int main()
{
	sf::Music music;
	if (music.openFromFile("Resources/Music/Theme.ogg")) {
		music.play();
	}
	music.setVolume(5);
	music.setLoop(true);

	CApplication app;
	app.run();

	return 0;
}
