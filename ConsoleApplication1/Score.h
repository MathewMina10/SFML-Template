#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
struct ScoreSystem
{
    int score;
    int combo;
    int levelindex;
    int highscore;
    float combotimer;
    float combomaxtime;
    Font font;
    Text scoreText;
    float beginY;
    float restY;
    float lastY;
    bool initialized;
    Text finalscoretext;
    Text finalhighscoretext;
    ScoreSystem();
    void init();
    void update(float playerY);
    void draw(RenderWindow& window);
    void addcombo(int platformspassed);
    void loadhighscore();
    void savehighscore();
    void checkAndSave();
    void scorereveal(Text& finalscoretext, Text& finalhighscoretext, Font& font, int score, int highScore);
};