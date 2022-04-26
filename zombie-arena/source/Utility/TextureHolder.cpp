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
	// 1. filename key map�� �ֳ� ����?

	// 2. ���� ��	
	// -> (�ʿ��� map insert)
	// 3. ���� ��
	// -> ���� map insert
	auto& map = instance->mapTexture;
	auto it = map.find(filename);
	if (it == map.end()) // �ȿ� �ִ� ���
	{
		auto& texture = map[filename]; // Ű , �� ������ ����
		texture.loadFromFile(filename);
	}
	return map[filename]; 
}
