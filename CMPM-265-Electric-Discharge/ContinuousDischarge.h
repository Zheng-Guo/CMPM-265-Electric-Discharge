#pragma once
#include <SFML\Graphics.hpp>
#include "Form.h"
#include "ElectricArc.h"

using namespace sf;
using namespace std;

class ContinuousDischarge: public Form
{
private:
	Text instruction1, instruction2;
	Font font;
	Display nextDisplay;
	ElectricArc electricArc;
public:
	ContinuousDischarge(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
	nextDisplay(Display::Continuous), electricArc(Vector2f(400, 100), 90, 600, 5, 0)
	{
		srand(time(NULL));
		int amplitude = rand() % Amplitude_Margin + Amplitude_Base;
		electricArc.setAmplitude(amplitude);
		electricArc.setNoiseSeed(rand());
		electricArc.setContinuous(true);
		electricArc.setTargetPoint(Vector2f(400, 600));
		electricArc.setBranching(false);
		electricArc.buildArc();
		font.loadFromFile("Tinos-Regular.ttf");
		instruction1.setFont(font);
		instruction1.setString("Press Enter to generate another electric arc.");
		instruction1.setCharacterSize(Instruction_Character_Size);
		instruction1.setFillColor(Color::Red);
		instruction1.setPosition(Menu_Instruction_X, Menu_Instruction_Y);
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

void ContinuousDischarge::processEvent(Event event)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		nextDisplay = Display::Menu;
	}
}

void ContinuousDischarge::update(float deltaTime)
{
	electricArc.update(deltaTime);
}

void ContinuousDischarge::render(RenderWindow& window)
{
	electricArc.draw(window);
	window.draw(instruction1);
	window.draw(instruction2);
}

Display ContinuousDischarge::next()
{
	return nextDisplay;
}

