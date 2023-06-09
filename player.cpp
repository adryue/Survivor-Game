#include "math.h"
#include "play.h"
#include "player.h"

const int PLAYER_INVENTORY_SIZE = 3;

Player::Player()
{
    hitbox.setRadius(PLAYER_SIZE);
    hitbox.setOrigin(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    hitbox.setPosition(sf::Vector2f(WIN_X_LEN / 2, WIN_Y_LEN / 2));
    hitbox.setFillColor(sf::Color::Red);

    currentItem = 0;
    for (int i = 0; i < PLAYER_INVENTORY_SIZE; i++)
    {
        inventory[i] = nullptr;
    }
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(hitbox);
    if (inventory[currentItem] == nullptr)
    {
        //draw hands
    }
    else
    {
        inventory[currentItem]->draw(window);
    }
}

void Player::update(const sf::Vector2i mouse) //handles movement, firing, equipping weapons
{
    //switching selected gun
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) currentItem = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) currentItem = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) currentItem = 2;

    //movement
    sf::Vector2f playerMovement;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) playerMovement.y -= PLAYER_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) playerMovement.x -= PLAYER_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) playerMovement.y += PLAYER_SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) playerMovement.x += PLAYER_SPEED;
    move(playerMovement);

    //equip/unequip
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) equip();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) unequip();

    pointAt(mouse);
    updateFiring();
}

void Player::pointAt(const sf::Vector2i position) //position is usually the mouse
{
    //point the item at the position
    if (inventory[currentItem] == nullptr)
    {
        //make hands point
    }
    else
    {
        inventory[currentItem]->pointAt(position);
    }
}

void Player::updateFiring()
{
    if (inventory[currentItem] == nullptr)
    {
        //make hands fire
    }
    else
    {
        inventory[currentItem]->handleFiring();
    }
}

void Player::move(const sf::Vector2f offset)
{
    hitbox.move(offset);

    //move the current item
    if (inventory[currentItem] == nullptr)
    {
        //move hands
    }
    else
    {
        //inventory[currentItem]->move(offset);
        inventory[currentItem]->attachToPlayer(hitbox.getPosition());
    }
}

sf::Vector2f Player::getPosition()
{
    return hitbox.getPosition();
}

void Player::equip() //checks if there are guns nearby and equips one of them (if there are available slots)
{
    for (int i = 0; i < numGuns(); i++)
    {
        //if the gun is within pickup range
        if ((getGun(i)->groundPosition.x - hitbox.getPosition().x) * (getGun(i)->groundPosition.x - hitbox.getPosition().x) +
            (getGun(i)->groundPosition.y - hitbox.getPosition().y) * (getGun(i)->groundPosition.y - hitbox.getPosition().y) <=
            GUN_PICKUP_RANGE * GUN_PICKUP_RANGE)
        {
            //pick up the gun in the selected slot -
            if (inventory[currentItem] == nullptr)
            {
                inventory[currentItem] = getGun(i);
                inventory[currentItem]->setStatus(Gun::Status::equipped, hitbox.getPosition());
                removeGun(i);
                break;
            }
            for (int g = 0; g < 3; g++) //- or first available slot
            {
                if (inventory[g] == nullptr)
                {
                    inventory[g] = getGun(i);
                    inventory[g]->setStatus(Gun::Status::equipped, hitbox.getPosition());
                    removeGun(i);
                    break;
                }
            }
            break;
        }
    }
}

void Player::unequip()
{
    if (inventory[currentItem] != nullptr)
    {
        //inventory[currentItem]->groundPosition = hitbox.getPosition();
        inventory[currentItem]->setStatus(Gun::Status::onGround, hitbox.getPosition());
        addGun(inventory[currentItem]);
        inventory[currentItem] = nullptr;
    }
}
