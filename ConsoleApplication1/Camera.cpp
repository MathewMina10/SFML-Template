#include "Camera.h"
#include<iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "Camera.h"

void Camera::camera_stuff(float width, float height)
{
    basespeed = 45.f;
    cameraSpeed = basespeed; // the basic camera
    maxcameraspeed = 150.f; // the fastest camera 
    startY = height / 2.f;
    gamestarted = false;
    view.setSize(width, height);
    view.setCenter(width / 2.f, height / 2.f);

    highestY = height / 2.f;
    deadZone = 170.f;
}

void Camera::camera_control(float playerY, float dt)
{
    float currentY = view.getCenter().y;

    float triggerLine = currentY - deadZone;

    if (!gamestarted && playerY < triggerLine)
    {
        gamestarted = true;
    }

    if (gamestarted)
    {
        currentY -= cameraSpeed * dt;
    }

    if (playerY < triggerLine)
    {
        float targetY = playerY + deadZone;
        currentY += (targetY - currentY) * 5.f * dt;
    }
    if (playerY < highestY)
    {
        highestY = playerY;
    }

    // how much player climbed
    float climbed = startY - highestY;

    // every 25 floors --> increase speed
    int level = climbed / 800.f;

    cameraSpeed = basespeed + level * 10.f;

    if (cameraSpeed > maxcameraspeed)
        cameraSpeed = maxcameraspeed;
    view.setCenter(view.getCenter().x, currentY);
}