#include <fstream>
#include <cmath>
#include "bullet.h"

void Bullet::update() //moves bullet, checks collisions (and calculates damage), checks expiration
{
    sprite.move(velocity);
    hitbox.move(velocity);
    position = hitbox.getPosition();
    currentTime++;
    if (currentTime == expireTime)
    {

    }
}

Bullet::Bullet(std::string Name, const sf::Vector2f pos, const float rotation, const Owner own) //rotation is in degrees
{
    name = Name;
    std::ifstream fin("Data/Bullets/" + Name + ".txt");
    fin >> speed;
    fin >> damage;
    fin >> expireTime;
    currentTime = 0;
    fin.close();

    texture.loadFromFile("Data/Bullets/" + Name + ".png");
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setRotation(rotation);
    sprite.setPosition(pos);

    hitbox.setRadius(BULLET_DEFAULT_SIZE);
    hitbox.setFillColor(sf::Color::Blue);
    hitbox.setOrigin(BULLET_DEFAULT_SIZE / 2, BULLET_DEFAULT_SIZE / 2);
    hitbox.setRotation(rotation);
    hitbox.setPosition(pos);

    position = pos;
    velocity.x = speed * std::cos(rotation * M_PI / 180);
    velocity.y = speed * std::sin(rotation * M_PI / 180);

    owner = own;

    currentTime = 0;
}

void Bullet::draw(sf::RenderWindow &window)
{
    //window.draw(hitbox);
    sprite.setTexture(texture);
    window.draw(sprite);
    //draw trail?
}
