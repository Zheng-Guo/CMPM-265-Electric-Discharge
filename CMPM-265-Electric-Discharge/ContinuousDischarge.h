#pragma once
#include <SFML\Graphics.hpp>
#include "Form.h"
#include "ElectricArc.h"

using namespace sf;
using namespace std;

class ContinuousDischarge: public Form
{
private:
	Text instruction1, instruction2,instruction3;
	Font font;
	Display nextDisplay;
	bool leftAlreadyPressed, rightAlreadyPressed;
	CircleShape anode;
	vector<CircleShape> cathodes;
	vector<shared_ptr<ElectricArc>> electricArcs;
	void addCathode(Vector2i p);
	void removeCathode(Vector2i p);
public:
	ContinuousDischarge(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
	nextDisplay(Display::Continuous), 
	leftAlreadyPressed(false),
	rightAlreadyPressed(false),
	anode(Continuous_Anode_Radius)
	{
		srand(time(NULL));
		anode.setOrigin(Continuous_Anode_Radius, Continuous_Anode_Radius);
		anode.setPosition(Continuous_Anode_X, Continuous_Anode_Y);
		anode.setFillColor(Color::Red);
		font.loadFromFile("Tinos-Regular.ttf");
		instruction1.setFont(font);
		instruction1.setString("Left click mouse anywhere on the screen to add an electrode.");
		instruction1.setCharacterSize(Instruction_Character_Size);
		instruction1.setFillColor(Color::Red);
		instruction1.setPosition(Menu_Instruction_X, Menu_Instruction_Y);
		instruction2.setFont(font);
		instruction2.setString("Right click on an electrode to remove it.");
		instruction2.setCharacterSize(Instruction_Character_Size);
		instruction2.setFillColor(Color::Red);
		instruction2.setPosition(Menu_Instruction_X, Menu_Instruction_Y+30);
		instruction3.setFont(font);
		instruction3.setString("Press Escape to return to menu.");
		instruction3.setCharacterSize(Instruction_Character_Size);
		instruction3.setFillColor(Color::Red);
		instruction3.setPosition(Menu_Instruction_X, Menu_Instruction_Y + 60);
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
	shared_ptr<ElectricArc> e = make_shared<ElectricArc>(anode.getPosition(), 0, 0, 3, 0);
	int amplitude = rand() % Amplitude_Margin + Amplitude_Base;
	e->setAmplitude(amplitude);
	e->setNoiseSeed(rand());
	e->setContinuous(true);
	e->setTargetPoint(Vector2f(p.x,p.y));
	e->buildArc();
	electricArcs.push_back(e);
}

void ContinuousDischarge::removeCathode(Vector2i p)
{
	for(vector<CircleShape>::reverse_iterator i=cathodes.rbegin();i!=cathodes.rend();++i)
	{
		float deltaX = i->getPosition().x - p.x, deltaY = i->getPosition().y - p.y;
		float distanceSquared = deltaX*deltaX + deltaY*deltaY;
		if(distanceSquared<Continuous_Anode_Radius*Continuous_Anode_Radius)
		{
			for(int j=0;j<electricArcs.size();++j)
			{
				if(electricArcs[j]->getTargetPoint()==i->getPosition())
				{
					electricArcs.erase(electricArcs.begin() + j);
					break;
				}
			}
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
	for (shared_ptr<ElectricArc> e : electricArcs)
		e->update(deltaTime);
}

void ContinuousDischarge::render(RenderWindow& window)
{
	for (shared_ptr<ElectricArc> e : electricArcs)
		e->draw(window);
	window.draw(anode);
	for (CircleShape c : cathodes)
		window.draw(c);
	window.draw(instruction1);
	window.draw(instruction2);
	window.draw(instruction3);
}

Display ContinuousDischarge::next()
{
	return nextDisplay;
}

