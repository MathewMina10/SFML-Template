#include "player.h"
#include "Platforms.h"
#include"Score.h"
#include <cmath>
anim a;
//------------------------------------- Player -------------------------------------------------------//
void playerinfo(player& p) {
    p.body.setSize(Vector2f(28.f, 28.f)); //Character Size
    p.body.setFillColor(Color::Transparent);
    p.body.setOutlineThickness(0.25);
    p.body.setOutlineColor(Color::Green);
    p.body.setPosition(390.f, 540.f);
    p.velocity = Vector2f(0.f, 0.f);
    p.gravity = 2600.f;
    p.movespeed = 2900.f;
    p.jumppower = -700.f;
    p.maxspeed = 700.f;
    p.friction = 0.90f;
    p.isonground = false;
    p.jumphold = false;
    p.inair = true;
    p.platformspassed = 0;
}

//--------------------------------

void playermovement(player& p, float dt)
{
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        p.velocity.x += p.movespeed * dt;
        a.ismoving = 1;
        p.body.setScale(1, 1);
    }
    else if (Keyboard::isKeyPressed(Keyboard::A)) {
        p.velocity.x -= p.movespeed * dt;
        a.ismoving = 1;
        p.body.setScale(-1, 1);
    }
    else {
        float slowdown = 1.f - (2.2f * dt);
        if (slowdown < 0) slowdown = 0;

        p.velocity.x *= slowdown;
    }

    // jump
    if (Keyboard::isKeyPressed(Keyboard::Space) && p.isonground)
    {
        float speedFactor = fabs(p.velocity.x) / p.maxspeed;
        speedFactor = min(speedFactor, 1.f);
        float jumpBoost = 1.f + speedFactor * 0.8f;
        if (p.lastland < 0.15f) {
            jumpBoost *= 1.2f;     // jumpboost
        }
        p.velocity.y = p.jumppower * jumpBoost;
        p.isonground = false;
        p.justlanded = false;
        a.isjumping = true;
        p.platformspassed = 0;
    }
}

//--------------------------------

void playerphysics(player& p, float dt)
{
    if (p.velocity.x > p.maxspeed) p.velocity.x = p.maxspeed;
    if (p.velocity.x < -p.maxspeed) p.velocity.x = -p.maxspeed;

    p.velocity.y += p.gravity * dt;

    if (p.velocity.y > 0)
        p.velocity.y += p.gravity * 1.2f * dt;

    if (p.velocity.y > 950.f)
        p.velocity.y = 950.f;
    if (!p.isonground)
    {
        p.inair = true;
    }
}

//--------------------------------

void playermove(player& p, float dt) {
    p.body.move(p.velocity.x * dt, p.velocity.y * dt);
}

//--------------------------------

void playerdraw(player& p, RenderWindow& window) {
    window.draw(p.body);
}

//--------------------------------collision----------------------------------------------------//

void collision(player& p, Platform platforms[]) {

    p.isonground = false;
    float playerW = p.body.getGlobalBounds().width;
    float playerH = p.body.getGlobalBounds().height;
    float px = p.body.getPosition().x;
    float py = p.body.getPosition().y;
    /////// walls
    if (px < 90)
    {
        p.body.setPosition(90.f, py);
        p.velocity.x = fabs(p.velocity.x) * 0.8f; // gets a little push
    }

    if (px + playerW > 710.f)
    {
        p.body.setPosition(710.f - playerW, py);
        p.velocity.x = -fabs(p.velocity.x) * 0.8f; //gets a little push
    }
    /////////////////ground
    if (py + playerH > 570) {
        p.body.setPosition(px, 570 - playerH);
        p.velocity.y = 0;
        p.isonground = true;
    }


    // platforms
    if (p.velocity.y >= 0)
    {
        FloatRect feet(px + 4.f, py + playerH - 2.f, playerW - 8.f, 6.f);
        for (int i = 0; i < PLATFORM_COUNT; i++)
        {
            FloatRect plat = platforms[i].sprite.getGlobalBounds();
            if (p.inair && !platforms[i].counted)
            {
                if (p.body.getPosition().y < plat.top)
                {
                    p.platformspassed++;
                    platforms[i].counted = true;
                }
            }




            if (feet.intersects(plat))
            {
                p.body.setPosition(p.body.getPosition().x, plat.top - playerH + 1.f);

                p.velocity.y = 0;
                p.isonground = true;

                if (p.inair)
                {
                    p.justlanded = true;
                    p.lastland = 0.f;
                }

                p.inair = false;
                break;
            }
        }
    }
}

//--------------------------------Animation---------------------------------------------------//

void start(anim& g) {

    g.idle.loadFromFile("idle.png");
    g.moving.loadFromFile("moving.png");
    g.jumping.loadFromFile("jump.png");
    g.Jumpbsss.loadFromFile("Jampbass.png");
    g.fall.loadFromFile("Falling.png");

    g.mary.setTexture(g.idle); // مهم

    g.mary.setOrigin(24.f, 28.f);
    g.mary.setScale(1.6f, 1.6f);
    g.mary.setRotation(0.f);

    g.animTimer = 0;
    g.animSpeed = 0.12f;
    g.fallindex = 0;
    g.sakinindix = 0;
    g.movingindix = 0;
}

//--------------------------------

void update(anim& g, player& p, float dt) {

    g.animTimer += dt;

    g.ismoving = (abs(p.velocity.x) > 0.1f);
    g.isjumping = !p.isonground;


    if (g.animTimer >= g.animSpeed) {
        //falling
        if (p.velocity.y > 1.f) {
            g.mary.setTexture(g.fall);
            g.mary.setTextureRect(IntRect(g.fallindex * 57, 0, 57, 58));
            g.fallindex = (g.fallindex + 1) % 2;
        }
        // jumping
        else if (g.isjumping && g.ismoving) {
            g.mary.setTexture(g.jumping);
            g.mary.setTextureRect(IntRect(g.jumpingindix * 49, 0, 49, 61));
            g.jumpingindix = (g.jumpingindix + 1) % 3;

        }
        // jump upward
        else if (g.isjumping) {
            g.mary.setTexture(g.Jumpbsss);
            g.mary.setTextureRect(IntRect(0, 0, 49, 61));
        }
        //moving
        else if (g.ismoving) {
            g.mary.setTexture(g.moving);
            g.mary.setTextureRect(IntRect(g.movingindix * 50, 0, 50, 54));
            g.movingindix = (g.movingindix + 1) % 4;
        }
        //idle
        else {
            g.mary.setTexture(g.idle);
            g.mary.setTextureRect(IntRect(g.sakinindix * 49, 0, 49, 56));
            g.sakinindix = (g.sakinindix + 1) % 4;
        }

        g.animTimer = 0;
    }
    const float PLAYER_SCALE = 1.6f;

    if (p.velocity.x < -0.1f)
        g.mary.setScale(-PLAYER_SCALE, PLAYER_SCALE);
    else
        g.mary.setScale(PLAYER_SCALE, PLAYER_SCALE);
    g.mary.setPosition(p.body.getPosition().x, p.body.getPosition().y - 10);
}