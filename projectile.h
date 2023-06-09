#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <string>
#include "CommonDef.h"

class Projectile
{
public:
    std::string name;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::Vector2f position;
    sf::Vector2f velocity;

    enum Owner
    {
        player,
        enemy
    };
    Owner owner;

    virtual void update() = 0; //function that's called every frame
    virtual void draw(sf::RenderWindow &window) = 0;
};

#endif // PROJECTILE_H_INCLUDED
