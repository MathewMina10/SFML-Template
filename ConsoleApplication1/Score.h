#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class ScoreSystem
{
private:
    int score;
    int combo;
    int highscore;
    float combotimer;
    float combomaxtime;
    Font font;
    Text scoreText;
    float beginY;
    float restY;
    bool initialized;

public:
    ScoreSystem();

    void init();
    void update(float playerY);
    void draw(RenderWindow& window);
    void addcombo(int platformspassed);
    void loadhighscore();
    void savehighscore();
    void updatehighscore();
};