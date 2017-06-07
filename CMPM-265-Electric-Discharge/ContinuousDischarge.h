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
	bool leftAlreadyPressed, rightAlreadyPressed;
	CircleShape anode;
	vector<CircleShape> cathodes;
	void addCathode(Vector2i p);
	void removeCathode(Vector2i p);
public:
	ContinuousDischarge(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
	nextDisplay(Display::Continuous), electricArc(Vector2f(400, 100), 90, 600, 5, 0),
	leftAlreadyPressed(false),
	rightAlreadyPressed(false),
	anode(Continuous_Anode_Radius)
	{
		srand(time(NULL));
		anode.setOrigin(Continuous_Anode_Radius, Continuous_Anode_Radius);
		anode.setPosition(Continuous_Anode_X, Continuous_Anode_Y);
		anode.setFillColor(Color::Red);
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
	virtual void processEvent(Event event, RenderWindow& window) override;
	virtual void update(float deltaTime) override;
	virtual void render(RenderWindow &window) override;
	virtual Display next() override;
};

void ContinuousDischarge::addCathode(Vector2i p)
{
	CircleShape cathode(Continuous_Anode_Radius);
	cathode.setOrigin(Continuous_Anode_Radius, Continuous_Anode_Radius);
	cathode.setFillColor(Color::Blue);
	cathode.setPosition(p.x,p.y);
	cathodes.push_back(cathode);
}

void ContinuousDischarge::removeCathode(Vector2i p)
{
	for(vector<CircleShape>::reverse_iterator i=cathodes.rbegin();i!=cathodes.rend();++i)
	{
		float deltaX = i->getPosition().x - p.x, deltaY = i->getPosition().y - p.y;
		float distanceSquared = deltaX*deltaX + deltaY*deltaY;
		if(distanceSquared<Continuous_Anode_Radius*Continuous_Anode_Radius)
		{
			cathodes.erase(--(i.base()));
			break;
		}
	}
}

void ContinuousDischarge::processEvent(Event event, RenderWindow& window)
{
	if (Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!leftAlreadyPressed) {
			addCathode(Mouse::getPosition(window));
			leftAlreadyPressed = true;
		}
	}
	else
	{
		leftAlreadyPressed = false;
	}
	if (Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!rightAlreadyPressed)
		{
			removeCathode(Mouse::getPosition(window));
			rightAlreadyPressed = true;
		}
	}
	else
	{
		rightAlreadyPressed = false;
	}
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
	window.draw(anode);
	for (CircleShape c : cathodes)
		window.draw(c);
	window.draw(instruction1);
	window.draw(instruction2);
}

Display ContinuousDischarge::next()
{
	return nextDisplay;
}

