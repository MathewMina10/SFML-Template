#include "game.h"
#include<iostream>
#include<vector>
#include "player.h"
#include "Platforms.h"
#include "Camera.h"
#include "Menu.h"
#include "Score.h"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
const int back_to_menu = 0;
const int restart = 1;
int selecteditem = 0;
int rungame(RenderWindow& window) {
    bool ispaused = false;
    bool isdead = false;
    const float windowWidth = 800;
    const float windowHeight = 600;
    //score
    ScoreSystem score;
    score.init();
    RenderTexture blurtexture;
    blurtexture.create(windowWidth, windowHeight); // blur for pause menu
    Sprite blursprite;


    View view(FloatRect(0, 0, windowWidth, windowHeight));
    Camera camera;
    anim a;
    start(a);
    srand(static_cast<unsigned>(time(0))); //random floors
    // window stuff
    Event event;
    player p;
    camera.camera_stuff(windowWidth, windowHeight);
    playerinfo(p);

    // background
    Texture backgroundTexture, wallTexture, floorTexture, platformTexture;
    Sprite backgroundSprite, leftWall, rightWall, floor;
    initBackground(backgroundTexture, backgroundSprite, windowWidth);

    //walls
    initWalls(wallTexture, leftWall, rightWall, windowWidth, windowHeight);


    //platforms 
    const int PLATFORM_COUNT = 200;
    Platform platformlist[PLATFORM_COUNT];
    initPlatforms(platformlist, platformTexture, windowWidth);
    initFloor(floorTexture, floor, windowWidth, windowHeight); //first floor
    Clock clock;

    /////// Death menu 
    Texture deathTexture;
    deathTexture.loadFromFile("entername (1).png");

    Sprite deathSprite;
    deathSprite.setTexture(deathTexture);
    deathSprite.setPosition(200, 100);

    Font font;
    font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf");

    Text playAgain, mainMenu;

    playAgain.setFont(font);
    playAgain.setString("Play Again");
    playAgain.setCharacterSize(30);
    playAgain.setPosition(300, 150);

    mainMenu.setFont(font);
    mainMenu.setString("Main Menu");
    mainMenu.setCharacterSize(30);
    mainMenu.setPosition(300, 230);

    // music inside the game 
    Music gameMusic;
    gameMusic.openFromFile("backgmusic.ogg"); //game music
    gameMusic.play();
    gameMusic.setLoop(true);


    //game loop
    bool running = true;
    while (running)
    {
        //deltatime
        if (!ispaused && !isdead) {
            p.dt = clock.restart().asSeconds();
            p.lastland += p.dt;
        }
        else {
            clock.restart();
        }

        //Event
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                running = false;
            }
            if (event.type == Event::KeyPressed) {
                if (!ispaused && !isdead) {
                    if (event.key.code == Keyboard::Escape)
                        ispaused = true; //first ESC ---> pause 
                }
                else {
                    if (event.key.code == Keyboard::Escape)
                        running = false; //second ESC ---> Exit
                    else
                        ispaused = false; //any other button ----> resume
                }

            }
            // death menu
            if (isdead && event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Up)
                {
                    selecteditem--;
                    if (selecteditem < 0)
                        selecteditem = 1;
                }

                if (event.key.code == Keyboard::Down)
                {
                    selecteditem++;
                    if (selecteditem > 1)
                        selecteditem = 0;
                }

                if (event.key.code == Keyboard::Enter)
                {
                    if (selecteditem == 0)
                        return restart;

                    if (selecteditem == 1)
                        return back_to_menu;
                }
            }
        }



        //Update
        if (!ispaused && !isdead) {
            playermovement(p, p.dt);
            playerphysics(p, p.dt);
            playermove(p, p.dt);
            collision(p, platformlist);
            if (p.justlanded)
            {
                score.addcombo(p.platformspassed);
                p.platformspassed = 0;
                p.justlanded = false;
            }
            update(a, p, p.dt);
            score.update(p.body.getPosition().y);

        }

        //Platforms 

        //camera stuff
        if (!ispaused && !isdead)
            camera.camera_control(p.body.getPosition().y, p.dt);
        float cameraBottom = camera.view.getCenter().y + 300.f;
        if (!ispaused && !isdead) {
            if (p.body.getPosition().y > cameraBottom + 50.f)
            {
                isdead = true; // the game is over
                selecteditem = 0;
            }
        }

        // death menu
        if (selecteditem == 0)
        {
            playAgain.setFillColor(Color::Yellow);
            mainMenu.setFillColor(Color::Black);
        }
        else
        {
            playAgain.setFillColor(Color::Black);
            mainMenu.setFillColor(Color::Yellow);
        }
        //Render
        window.clear();
        window.setView(window.getDefaultView());
        //draw your game 
        window.draw(backgroundSprite);
        window.draw(leftWall);
        window.draw(rightWall);
        window.setView(camera.view);
        for (int i = 0; i < PLATFORM_COUNT; i++)
            window.draw(platformlist[i].sprite);
        window.draw(floor);
        window.draw(a.mary);
        window.setView(window.getDefaultView());
        //pause menu 
        if (ispaused) {
            blurtexture.clear();

            // draw background (default view)
            blurtexture.setView(window.getDefaultView());
            blurtexture.draw(backgroundSprite);
            blurtexture.draw(leftWall);
            blurtexture.draw(rightWall);

            // draw world (camera view)
            blurtexture.setView(camera.view);
            for (int i = 0; i < PLATFORM_COUNT; i++)
                blurtexture.draw(platformlist[i].sprite);

            blurtexture.draw(floor);
            blurtexture.draw(a.mary);

            blurtexture.display();

            blursprite.setTexture(blurtexture.getTexture());

            // fake blur effect
            blursprite.setScale(1.02f, 1.02f);
            blursprite.setColor(Color(255, 255, 255, 200));

            window.setView(window.getDefaultView());
            window.draw(blursprite);


            RectangleShape overlay(Vector2f(windowWidth, windowHeight));
            overlay.setFillColor(Color(0, 0, 0, 120));
            window.draw(overlay);

            Font font;
            bool loaded = false;
            if (!loaded)
            {
                font.loadFromFile("HalloweenSlimePersonalUse-4B80D.otf");
                loaded = true; // to prevent from repetition
            }

            Text pauseText;
            pauseText.setFont(font);
            pauseText.setString("DO YOU REALLY WANT TO EXIT ?\nPRESS ANY KEY TO RESUME\nPRESS ESC TO EXIT");
            pauseText.setCharacterSize(30);
            pauseText.setFillColor(Color::White);

            // center it (better look)
            FloatRect textRect = pauseText.getLocalBounds();
            pauseText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
            pauseText.setPosition(windowWidth / 2.f, windowHeight / 2.f);

            window.draw(pauseText);
        }
        ///////////////death menu
        if (isdead)
        {
            window.setView(window.getDefaultView());
            window.draw(deathSprite);
            window.draw(playAgain);
            window.draw(mainMenu);
        }
        //////score draw
        window.setView(window.getDefaultView());
        score.draw(window);
        window.display();
    }
    // end of application
    return back_to_menu;
}