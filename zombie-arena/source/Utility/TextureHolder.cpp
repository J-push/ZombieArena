#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(instance == nullptr);
	instance = this;
}

Texture& TextureHolder::GetTexture(string filename)
{
	// 1. filename key map에 있냐 없냐?

	// 2. 있을 떄	
	// -> (맵에서 map insert)
	// 3. 없을 떄
	// -> 만들어서 map insert
	auto& map = instance->mapTexture;
	auto it = map.find(filename);
	if (it == map.end()) // 안에 있는 경우
	{
		auto& texture = map[filename]; // 키 , 빈 생성자 생성
		texture.loadFromFile(filename);
	}
	return map[filename]; 
}
