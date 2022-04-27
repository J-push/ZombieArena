#include <SFML/Graphics.hpp>
#include "source/Utility/InputManager.h"
#include "source/Utility/Utility.h"
#include "source/Player/Player.h"
#include <iostream>
#include "source/Utility/TextureHolder.h"
#include "source/Zombie/Zombie.h"
#include "source/Bullet/Bullet.h"
#include "Pickup.h"
#include <sstream>

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

            // 위치 정보 
            int vertexIndex = index * VERTS_IN_QUAD;
            va[vertexIndex + 0].position = Vector2f(x,y);
            va[vertexIndex + 1].position = Vector2f(x + TILE_SIZE,y);
            va[vertexIndex + 2].position = Vector2f(x + TILE_SIZE,y + TILE_SIZE);
            va[vertexIndex + 3].position = Vector2f(x,y + TILE_SIZE);

            bool outline = (c == 0 || r == 0 || c == cols - 1 || r == rows - 1);
            int texIndex = outline ? TILE_SIZE : Utility::RandomRange(0, TILE_TYPES);
            
            // 사진 짤라준 것
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

    Sprite spriteBackground;
    Texture textureBackground = TextureHolder::GetTexture("graphics/background.png");
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Font fontZombie;
    fontZombie.loadFromFile("fonts/zombiecontrol.ttf");

    // 시작 문구
    Text textStart;
    textStart.setFont(fontZombie);
    textStart.setString("Press Enter to Play");
    textStart.setCharacterSize(75);
    textStart.setFillColor(Color::White);
    FloatRect textRectStart = textStart.getLocalBounds();
    textStart.setOrigin(
        textRectStart.left + textRectStart.width * 0.5f,
        textRectStart.top + textRectStart.height * 0.5f);
    textStart.setPosition(1000, 500);

    // FIRE 강화
    Text textIncFire;
    textIncFire.setFont(fontZombie);
    textIncFire.setString("1- INCREASED RATE OF FIRE");
    textIncFire.setCharacterSize(75);
    textIncFire.setFillColor(Color::White);
    FloatRect textRectFire = textIncFire.getLocalBounds();
    textIncFire.setOrigin(
        textRectFire.left + textRectFire.width * 0.5f,
        textRectFire.top + textRectFire.height * 0.5f);
    textIncFire.setPosition(800, 300);

    // 장전 강화
    Text textIncReload;
    textIncReload.setFont(fontZombie);
    textIncReload.setString("2- INCREASED CLIP SIZE(NEXT RELOAD)");
    textIncReload.setCharacterSize(75);
    textIncReload.setFillColor(Color::White);
    FloatRect textRectReload = textIncReload.getLocalBounds();
    textIncReload.setOrigin(
        textRectReload.left + textRectReload.width * 0.5f,
        textRectReload.top + textRectReload.height * 0.5f);
    textIncReload.setPosition(975, 380);

    // 체력 강화
    Text textIncHealth;
    textIncHealth.setFont(fontZombie);
    textIncHealth.setString("3- INCREASED MAX HEALTH");
    textIncHealth.setCharacterSize(75);
    textIncHealth.setFillColor(Color::White);
    FloatRect textRectHealth = textIncHealth.getLocalBounds();
    textIncHealth.setOrigin(
        textRectHealth.left + textRectHealth.width * 0.5f,
        textRectHealth.top + textRectHealth.height * 0.5f);
    textIncHealth.setPosition(800, 460);

    // 속도 강화
    Text textIncSpeed;
    textIncSpeed.setFont(fontZombie);
    textIncSpeed.setString("4- INCREASED RUN SPEED");
    textIncSpeed.setCharacterSize(75);
    textIncSpeed.setFillColor(Color::White);
    FloatRect textRectSpeed = textIncSpeed.getLocalBounds();
    textIncSpeed.setOrigin(
        textRectSpeed.left + textRectSpeed.width * 0.5f,
        textRectSpeed.top + textRectSpeed.height * 0.5f);
    textIncSpeed.setPosition(760, 540);

    // 힐팩 
    Text textIncHealPick;
    textIncHealPick.setFont(fontZombie);
    textIncHealPick.setString("5- MORE AND BETTER HEALTH PICKUPS");
    textIncHealPick.setCharacterSize(75);
    textIncHealPick.setFillColor(Color::White);
    FloatRect textRectHealPick = textIncHealPick.getLocalBounds();
    textIncHealPick.setOrigin(
        textRectHealPick.left + textRectHealPick.width * 0.5f,
        textRectHealPick.top + textRectHealPick.height * 0.5f);
    textIncHealPick.setPosition(958, 620);

    // 총알 아이템
    Text textIncAmmoPick;
    textIncAmmoPick.setFont(fontZombie);
    textIncAmmoPick.setString("6- MORE AND BETTER AMMO PICKUPS");
    textIncAmmoPick.setCharacterSize(75);
    textIncAmmoPick.setFillColor(Color::White);
    FloatRect textRectAmmoPick = textIncAmmoPick.getLocalBounds();
    textIncAmmoPick.setOrigin(
        textRectAmmoPick.left + textRectAmmoPick.width * 0.5f,
        textRectAmmoPick.top + textRectAmmoPick.height * 0.5f);
    textIncAmmoPick.setPosition(938, 700);

    // 재시작 문구
    Text textReStart;
    textReStart.setFont(fontZombie);
    textReStart.setString("PRESS ENTER TO CONTINUE");
    textReStart.setCharacterSize(130);
    textReStart.setFillColor(Color::White);
    FloatRect textRectReStart = textReStart.getLocalBounds();
    textReStart.setOrigin(
        textRectReStart.left + textRectReStart.width * 0.5f,
        textRectReStart.top + textRectReStart.height * 0.5f);
    textReStart.setPosition(1000, 500);

    Text textBullet;
    textBullet.setFont(fontZombie);
    textBullet.setCharacterSize(50);
    textBullet.setFillColor(Color::White);
    textBullet.setPosition(200, 1000);

    // 스코어 점수
    Text textScore;
    textScore.setFont(fontZombie);
    textScore.setString("Score = 0");
    textScore.setCharacterSize(75);
    textScore.setFillColor(Color::White);
    textScore.setPosition(40, 20);

    // 최고 점수
    Text textHighScore;
    textHighScore.setFont(fontZombie);
    textHighScore.setString("High Score = 0");
    textHighScore.setCharacterSize(75);
    textHighScore.setFillColor(Color::White);
    textHighScore.setPosition(1400, 20);

    // 웨이브 단계
    Text textWave;
    textWave.setFont(fontZombie);
    textWave.setString("Wave = 0");
    textWave.setCharacterSize(50);
    textWave.setFillColor(Color::White);
    textWave.setPosition(1400, 1000);

    // 좀비 개수
    Text textZombie;
    textZombie.setFont(fontZombie);
    textZombie.setString("Zombie = 0");
    textZombie.setCharacterSize(50);
    textZombie.setFillColor(Color::White);
    textZombie.setPosition(1650, 1000);

    // 확인용 체력
    Text textHP;
    textHP.setFont(fontZombie);
    textHP.setString("HP : 100");
    textHP.setCharacterSize(50);
    textHP.setFillColor(Color::White);
    textHP.setPosition(400, 900);

    // 체력 바
    RectangleShape HpBar;
    float HpBarWidth = 300;
    float HpBarHeight = 40;

    Vector2f HpBarSize = Vector2f(HpBarWidth, HpBarHeight);
    HpBar.setSize(HpBarSize);
    HpBar.setPosition(400, 1000);
    HpBar.setFillColor(Color::Red);

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Fullscreen);

    window.setMouseCursorVisible(false);

    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::GetTexture("graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    Utility::SetOrigin(spriteCrosshair, Pivots::CENTERCENTER);

    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    View uiView(FloatRect(0, 0, resolution.x, resolution.y));

    InputManager::Init();

    IntRect arena;
    arena.width = 1000;
    arena.height = 1000;

    Pickup ammoPickup(PickupTypes::Ammo);
    Pickup healthPickup(PickupTypes::Health);
    ammoPickup.SetArena(arena);
    healthPickup.SetArena(arena);

    std::list<Pickup *> items;
    items.push_back(&ammoPickup);
    items.push_back(&healthPickup);

    Player player;
    player.Spawn(arena, resolution, 0.f);

    std::vector<Zombie *> zombies;
    int zombiesCount = 10;
    CreateZombies(zombies, zombiesCount, arena);

    Clock clock;
    Time playTime;

    Texture &texBackground = TextureHolder::GetTexture("graphics/background_sheet.png");

    VertexArray tileMap;
    CreateBackground(tileMap, arena);

    bool IsPause = false;
    bool gameStart = false;
    bool gameClear = false;
    bool playerDie = false;

    while (window.isOpen())
    {
        Time dt = clock.restart();
        playTime += dt;
        InputManager::ClearInput();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                switch (event.key.code)
                {
                case Keyboard::Escape:
                    window.close();
                    break;
                case Keyboard::Return:
                {
                    IsPause = true;
                    gameStart = true;
                }
                break;
                }
            }
        }
        if (IsPause && gameStart)
        {
            InputManager::ProcessInput(event);
            // Update
            InputManager::Update(dt.asSeconds(), window, mainView);

            if (Keyboard::isKeyPressed(Keyboard::Num0))
            {
                IsPause = false;
                gameStart = false;
                gameClear = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Num1))
            {
                IsPause = false;
                gameStart = false;
                playerDie = true;
            }
            spriteCrosshair.setPosition(InputManager::GetMouseWorldPosition());

            player.Update(dt.asSeconds());
            mainView.setCenter(player.GetPosition());

            // 각자의 속도로 좀비가 플레이어를 쫓아가게 해라.
            for (auto zombie : zombies)
            {
                zombie->Update(dt.asSeconds(), player.GetPosition(), arena);
            }

            ammoPickup.Update(dt.asSeconds());
            healthPickup.Update(dt.asSeconds());

            // 충돌처리(Collision)
            player.UpdateCollision(zombies);
            for (auto zombie : zombies)
            {
                if (zombie->UpdateCollision(playTime, player))
                {
                    break;
                }
            }
            player.UpdateCollision(items);

            stringstream C;
            C << player.GetClip() << " / " << player.GetClipSum();
            textBullet.setString(C.str());

            int score = 0;
            stringstream upScore;
            upScore << "Score = " << score;
            textScore.setString(upScore.str());

            int highScore = 10;
            if (score > highScore)
            {
                stringstream HS;
                HS << "High Score = " << highScore;
                textHighScore.setString(HS.str());
            }

            int WaveNum = 3;
            stringstream WN;
            WN << "Wave = " << WaveNum;
            textWave.setString(WN.str());

            stringstream ZN;
            ZN << "Zombie = " << zombiesCount;
            textZombie.setString(ZN.str());

            stringstream HH;
            HH << "HP : " << player.GetHealth();
            textHP.setString(HH.str());

            HpBarWidth = 300 * ((float)player.GetHealth() / player.GetMaxHealth());
            Vector2f HpBarSize = Vector2f(HpBarWidth, HpBarHeight);
            HpBar.setSize(HpBarSize);

            if (HpBarWidth < 0)
            {
                IsPause = false;
                gameStart = false;
                playerDie = true;
            }

            // Draw
            window.clear();

            window.setView(mainView);
            window.draw(tileMap, &texBackground);

            for (auto item : items)
            {
                if (item->GetEarnIt())
                {
                    window.draw(item->GetSprite());
                }
            }
            for (auto zombie : zombies)
            {
                zombie->Draw(window);
            }

            player.Draw(window);
            window.draw(spriteCrosshair);

            window.setView(uiView);
            window.draw(textBullet);

            window.draw(HpBar);
            window.draw(textScore);
            window.draw(textHighScore);
            window.draw(textWave);
            window.draw(textZombie);
            window.draw(textBullet);

            window.draw(textHP);
        }
        else if (gameClear)
        {
            // 1번
            FloatRect crossHairBounds = spriteCrosshair.getGlobalBounds();
            if (crossHairBounds.intersects(textIncFire.getGlobalBounds()))
            {
                textIncFire.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    gameClear = false;
                }
            }
            else
            {
                textIncFire.setFillColor(Color::White);
            }

            // 2번
            if (crossHairBounds.intersects(textIncReload.getGlobalBounds()))
            {
                textIncReload.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    gameClear = false;

                    player.SetBul(5);
                    player.SetHiBul(5);
                }
            }
            else
            {
                textIncReload.setFillColor(Color::White);
            }

            // 3번
            if (crossHairBounds.intersects(textIncHealth.getGlobalBounds()))
            {
                textIncHealth.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    gameClear = false;

                    player.SetHealth();
                    player.SetMaxHealth();
                }
            }
            else
            {
                textIncHealth.setFillColor(Color::White);
            }

            // 4번
            if (crossHairBounds.intersects(textIncSpeed.getGlobalBounds()))
            {
                textIncSpeed.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    gameClear = false;
                    player.SetSpeed();
                }
            }
            else
            {
                textIncSpeed.setFillColor(Color::White);
            }

            // 5번
            if (crossHairBounds.intersects(textIncHealPick.getGlobalBounds()))
            {
                textIncHealPick.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    gameClear = false;
                    healthPickup.SetHealthValue();
                }
            }
            else
            {
                textIncHealPick.setFillColor(Color::White);
            }

            // 6번
            if (crossHairBounds.intersects(textIncAmmoPick.getGlobalBounds()))
            {
                textIncAmmoPick.setFillColor(Color::Red);
                if (Mouse::isButtonPressed(Mouse::Button::Left))
                {
                    gameClear = false;
                    ammoPickup.SetAmmoValue();
                }
            }
            else
            {
                textIncAmmoPick.setFillColor(Color::White);
            }
            InputManager::Update(dt.asSeconds(), window, mainView);
            spriteCrosshair.setPosition(InputManager::GetMouseWorldPosition());
            window.setView(uiView);
            window.draw(spriteBackground);
            window.draw(textIncFire);
            window.draw(textIncReload);
            window.draw(textIncHealth);
            window.draw(textIncSpeed);
            window.draw(textIncHealPick);
            window.draw(textIncAmmoPick);
            window.draw(spriteCrosshair);
        }
        else if (playerDie)
        {
            window.draw(spriteBackground);
            window.draw(textReStart);
            gameStart = false;
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                if (Keyboard::isKeyPressed(Keyboard::Return))
                {
                    player.InitHealth();
                    IsPause = true;
                    gameStart = true;
                    playerDie = false;
                }
                gameStart = true;
            }
        }
        else
        {
            window.setView(uiView);
            window.draw(spriteBackground);
            window.draw(textStart);
        }
        window.display();
    }
    return 0;
}