#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

//texture를 들고있는 놈들 (모음집)
class TextureHolder
{
public:
	TextureHolder();
	static Texture& GetTexture(string filename);
private:
	std::map<string, Texture> mapTexture;
	static TextureHolder* instance;
};

