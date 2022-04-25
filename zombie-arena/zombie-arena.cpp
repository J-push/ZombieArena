#include <SFML/Graphics.hpp>
#include "source/Utility/InputManager.h"
#include "source/Utility/Utility.h"
#include "source/Player/Player.h"

int main()
{
    Vector2i resolution;

    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);
    
    InputManager::Init();
    
    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;

    Player player;
    player.Spawn(arena, resolution, 0.f);
    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart();

        InputManager::ClearInput();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputManager::ProcessInput(event);
        }

        player.Update(dt.asSeconds());
        window.clear();
        window.draw(player.GetSprite());
        window.display();
    }
    return 0;
}