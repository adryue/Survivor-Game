#ifndef GUN_H_INCLUDED
#define GUN_H_INCLUDED

#include "CommonDef.h"

class Gun
{
public:
    sf::Texture equippedTexture;
    sf::Texture groundTexture;
    sf::Sprite sprite;

    float rotation; //in degrees
    std::string name;
    sf::Vector2f groundPosition;

    int fireSpeed; //the number of frames it takes to fire 1 bullet
    int currentTick;
    int capacity; //the number of bullets
    std::string bulletType;

    enum Status
    {
        equipped,
        onGround
    };
    Status status;

    Gun(const std::string Name, const sf::Vector2f pos);
    Gun();

    void setStatus(Status newStatus, sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
    //void drawEquipped(sf::RenderWindow &window, const sf::Vector2f playerPos);
    //void drawOnGround(sf::RenderWindow &window);

    //void move(const sf::Vector2f offset);
    void attachToPlayer(const sf::Vector2f position);
    void pointAt(const sf::Vector2i position);

    void handleFiring();
    void updateFireTick();
};

#endif // GUN_H_INCLUDED
