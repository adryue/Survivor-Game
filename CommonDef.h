#ifndef COMMONDEF_H_INCLUDED
#define COMMONDEF_H_INCLUDED

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "gun.h"

enum ScreenName
{
    home,
    play,
    settings,
    lose,
    none
};

extern const int WIN_X_LEN;
extern const int WIN_Y_LEN;
extern const int FRAMERATE;

//extern std::vector<Bullet> bullets;

extern const float PLAYER_SIZE; //radius
extern const float PLAYER_SPEED;
//extern const int PLAYER_INVENTORY_SIZE;

extern const float GUN_PICKUP_RANGE; //how far the player can pick up a gun

extern const float BULLET_DEFAULT_SPEED;
extern const int BULLET_DEFAULT_FIRE_SPEED;
extern const float BULLET_DEFAULT_SIZE; //radius

#endif // COMMONDEF_H_INCLUDED
