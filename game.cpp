#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>

using namespace sf;
using namespace std;

void runGame(sf::RenderWindow& window)
{
    srand(static_cast<unsigned>(time(0)));
    window.setFramerateLimit(60);

    const int platformCount = 15;
    const float platformWidth = 100.f;
    const float platformHeight = 25.f;

    // Platforms
    vector<RectangleShape> plat(platformCount);
    vector<Vector2f> opos(platformCount); // Store positions for scrolling

    for (int i = 0; i < platformCount; ++i)
    {
        plat[i].setSize(Vector2f(platformWidth, platformHeight));
        plat[i].setFillColor(Color::Green);
        float x = rand() % 900; // Keep inside screen width (400 - 60)
        float y = i * (1400 / platformCount); // evenly spaced
        plat[i].setPosition({x, y});
        opos[i] = {x, y};
    }

    // Player
    const float playerRadius = 15.f;
    CircleShape player(playerRadius);
    player.setFillColor(Color::Yellow);
    player.setOrigin({playerRadius, playerRadius});

    float a, b, h = 200; // a = x, b = y
    float da = 0, db = 0;

    // Start player on middle platform 
    int midIndex = platformCount / 2;
    float platformX = plat[midIndex].getPosition().x;
    float platformY = plat[midIndex].getPosition().y;

    a = platformX + platformWidth / 2.f;         // horizontally centered
    b = platformY - playerRadius;                // standing on top


    while (window.isOpen())
    {
        while(auto event=window.pollEvent())
        {
         if (event->is<Event::Closed>())
            {
                window.close();
            }
           }

        // Movement input
        if (Keyboard::isKeyPressed(Keyboard::Key::Right)) a += 3;
        if (Keyboard::isKeyPressed(Keyboard::Key::Left)) a -= 3;

        // Gravity and fall
        db += 0.2f;
        b += db;

        // Game Over if player falls below screen
        if (b - playerRadius > window.getSize().y)
        {
            cout << "Game Over!" << endl;
            window.close();
             
        }

        // Scroll world if above height
        if (b < h)
        {
            b = h;
            for (int i = 0; i < platformCount; ++i)
            {
                opos[i].y += -db;
                if (opos[i].y > 1400)
                {
                    opos[i].y = 0;
                    opos[i].x = rand() % 900;
                }
                plat[i].setPosition(opos[i]);
            }
        }

        // Collision with platforms
        for (int i = 0; i < platformCount; ++i)
        {
            Vector2f pPos = {a, b};
            Vector2f platPos = plat[i].getPosition();

            if (pPos.x + playerRadius > platPos.x &&
                pPos.x - playerRadius < platPos.x + platformWidth &&
                pPos.y + playerRadius > platPos.y &&
                pPos.y + playerRadius < platPos.y + platformHeight &&
                db > 0)
            {
                db = -10;
                b = platPos.y - playerRadius;
            }
        }

        player.setPosition({a, b});

        // Draw
        window.clear(Color::Black);
        window.draw(player);
        for (int i = 0; i < platformCount; ++i)
            window.draw(plat[i]);
        window.display();
    }
}