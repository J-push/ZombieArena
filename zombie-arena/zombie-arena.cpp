#include <SFML/Graphics.hpp>
#include "source/Utility/InputManager.h"
#include "source/Utility/Utility.h"
#include "source/Player/Player.h"
#include <iostream>
#include "source/Utility/TextureHolder.h"
#include "source/Zombie/Zombie.h"

//배경 만들기
int CreateBackground(VertexArray& va, IntRect arena)
{
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int cols = arena.width / TILE_SIZE;
    int rows = arena.height / TILE_SIZE;

    va.setPrimitiveType(Quads);
    va.resize(cols * rows * VERTS_IN_QUAD);

    int index = 0;


    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            int index = r * cols + c;
            float x = c * TILE_SIZE;
            float y = r * TILE_SIZE;

            int vertexIndex = index * VERTS_IN_QUAD;
            va[vertexIndex + 0].position = Vector2f(x,y);
            va[vertexIndex + 1].position = Vector2f(x + TILE_SIZE,y);
            va[vertexIndex + 2].position = Vector2f(x + TILE_SIZE,y + TILE_SIZE);
            va[vertexIndex + 3].position = Vector2f(x,y + TILE_SIZE);

            bool outline = (c == 0 || r == 0 || c == cols - 1 || r == rows - 1);
            int texIndex = outline ? TILE_SIZE : Utility::RandomRange(0, TILE_TYPES);

            float offset = texIndex * TILE_SIZE;
            va[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
            va[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
            va[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
            va[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
        }
    }
    return cols * rows;
}


void CreateZombies(std::vector<Zombie*>& zombies,int count, IntRect arena)
{
    for (auto v : zombies) // 좀비배열 순회
    {
        delete v;  
    }
    // 기존에 좀비가 들고있는게 있을 수 있으니 날려줘야함(비워줘야함)
    zombies.clear();

    int offset = 25;
    int minX = arena.left + offset;
    int maxX = arena.width - offset;
    int minY = arena.top + offset;
    int maxY = arena.height - offset;

    for (int i = 0; i < count; ++i)
    {
        int x = Utility::RandomRange(minX, maxX + 1);
        int y = Utility::RandomRange(minY, maxY + 1);
        ZombieTypes type = (ZombieTypes)Utility::RandomRange(0, (int)ZombieTypes::COUNT);

        Zombie* zombie = new Zombie();
        zombie->Spawn(x, y, type);
        // 스폰을 할떄마다 좀비가 새로 시작하는 느낌
        zombies.push_back(zombie);
    }
}

int main()
{
    TextureHolder textureHolder;

    Vector2i resolution;

    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);
    
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));

    InputManager::Init();
    
    IntRect arena;
    arena.width = 500;
    arena.height = 500;

    Player player;
    player.Spawn(arena, resolution, 0.f);

    std::vector<Zombie*> zombies;
    CreateZombies(zombies, 10 ,arena);

    Clock clock;   

    Texture textBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

    VertexArray tileMap;
    CreateBackground(tileMap, arena);

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
        //Update
        InputManager::Update(dt.asSeconds());

        player.Update(dt.asSeconds());
        mainView.setCenter(player.GetPosition());

        for (auto zombie : zombies)
        {
            zombie->Update(dt.asSeconds(), player.GetPosition());
        }

        // Draw
        window.clear();
        window.setView(mainView);
        window.draw(tileMap, &textBackground);

        for (auto zombie : zombies)
        {
            window.draw(zombie->GetSprite());
        }
        window.draw(player.GetSprite());
        window.display();
    }
}