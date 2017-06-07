#pragma once
#include <SFML\Graphics.hpp>
#include "Constants.h"

using namespace sf;
using namespace std;

class Form
{
public:
	Form(int windowWidth = 100, int windowHeight = 100)
	{
	}
	virtual void processEvent(Event event, RenderWindow& window) = 0;
	virtual void update(float deltaTime) = 0;
	virtual void render(RenderWindow &window)=0;
	virtual Display next() = 0;
};