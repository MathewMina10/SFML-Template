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
    highscore = 0;
    levelindex = 0;
    combotimer = 0.f;
    combomaxtime = 1.0f;
    initialized = false;
}

void ScoreSystem::init()
{
    if (!font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf"))
    {
        cout << "Font Error\n";
    }


    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);

    initialized = false; // important
}

void ScoreSystem::update(float playerY)
{
    combotimer += 0.016f;

    // first frame
    if (!initialized)
    {
        lastY = playerY;
        initialized = true;
    }

    // if player moved UP
    if (playerY < lastY)
    {
        float delta = lastY - playerY;
        score += 1;
    }

    lastY = playerY;

    // update highscore LIVE
    if (score > highscore)
        highscore = score;

    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Score: " + to_string(score) + "\nHigh Score: " + to_string(highscore) + "\nCombo: " + to_string(combo));
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

void ScoreSystem::loadhighscore()
{
    string filename = "highscore_level" + to_string(levelindex) + ".txt";

    ifstream file(filename);

    if (file.is_open())
    {
        if (!(file >> highscore))
            highscore = 0;

        file.close();
    }
    else
    {
        highscore = 0;
    }
}


void ScoreSystem::draw(RenderWindow& window)
{
    window.draw(scoreText);
}
//=======================================highscore===============================================//
void ScoreSystem::savehighscore()
{
    string filename = "highscore_level" + to_string(levelindex) + ".txt";

    ofstream file(filename);

    if (file.is_open())
    {
        file << highscore;
        file.close();
    }
}

void ScoreSystem::checkAndSave()
{
    if (score > highscore)
        highscore = score;

    savehighscore();
}
void ScoreSystem::scorereveal(Text& finalscoretext, Text& finalhighscoretext, Font& font, int score, int highScore)
{
    scoreText.setFont(font);
    finalhighscoretext.setFont(font);

    scoreText.setCharacterSize(30);
    finalhighscoretext.setCharacterSize(30);

    scoreText.setFillColor(Color::White);
    finalhighscoretext.setFillColor(Color::White);

    scoreText.setString("Score: " + to_string(score));
    finalhighscoretext.setString("High Score: " + to_string(highScore));

    scoreText.setPosition(260.f, 300.f);
    finalhighscoretext.setPosition(260.f, 350.f);
}