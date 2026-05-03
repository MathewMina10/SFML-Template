#pragma once
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
struct Platform;
struct player
{
    RectangleShape body;
    Vector2f velocity;
    int platformspassed;
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
    float dt;
    float maxspeed = 0;
    float friction = 0;
};
void playerinfo(player& player);
void playermovement(player& player, float dt);
void playerphysics(player& player, float dt);
void playermove(player& player, float dt);
void playerdraw(player& player, RenderWindow& window);
void collision(player& p, Platform platformlist[]);

//--------------------------------------------------Animation--------------------------------------//

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