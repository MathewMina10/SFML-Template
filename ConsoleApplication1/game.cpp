#include "game.h"
#include<iostream>
#include<vector>
#include "player.h"
#include "Platforms.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
using namespace std;
using namespace sf;
void rungame(RenderWindow& window) {
    bool ispaused = false;
    const float windowWidth = 800;
    const float windowHeight = 600;


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
    //game loop
    bool running = true;
    while (running)
    {
        //deltatime
        if (!ispaused) {
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
                if (!ispaused) {
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
        }
        //Update
        if (!ispaused) {
            playermovement(p, p.dt);
            playerphysics(p, p.dt);
            playermove(p, p.dt);
            collision(p, platformlist);
            update(a, p, p.dt);
        }

        //Platforms 

        //camera stuff
        if (!ispaused)
            camera.camera_control(p.body.getPosition().y, p.dt);
        float cameraBottom = camera.view.getCenter().y + 300.f;
        if (!ispaused) {
            if (p.body.getPosition().y > cameraBottom + 50.f)
            {
                running = false; // the game is over 
            }
        }

        // 
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
        window.display();
    }
    // end of application
}