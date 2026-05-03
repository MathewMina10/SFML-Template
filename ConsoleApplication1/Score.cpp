#include "Score.h"
#include "Player.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;
ScoreSystem::ScoreSystem()
{
    score = 0;
    combo = 0;
    combotimer = 0.f;
    combomaxtime = 1.0f;
    initialized = false;
}

void ScoreSystem::init()
{
    beginY = 0.f;
    // استخدمنا خط من الويندوز علشان يشتغل فورًا
    if (!font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf"))
    {
        std::cout << "Font Error\n";
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
}

void ScoreSystem::update(float playerY)
{
    combotimer += 0.016f;
    // save starting position ONCE
    if (!initialized)
    {
        restY = playerY;
        beginY = playerY;
        initialized = true;
    }
    if (playerY < beginY)
    {
        beginY = playerY;
    }
    // calculate how much player moved UP
    float delta = restY - beginY;

    int baseScore = (int)(delta / 10);
    score = baseScore * (combo > 0 ? combo : 1);

    scoreText.setString("Score: " + to_string(score));
    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Score: " + to_string(score) + "\nCombo: " + to_string(combo));
}
//combo
void ScoreSystem::addcombo(int platformsPassed)
{
    if (platformsPassed >= 2)
    {
        combo = platformsPassed;
        score += combo * 20;
    }
    else
    {
        combo = 0;
    }
}

void ScoreSystem::loadhighscore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highscore;
        file.close();
    }
    else {
        highscore = 0;
    }
}


void ScoreSystem::draw(RenderWindow& window)
{
    window.draw(scoreText);
}