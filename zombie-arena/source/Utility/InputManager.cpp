#include "InputManager.h"
#include <algorithm>
#include <iostream>
#include <cmath>

std::map<Axis, AxisInfo> InputManager::mapAxis;

list<Keyboard::Key> InputManager::downKeys;
list<Keyboard::Key> InputManager::ingKeys;
list<Keyboard::Key> InputManager::upKeys;

list<Mouse::Button> InputManager::downButtons;
list<Mouse::Button> InputManager::ingButtons;
list<Mouse::Button> InputManager::upButtons;

Vector2i InputManager::mousePosition;
Vector2f InputManager::mouseWorldPosition;
void InputManager::Init()
{
	mapAxis.clear();

	AxisInfo info;
	// Horizontal
	info.axis = Axis::Horizontal;
	info.sensi = 2.0f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::D);
	info.positiveKeys.push_back(Keyboard::Right);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::A);
	info.negativeKeys.push_back(Keyboard::Left);
	mapAxis[info.axis] = info;

	// Vertical
	info.axis = Axis::Vertical;
	info.sensi = 2.0f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::S);
	info.positiveKeys.push_back(Keyboard::Down);

	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::W);
	info.negativeKeys.push_back(Keyboard::Up);
	mapAxis[info.axis] = info;
}

void InputManager::ClearInput()
{
	downButtons.clear();
	downKeys.clear();
	upKeys.clear();
}

void InputManager::ProcessInput(const Event& event)
{
	switch (event.type)
	{
	case Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			downKeys.push_back(event.key.code);
			ingKeys.push_back(event.key.code);
		}
		break;
	case Event::KeyReleased:
		ingKeys.remove(event.key.code);
		upKeys.push_back(event.key.code);
		break;
	case Event::MouseButtonPressed:
		if (!GetMouseButton(event.mouseButton.button))
		{
			downButtons.push_back(event.mouseButton.button);
			ingButtons.push_back(event.mouseButton.button);
		}
		break;
	case Event::MouseButtonReleased:
		ingButtons.remove(event.mouseButton.button);
		upButtons.push_back(event.mouseButton.button);
		break;
	default:
		break;
	}
}

void InputManager::Update(float dt, RenderWindow &window, View &worldView)
{
	for (auto it = mapAxis.begin(); it != mapAxis.end(); ++it)
	{
		AxisInfo& ref = it->second;

		// Axis(���ÿ� ���缭)
		int axis = GetAxisRaw(ref.axis);
		if (axis == 0)
		{
			axis = ref.value > 0 ? -1 : 1;
			if (abs(ref.value) < ref.limit)
			{
				axis = 0;
				ref.value = 0;
			}
		}

		ref.value += axis * ref.sensi * dt;

		if (ref.value > 1.f)
		{
			ref.value = 1.f;
		}

		if (ref.value < -1.f)
		{
			ref.value = -1.f;
		}
	}
	mousePosition = Mouse::getPosition();
	mouseWorldPosition= window.mapPixelToCoords(mousePosition, worldView);
}

float InputManager::GetAxis(Axis axis)
{
	if (mapAxis.find(axis) != mapAxis.end())
	{
		return mapAxis[axis].value;
	}
	return 0.f;
}

// Ű�Է��� �޾Ƽ� Ȯ������ ��������
int InputManager::GetAxisRaw(list<Keyboard::Key> positive, list<Keyboard::Key> negative)
{
	int axis = 0;
	bool isPositive = false;
	bool isNegative = false;

	for (auto it = positive.begin(); it != positive.end(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isPositive = true;
			break;
		}
	}

	for (auto it = negative.begin(); it != negative.end(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isNegative = true;
			break;
		}
	}

	if (isPositive && isNegative)
	{
		axis = 0;
	}

	else if (isPositive)
	{
		axis = 1;
	}
	else if (isNegative)
	{
		axis = -1;
	}
	return axis;
}

int InputManager::GetAxisRaw(Axis axis)
{
	//find�� �������� end�� Ȯ���ؾ��Ѵ�.
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxisRaw(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	return 0;
}

bool InputManager::GetKeyDown(Keyboard::Key key)
{
	auto it = find(downKeys.begin(), downKeys.end(), key);
	return it != downKeys.end();
}

bool InputManager::GetKey(Keyboard::Key key)
{
	auto it = find(ingKeys.begin(), ingKeys.end(), key);
	return it != ingKeys.end();
}

bool InputManager::GetKeyUp(Keyboard::Key key)
{
	auto it = find(upKeys.begin(), upKeys.end(), key);
	return it != upKeys.end();
}


Vector2i InputManager::GetMousePosition()
{
	return mousePosition;
}

Vector2f InputManager::GetMouseWorldPosition()
{
	return mouseWorldPosition;
}

bool InputManager::GetMouseButtonDown(Mouse::Button button)
{
	auto it = find(downButtons.begin(), downButtons.end(), button);
	return it != downButtons.end();
}

bool InputManager::GetMouseButton(Mouse::Button button)
{
	auto it = find(ingButtons.begin(), ingButtons.end(), button);
	return it != ingButtons.end();
}


bool InputManager::GetMouseButtonUp(Mouse::Button button)
{
	auto it = find(upButtons.begin(), upButtons.end(), button);
	return it != upButtons.end();
}


