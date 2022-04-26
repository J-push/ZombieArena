#pragma once

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

//texture�� ����ִ� ��� (������)
class TextureHolder
{
public:
	TextureHolder();
	static Texture& GetTexture(string filename);
private:
	std::map<string, Texture> mapTexture;
	static TextureHolder* instance;
};

