#pragma once
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "Camera.h"
using namespace std;
using namespace sf;

//=====================================================================Player=======================================================//


struct Platform;
struct player
{
    RectangleShape body;
    Vector2f velocity;
    int platformspassed;
    int lastplatformindex;
    float gravity;
    float movespeed;
    float jumppower;
    float jumpboost;
    float lastland;
    bool isonground;
    bool justlanded;
    bool jumphold;
    bool gamestarted;
    bool inair;
    bool fallPlayed = false;
    float dt;
    float maxspeed;
    float friction;
    float stepTimer;
    float stepDelay;
};
void playerinfo(player& player);
void playermovement(player& player, float dt);
void playerphysics(player& player, float dt);
void playermove(player& player, float dt);
void playerdraw(player& player, RenderWindow& window);
void collision(player& p, Platform platformlist[]);
void loadSounds(player& p); // sound


//=====================================================================Animation=======================================================//


struct anim {
    Sprite mary;
    Texture idle, moving, jumping, fall, Jumpbsss;
    float animTimer;
    float animSpeed;
    bool isjumping;
    bool ismoving;
    int sakinindix;
    int movingindix;
    int jumpingindix;
    int fallindex;
    Clock dt_clock;
};
void start(anim& g);
void update(anim& g, player& p, float dt);