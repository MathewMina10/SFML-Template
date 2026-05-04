#include <SFML/Graphics.hpp>
#include <iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>
#include <SFML/Audio.hpp>
#include "menu.h"
#include "player.h"
#include "Platforms.h"
#include "Camera.h"
#include "game.h"
//=====================================================================Main Menu (Mariham Merzek)  ====================================================================//

using namespace sf;
using namespace std;
enum GameState { MENU, LEVELS, GAME, OPTIONS };

float windowWidth = 800.0f;
float windowHeight = 600.0f;
int currentLevel = 0;

sf::Music bgMusic;

int main()
{
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Icy Tower", Style::Titlebar | Style::Close | Style::Resize);

    window.setKeyRepeatEnabled(false);

    // ================= IMAGE (Texture & Sprite) =================
    sf::Texture texture;
    sf::Sprite sprite;

    if (!texture.loadFromFile("heads.png"))
        cout << "Image error\n";

    sprite.setTexture(texture);

    // Animation setup
    int currentFrame = 0;
    int totalFrames = 3;
    float frameWidth = 211.f;
    float frameHeight = 258.f;

    sf::Clock animationClock;
    float animationSpeed = 0.3f;

    sprite.setTextureRect(IntRect(0, 0, (int)frameWidth, (int)frameHeight));
    sprite.setPosition(500.f, 50.f);

    // ================= MENU =================
    Menu menu(windowWidth, windowHeight);

    // ================= MUSIC =================
    if (!bgMusic.openFromFile("ori music.ogg"))
        cout << "Music error\n";

    bgMusic.setLoop(true);
    bgMusic.setVolume(menu.getMusic());
    bgMusic.play();

    // ================= FONT =================
    Font font;
    if (!font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf"))
        cout << "Font error\n";

    // ================= LEVELS =================
    Text levels[3];
    string lvlNames[3] = { "Level 1", "Level 2", "Level 3" };
    int selectedLevel = 0;

    for (int i = 0; i < 3; i++)
    {
        levels[i].setFont(font);
        levels[i].setString(lvlNames[i]);
        levels[i].setCharacterSize(40);
        levels[i].setPosition(520, 350 + i * 60);
        levels[i].setFillColor(Color::Black);
    }

    // ================= GAME TEXT =================
    Text text;
    text.setFont(font);
    text.setString("GAME STARTED!");
    text.setCharacterSize(40);
    text.setFillColor(Color::White);
    text.setPosition(350, 200);

    // ================= STATE =================
    GameState state = MENU;

    // ================= GAME LOOP =================
    while (window.isOpen())
    {
        Event event;

        // ================= INPUT =================
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // ================= MENU =================
            if (state == MENU)
            {
                if (bgMusic.getStatus() != sf::Music::Playing)
                    bgMusic.play();

                menu.HandleInput(event);

                if (menu.isPlaySelected())
                {
                    state = LEVELS;
                    menu.resetPlay();
                }

                if (menu.isOptionsOpen())
                    state = OPTIONS;

                if (menu.shouldExit())
                    window.close();
            }

            // ================= LEVELS =================
            else if (state == LEVELS)
            {
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        selectedLevel--;
                        menu.playClick();
                    }

                    if (event.key.code == Keyboard::Down)
                    {
                        selectedLevel++;
                        menu.playClick();
                    }

                    if (selectedLevel < 0) selectedLevel = 2;
                    if (selectedLevel > 2) selectedLevel = 0;

                    if (event.key.code == Keyboard::Enter)
                    {
                        menu.playClick();
                        bgMusic.stop();
                        currentLevel = selectedLevel;
                        state = GAME;
                    }

                    if (event.key.code == Keyboard::Escape)
                        state = MENU;
                }
            }

            // ================= GAME =================
            else if (state == GAME)
            {
                if (event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Escape)
                {
                    state = LEVELS;
                }
            }

            // ================= OPTIONS =================
            else if (state == OPTIONS)
            {
                menu.HandleInput(event);

                if (event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Escape)
                {
                    menu.closeOptions();
                    menu.resetMenu();
                    state = MENU;
                }

                if (menu.shouldBackToMenu())
                {
                    state = MENU;
                    menu.resetBackToMenu();
                }
            }
        }

        bgMusic.setVolume(menu.getMusic());

        // ================= ANIMATION UPDATE =================
        if (state == MENU)
        {
            if (animationClock.getElapsedTime().asSeconds() > animationSpeed)
            {
                currentFrame = (currentFrame + 1) % totalFrames;

                sprite.setTextureRect(IntRect(
                    currentFrame * (int)frameWidth, 0, (int)frameWidth, (int)frameHeight));

                animationClock.restart();
            }
        }

        // ================= DRAW =================
        window.clear();

        if (state == MENU)
        {
            menu.draw(window);

            if (!menu.isInstructionsOpen() && !menu.isOptionsOpen() && !menu.isCreditsOpen())
            {
                window.draw(sprite);
            }
        }
        else if (state == LEVELS)
        {
            menu.drawBackground(window);

            for (int i = 0; i < 3; i++)
            {
                if (i == selectedLevel)
                    levels[i].setFillColor(Color::Yellow);
                else
                    levels[i].setFillColor(Color::Black);

                window.draw(levels[i]);
            }
        }
        else if (state == GAME)
        {
            int result = rungame(window, currentLevel);

            if (result == 1)
                state = GAME;
            else
                state = MENU;
        }
        else if (state == OPTIONS)
        {
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}