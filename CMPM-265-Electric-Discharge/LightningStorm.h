#pragma once
#include <SFML\Graphics.hpp>
#include "Form.h"
#include "ElectricArc.h"

using namespace sf;
using namespace std;

class LightningStorm: public Form
{
private:
	Text instruction2;
	Font font;
	Display nextDisplay;
	ElectricArc electricArc;
public:
	LightningStorm(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
	nextDisplay(Display::Storm),
	electricArc(Vector2f(400, 50), 90, 600, 5, 0, false,Storm_Duration,Storm_Fading_Rate)
	{
		srand(time(NULL));
		int amplitude = rand() % Amplitude_Margin + Amplitude_Base;
		electricArc.setAmplitude(amplitude);
		electricArc.setNoiseSeed(rand());
		electricArc.buildArc();
		font.loadFromFile("Tinos-Regular.ttf");
		instruction2.setFont(font);
		instruction2.setString("Press Escape to return to menu.");
		instruction2.setCharacterSize(Instruction_Character_Size);
		instruction2.setFillColor(Color::Red);
		instruction2.setPosition(Menu_Instruction_X, Menu_Instruction_Y + 30);
	}
	virtual void processEvent(Event event) override;
	virtual void update(float deltaTime) override;
	virtual void render(RenderWindow &window) override;
	virtual Display next() override;
};

void LightningStorm::processEvent(Event event)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		nextDisplay = Display::Menu;
	}
}

void LightningStorm::update(float deltaTime)
{
	electricArc.update(deltaTime);
}

void LightningStorm::render(RenderWindow& window)
{
	electricArc.draw(window);
	window.draw(instruction2);
}

Display LightningStorm::next()
{
	return nextDisplay;
}