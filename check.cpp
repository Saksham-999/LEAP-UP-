#include "game.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <ctime>
#include <vector>



enum class Scene { Menu, Game };

using namespace sf;
using namespace std;

void fadeIn(sf::RenderWindow& window, sf::Sprite& background,sf::Sprite& start,sf::Sprite& credits,sf::Sprite& quit,
    sf::Sprite& volume, sf::Music& music) {
    sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 255)); // Fully black

    const float fadeDuration = 2.0f; // seconds
    sf::Clock clock;

    music.play(); // Start music just before fade-in

    while (overlay.getFillColor().a > 0) {
        float elapsed = clock.getElapsedTime().asSeconds();
        float alpha = 255 - (elapsed / fadeDuration) * 255;
        if (alpha < 0) alpha = 0;

        overlay.setFillColor(sf::Color(0, 0, 0, static_cast<uint8_t>(alpha)));

        window.clear();
        window.draw(background);     // draw background underneath
        window.draw(start);          // draw start button
        window.draw(credits);        // draw credits button
        window.draw(quit);           // draw quit button
        window.draw(volume);         // draw volume button
        window.draw(overlay);        // then draw fading black overlay
        window.display();
    }
}


int main()
{
    // Videomode and RenderWindow class under sf namespace

    sf::VideoMode videoMode({1000, 1400}, 32);                          // setting the window size and bits
    sf::RenderWindow window(videoMode, "LEAP UP!", sf::Style::Default); // creates name for window and creates close, resize, and minimize button

    sf::Texture background, start, credits, quit, volume, mute;

    if (!background.loadFromFile("assets/bg.png") ||
        !start.loadFromFile("assets/start.png") ||
        !credits.loadFromFile("assets/credits.png") ||
        !quit.loadFromFile("assets/quit.png") ||
        !volume.loadFromFile("assets/volume.png") ||
        !mute.loadFromFile("assets/mute.png"))
    {
        return -1; // error loading image
    }

    sf::Sprite bg(background);
    sf::Sprite Start(start);
    sf::Sprite Credit(credits);
    sf::Sprite Quit(quit);
    sf::Sprite Volume(volume);

    sf::Music music;//music sprite
    if (!music.openFromFile("assets/music1.mp3"))
    {
        std::cerr << "Failed to load music\n";
        return -1;
    }
    music.setLooping(true);//music loop
    music.play();
    

    bool musicOn = true;
 
    Start.setPosition({230.f, 400.f});
    Credit.setPosition({230.f, 600.f});
    Quit.setPosition({230.f, 800.f});

    Volume.setScale({0.2f, 0.2f});
    Start.setScale({0.85f, 0.85f});
    Credit.setScale({0.85f, 0.85f});
    Quit.setScale({0.85f, 0.85f});

    Scene currentScene = Scene::Menu;
    fadeIn(window, bg,Start,Credit,Quit,Volume, music); // Fade in effect



    while (window.isOpen())
    { // Loop to hold the window

        while (auto eventOpt = window.pollEvent())
        { // checks for user actions like closing window,mouse click
            if (!eventOpt.has_value())
                continue;

            const sf::Event &event = eventOpt.value();

            if (event.is<sf::Event::Closed>())
            {
                window.close();
            }

            /*if (event.is<sf::Event::MouseMoved>())
            {
                const auto &mouse = event.getIf<sf::Event::MouseMoved>();
                sf::Vector2f mousePos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));

                if (Start.getGlobalBounds().contains(mousePos))
                {
                    Start.setColor(sf::Color(255, 255, 255, 150));//hover effect for start button
                }
            }*/
            if (event.is<sf::Event::MouseButtonPressed>())
            {
                const auto &mouse = event.getIf<sf::Event::MouseButtonPressed>();
                sf::Vector2f mousePos(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));

                if (Quit.getGlobalBounds().contains(mousePos))
                {
                    return 0;
                }

                if (Start.getGlobalBounds().contains(mousePos)) {
                    currentScene = Scene::Game;
                    runGame(window); // Start the game
                }


                if (Volume.getGlobalBounds().contains(mousePos))
                {

                    musicOn = !musicOn;
                    if (musicOn)
                    {
                        music.play();
                        Volume.setTexture(volume);
                    }
                    else
                    {
                        music.pause();
                        Volume.setTexture(mute);
                    }
                }
            }

             
            
            window.clear(sf::Color(255, 165, 0)); // color
            
            window.draw(bg);
            window.draw(Start);
            window.draw(Credit);
            window.draw(Quit);
            window.draw(Volume);
            window.display(); // makes the window appear;used during gameloop
        }
    }
    return 0;

    
}








