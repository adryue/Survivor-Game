#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "CommonDef.h"
#include "gun.h"

class Player
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::CircleShape hitbox;

    Gun *inventory[3];
    int currentItem; //index of the item currently being used


public:
    Player();
    void draw(sf::RenderWindow &window);
    void update(const sf::Vector2i mouse); //handles movement, firing, equipping weapons

    void pointAt(const sf::Vector2i position);

    void updateFiring();

    void move(const sf::Vector2f offset);
    sf::Vector2f getPosition();

    void equip(); //checks if there are guns nearby and equips one of them (if there are available slots)
    void unequip();
};

#endif // PLAYER_H_INCLUDED
