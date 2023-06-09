#include <SFML/Graphics.hpp>
#include "CommonDef.h"
#include "play.h"
#include "player.h"

const int WIN_X_LEN = 800;
const int WIN_Y_LEN = 600;
const int FRAMERATE = 60;

const float PLAYER_SIZE = 40;
const float PLAYER_SPEED = 5.0;

const float GUN_PICKUP_RANGE = 60.0;

const float BULLET_DEFAULT_SPEED = 10.0;
const int BULLET_DEFAULT_FIRE_SPEED = 10;
const float BULLET_DEFAULT_SIZE = 10.0;

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIN_X_LEN, WIN_Y_LEN), "Survivor");
    window.setFramerateLimit(FRAMERATE);

    ScreenName nextScreen = ScreenName::play;

	// Start the game loop
    while (window.isOpen())
    {
        switch (nextScreen)
        {
        case ScreenName::home:
            break;
        case ScreenName::settings:
            break;
        case ScreenName::play:
            playScreen(window);
            break;
        case ScreenName::lose:
            break;
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
}
