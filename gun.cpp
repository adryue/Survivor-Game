#include <fstream>
#include <cmath>
#include "gun.h"
#include "play.h"
#include "projectile.h"
#include "bullet.h"

Gun::Gun(const std::string Name, const sf::Vector2f pos)
{
    //extract all the data from Data and Images folders
    //the filenames are the exact same as Name

    equippedTexture.loadFromFile("Data/Guns/" + Name + ".png");
    groundTexture.loadFromFile("Data/Guns/" + Name + "Ground.png");
    sprite.setTexture(equippedTexture);
    sprite.setOrigin(sf::Vector2f(-PLAYER_SIZE, (float)equippedTexture.getSize().y / 2));
    name = Name;
    groundPosition = pos;

    setStatus(Status::onGround, pos);

    std::ifstream fin("Data/Guns/" + Name + ".txt");
    fin >> fireSpeed;
    fin >> capacity;
    fin >> bulletType;
    fin.close();

    currentTick = 0;
}

Gun::Gun()
{
    equippedTexture.loadFromFile("Images/Guns/Gun1.png");
    sprite.setTexture(equippedTexture);
    sprite.setOrigin(sf::Vector2f(0.0, (float)equippedTexture.getSize().y / 2));
    sprite.setPosition(WIN_X_LEN / 2, WIN_Y_LEN / 2);
    name = "Gun1";

    currentTick = 0;
    fireSpeed = BULLET_DEFAULT_FIRE_SPEED;
}

/*void Gun::move(const sf::Vector2f offset)
{
    sprite.move(offset);
}*/
void Gun::attachToPlayer(const sf::Vector2f position)
{
    sprite.setPosition(position);
}
void Gun::setStatus(Status newStatus, sf::Vector2f pos)
{
    status = newStatus;
    switch (newStatus)
    {
    case Status::equipped:
        sprite.setTexture(equippedTexture);
        sprite.setOrigin(sf::Vector2f(-PLAYER_SIZE, (float)equippedTexture.getSize().y / 2));
        sprite.setPosition(pos);
        break;
    case Status::onGround:
        //when putting the weapon on the ground, the base of the weapon is at the center of the player
        sf::Vector2f newPosition;
        newPosition.x = pos.x + PLAYER_SIZE * std::cos(sprite.getRotation() * M_PI / 180);
        newPosition.y = pos.y + PLAYER_SIZE * std::sin(sprite.getRotation() * M_PI / 180);

        sprite.setTexture(groundTexture);
        sprite.setOrigin(sf::Vector2f((float)equippedTexture.getSize().x / 2, (float)equippedTexture.getSize().y / 2));
        sprite.setPosition(newPosition);
        groundPosition = newPosition;
        break;
    }
}
void Gun::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}
/*void Gun::drawEquipped(sf::RenderWindow &window, const sf::Vector2f playerPos)
{
    //move it to the player
    window.draw(sprite);
}
void Gun::drawOnGround(sf::RenderWindow &window)
{
    //move it to the ground
    window.draw(sprite);
}*/


void Gun::pointAt(const sf::Vector2i position)
{
    float xDiff = position.x - (WIN_X_LEN / 2);
    float yDiff = position.y - (WIN_Y_LEN / 2);
    float degree = std::atan(yDiff / xDiff) / M_PI * 180;
    if (xDiff < 0.0)
    {
        degree += 180.0;
    }
    rotation = degree;
    sprite.setRotation(degree);
}

void Gun::handleFiring()
{
    updateFireTick();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (currentTick == 0)
        {
            currentTick = fireSpeed;
            //spawn a new bullet at the tip of the gun
            sf::Vector2f newPosition(sprite.getPosition());
            newPosition.x += (PLAYER_SIZE + equippedTexture.getSize().x) * std::cos(rotation * M_PI / 180);
            newPosition.y += (PLAYER_SIZE + equippedTexture.getSize().x) * std::sin(rotation * M_PI / 180);

            createProjectile(new Bullet("Bullet1", newPosition, rotation, Bullet::Owner::player));
        }
    }
}

void Gun::updateFireTick()
{
    if (currentTick > 0)
    {
        currentTick--;
    }
}
