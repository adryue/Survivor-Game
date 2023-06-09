#include "play.h"

//There is a global vector that stores all the bullets currently fired
//This is to make collision detection with objects easier
//Each bullet has an owner (the person that originally fired it)
std::vector<Projectile*> projectiles;

//global vector that stores all the guns on the ground
//add or remove from it whenever the player picks up / drops guns
std::vector<Gun*> guns;


void createProjectile(Projectile* projectile) //function is called from the Player class when it is running the update function
{
    projectiles.push_back(projectile);
}

Gun* getGun(const int index)
{
    return guns[index];
}
void addGun(Gun* gun)
{
    guns.push_back(gun);
}
void removeGun(const int index)
{
    guns.erase(guns.begin() + index);
}
int numGuns()
{
    return guns.size();
}

ScreenName playScreen(sf::RenderWindow &window)
{
    sf::Cursor normalCursor;
    normalCursor.loadFromSystem(sf::Cursor::Cross);
    window.setMouseCursor(normalCursor);

    //Create map
    sf::Texture mapTexture;
    mapTexture.loadFromFile("Images/grid.png");
    sf::Sprite mapSprite;
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(5.0, 5.0);

    /*sf::Texture tempTexture;
    tempTexture.loadFromFile("Data/Bullets/Bullet1.png");
    sf::Sprite tempSprite;
    tempSprite.setTexture(tempTexture);
    tempSprite.setOrigin(1, 1);
    tempSprite.setRotation(500);
    tempSprite.setPosition(10, 10);
    tempSprite.move(1, 1);
    tempSprite.move(1, 1);*/


    //Create player
    Player player;
    //Camera
    sf::View playerView;
    playerView.setSize(WIN_X_LEN, WIN_Y_LEN);
    playerView.setViewport(sf::FloatRect(0.0, 0.0, 1.0, 1.0));

    //load all the guns
    guns.push_back(new Gun("Gun1", sf::Vector2f(500, 500)));
    guns.push_back(new Gun("Gun2", sf::Vector2f(300, 300)));
    guns.push_back(new Gun("Gun2", sf::Vector2f(500, 300)));
    guns.push_back(new Gun("Gun1", sf::Vector2f(300, 500)));

    //GAME LOOP
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed)
            {
                window.close();
                return ScreenName::none;
            }
        }
        window.clear();

        //handle player (movement, equip/unequip, switching selected gun, pointing at mouse, firing
        player.update(sf::Mouse::getPosition(window));

        //handle projectiles (update position, checking and handling collisions
        for (Projectile* &p : projectiles)
        {
            p->update();
        }

        //draw everything
        playerView.setCenter(player.getPosition()); //set the camera view to the player
        window.setView(playerView);

        window.draw(mapSprite); //draw the background
        for (unsigned int i = 0; i < guns.size(); i++) //draw the guns on the ground
        {
            guns[i]->draw(window);
        }
        player.draw(window); //draw the player (and gun)
        for (Projectile* &p : projectiles) //draw the projectiles
        {
            p->draw(window);
        }


        window.display();
    }

    return ScreenName::none;
}
