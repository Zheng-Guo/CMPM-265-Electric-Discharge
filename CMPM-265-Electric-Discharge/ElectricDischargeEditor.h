#pragma once
#include <SFML\Graphics.hpp>
#include "Form.h"
#include "ElectricArc.h"

using namespace sf;
using namespace std;

class ElectricDischargeEditor: public Form
{
private:
	Text instruction1, instruction2;
	Font font;
	Display nextDisplay;
	ElectricArc electricArc;
public:
	ElectricDischargeEditor(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
	nextDisplay(Display::Editor),
	electricArc(Vector2f(400,50),90,600,8)
	{

		font.loadFromFile("Tinos-Regular.ttf");
		instruction1.setFont(font);
		instruction1.setString("Press Up/Down arrow key to increase/decrease the number of particles.");
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

void ElectricDischargeEditor::processEvent(Event event)
{
	if (Keyboard::isKeyPressed(Keyboard::Up)) {

	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {

	}
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		nextDisplay = Display::Menu;
	}
}

void ElectricDischargeEditor::update(float deltaTime)
{
	
}

void ElectricDischargeEditor::render(RenderWindow& window)
{
	electricArc.draw(window);
	window.draw(instruction1);
	window.draw(instruction2);
}

Display ElectricDischargeEditor::next()
{
	return nextDisplay;
}

