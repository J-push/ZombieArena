#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class Player;

enum class ZombieTypes
{
    BLOATER,
    CHASER,
    CRAWLER,
    COUNT,
};

//이정보를 누군가 들고 있는 것이 좋다..
struct ZombieInfo
{
    ZombieTypes type;
    std::string textureFileName;
    float speed;
    int health;
};

enum class ZombieState
{
    ALIVE,        //살음
    DEATH,        //죽음
    DROP,        //현재 없음.
};

class Zombie
{
private:
    ZombieTypes zombieTypes;
    ZombieState zombieState; //좀비상태가 없는 상태
    Vector2f position;
    Sprite sprite;
    //Sprite sprite;

    float speed;    //기본속도
    int health;    //체력

    //bool alive; //살았는지 죽었는지
    float deleteBloodTime;    //피를 삭제하는 시간?

    static std::vector<ZombieInfo> zombieInfo;
    static bool isInitInfo;

public:
    Zombie();
    bool OnHitted();
    bool IsAlive();

    void Spawn(float x, float y, ZombieTypes type); //초기화함수
    void Update(float dt, Vector2f playerPosition, IntRect arena);

    bool UpdateCollision(Time time, Player &player);

    FloatRect GetGlobalBound();
    Sprite GetSprite();
	void Normalize(Vector2f& dir);

    void Draw(RenderWindow &window);

};
