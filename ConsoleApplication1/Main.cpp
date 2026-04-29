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
int main()
{
    const float windowWidth = 800;
    const float windowHeight = 600;
    View view(FloatRect(0, 0, windowWidth, windowHeight));
    Camera camera;
    anim a;
    start(a);
    srand(static_cast<unsigned>(time(0))); //random floors
    // window stuff
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Icy Tower", Style::Titlebar | Style::Close | Style::Resize);
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
    while (window.isOpen())
    {
        //deltatime
        p.dt = clock.restart().asSeconds();
        p.lastland += p.dt;

        //Event
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }
        //Update
        playermovement(p, p.dt);
        playerphysics(p, p.dt);
        playermove(p, p.dt);
        collision(p, platformlist);
        update(a, p, p.dt);


        //Platforms 

        //camera stuff

        camera.camera_control(p.body.getPosition().y, p.dt);
        float cameraBottom = camera.view.getCenter().y + 300.f;
        if (p.body.getPosition().y > cameraBottom + 50.f)
        {
            window.close(); // the game is over 
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
        window.display();
    }
    // end of application
    return 0;
}