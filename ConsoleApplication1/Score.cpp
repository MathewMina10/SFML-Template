#include "Score.h"
#include "Player.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;
//=====================================================================SCORE SYSTEM (Marly Hazem)  =======================================================//

             //=============================Score info====================//
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

//=============================Score Font====================//

void ScoreSystem::init()
{
    font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    initialized = false;
}

//=============================Score Update====================//

void ScoreSystem::update(float playerY)
{
    combotimer += 0.016f;


    if (!initialized)
    {
        lastY = playerY;
        initialized = true;
    }

    // when the player moves up
    if (playerY < lastY)
    {
        float delta = lastY - playerY;
        score += 1;
    }

    lastY = playerY;

    // reset the highscore
    if (score > highscore)
        highscore = score;

    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Score: " + to_string(score) + "\nHigh Score: " + to_string(highscore) + "\nCombo: " + to_string(combo));
}

//=============================Score Combo====================//

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

//=============================HighScore System====================//

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

//=============================Score Reveal====================//


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