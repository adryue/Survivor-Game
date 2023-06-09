#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED

#include "CommonDef.h"
#include "gun.h"
#include "player.h"
#include "Projectile.h"
#include "Bullet.h"

//There is a global vector that stores all the bullets currently fired
//This is to make collision detection with objects easier
//Each bullet has an owner (the person that originally fired it)

//std::vector<Bullet> bullets;

void createProjectile(Projectile* projectile);

//these functions are necessary because I can't create the guns vector in this header file
Gun* getGun(const int index);
void addGun(Gun *gun);
void removeGun(const int index);
int numGuns();

ScreenName playScreen(sf::RenderWindow &window);

#endif // PLAY_H_INCLUDED
