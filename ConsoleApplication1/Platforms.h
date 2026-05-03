#pragma once
#include<iostream>
#include<vector>
#include "player.h"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
const int PLATFORM_COUNT = 100;
struct Platform
{
	Sprite sprite;
	bool counted = false; // for platforms that passed 
};
//-------------------------------------------------------  FUNCTIONS------------------------------------------------------------// 
void initBackground(Texture& backgroundTexture, Sprite& backgroundSprite, float windowWidth);
void initWalls(Texture& wallTexture, Sprite& leftWall, Sprite& rightWall, float windowWidth, float windowHeight);
void initFloor(Texture& floorTexture, Sprite& floor, float windowWidth, float windowHeight);
void initPlatforms(Platform platforms[], Texture& platformTexture, float windowW);