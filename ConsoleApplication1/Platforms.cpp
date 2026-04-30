#include "Platforms.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <cstdlib>   // for rand()
#include <ctime>
#include<algorithm>
using namespace std;
using namespace sf;
//---------------------------------  BACKGROUND-------------------------------------------------// 
void initBackground(Texture& backgroundTexture, Sprite& backgroundSprite, float windowWidth)
{
    backgroundTexture.loadFromFile("BackGround game1.png");
    backgroundTexture.setRepeated(true);
    backgroundTexture.setSmooth(false);

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(IntRect(0, 0, windowWidth, 8000));

    backgroundSprite.setScale(windowWidth / backgroundTexture.getSize().x, 1.0f);
}
//------------------------------------------------  WALLS ------------------------------------------//
void initWalls(Texture& wallTexture, Sprite& leftWall, Sprite& rightWall, float windowWidth, float windowHeight)
{
    wallTexture.loadFromFile("wall11.png");
    wallTexture.setRepeated(true);
    wallTexture.setSmooth(false);

    float wallWidth = 90.0f;

    leftWall.setTexture(wallTexture);
    rightWall.setTexture(wallTexture);

    float scaleX = wallWidth / wallTexture.getSize().x;
    leftWall.setScale(scaleX, 1);
    rightWall.setScale(scaleX, 1);

    leftWall.setTextureRect(IntRect(0, 0, wallTexture.getSize().x, windowHeight));
    rightWall.setTextureRect(IntRect(0, 0, wallTexture.getSize().x, windowHeight));

    leftWall.setPosition(0, 0);
    rightWall.setPosition(windowWidth - wallWidth, 0);
}

//---------------------------------------------  FLOOR -----------------------------------------------------------// 
void initFloor(Texture& floorTexture, Sprite& floor, float windowWidth, float windowHeight)
{
    floorTexture.loadFromFile("floor.png");
    floor.setTexture(floorTexture);

    float wallWidth = 90.0f;
    float floorWidth = windowWidth - 2 * wallWidth;
    float scaleX = floorWidth / floorTexture.getSize().x;

    floor.setScale(scaleX, 1.0f);

    float floorHeight = floor.getGlobalBounds().height;
    floor.setPosition(wallWidth, windowHeight - floorHeight);
}
//------------------------------------------------  PLATFORMS---------------------------------------------------------//
void initPlatforms(Platform platforms[], Texture& platformTexture, float windowW)
{
    platformTexture.loadFromFile("Stair (3).png");

    float wallWidth = 90.0f;
    float playableWidth = windowW - 2 * wallWidth;

    float previousX = wallWidth + rand() % (int)playableWidth;

    const float verticalSpacing = 125.f; // the distance between the platforms 
    const float maxJumpX = 150.f;
    const float minGap = 60.f;

    for (int i = 0; i < PLATFORM_COUNT; i++)
    {
        platforms[i].sprite.setTexture(platformTexture);

        float scaleX = 0.8f + static_cast<float>(rand()) / RAND_MAX * 1.2f;
        platforms[i].sprite.setScale(scaleX, 1.0f);

        float platformWidth = platformTexture.getSize().x * scaleX;

        float x;

        if (rand() % 2 == 0)
        {
            x = wallWidth + rand() % (int)(playableWidth - platformWidth);
        }
        else
        {
            int direction = (rand() % 2 == 0 ? -1 : 1);
            float dx = direction * (rand() % (int)maxJumpX);

            x = previousX + dx;

            if (abs(x - previousX) < minGap)
                x += (x > previousX ? minGap : -minGap);
        }

        x = max(wallWidth, min(x, windowW - wallWidth - platformWidth));

        float y = 450 - i * verticalSpacing;

        platforms[i].sprite.setPosition(x, y);

        previousX = x;
    }
}