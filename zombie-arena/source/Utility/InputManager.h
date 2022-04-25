#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	list<Keyboard::Key> positiveKeys;
	list<Keyboard::Key> negativeKeys;
};

class InputManager
{
private:
	static map<Axis, AxisInfo> mapAxis;

	static list<Keyboard::Key>downKeys;
	static list<Keyboard::Key>ingKeys;
	static list<Keyboard::Key>upKeys;
public:
	static void Init();
	static void ClearInput();
	static void ProcessInput(const Event& event);

	static int GetAxis(list<Keyboard::Key> positive, list<Keyboard::Key> negative);
	static int GetAxis(Axis axis);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	static Vector2i GetMousePosition();
};

