#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


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

    Start.setPosition({230.f, 500.f});
    Credit.setPosition({230.f, 700.f});
    Quit.setPosition({230.f, 900.f});

    Volume.setScale({0.2f, 0.2f});
    Start.setScale({0.85f, 0.85f});
    Credit.setScale({0.85f, 0.85f});
    Quit.setScale({0.85f, 0.85f});

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
                   // Start.setColor(sf::Color(255, 255, 255, 150));//hover effect for start button
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
