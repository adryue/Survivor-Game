#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "CommonDef.h"
#include "projectile.h"

class Bullet : public Projectile
{
public:
    sf::CircleShape hitbox;

    float speed;
    float damage;
    int expireTime; //number of frames before the bullet disappears
    int currentTime; //number of frames that this bullet has existed for

    Bullet(std::string Name, const sf::Vector2f pos, const float rotation, const Owner own); //rotation is in degrees
    void draw(sf::RenderWindow &window);
    void update();
};

#endif // BULLET_H_INCLUDED
