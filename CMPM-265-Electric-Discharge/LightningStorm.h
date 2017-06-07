#pragma once
#include <vector>
#include <memory>
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
	vector<shared_ptr<ElectricArc>> electricArcs;
	float interval;
public:
	LightningStorm(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
	nextDisplay(Display::Storm)
	{
		srand(time(NULL));
		interval = (rand() % Lightning_Interval_Limit) / 100.f;
		font.loadFromFile("Tinos-Regular.ttf");
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

void LightningStorm::processEvent(Event event, RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		nextDisplay = Display::Menu;
	}
}

void LightningStorm::update(float deltaTime)
{
	int i = 0;
	while(i<electricArcs.size())
	{
		if(electricArcs[i]->isVisible())
		{
			electricArcs[i]->update(deltaTime);
			++i;
		}
		else
		{
			electricArcs.erase(electricArcs.begin()+i);
		}
	}
	interval -= deltaTime;
	if(interval<=0)
	{
		interval = (rand() % Lightning_Interval_Limit) / 100.f;
		int sourceX = rand() % Lightning_X_Range + Lightning_X_Base;
		int direction = rand() % Lightning_Direction_Range + Lightning_Direction_Base;
		shared_ptr<ElectricArc> electricArc=make_shared<ElectricArc>(Vector2f(sourceX, Lightning_Y), direction, 600, 5, 0, false, Storm_Duration, Storm_Fading_Rate);
		int amplitude = rand() % Amplitude_Margin + Amplitude_Base;
		electricArc->setAmplitude(amplitude);
		electricArc->setNoiseSeed(rand());
		electricArc->buildArc();
		electricArcs.push_back(electricArc);
	}
	
}

void LightningStorm::render(RenderWindow& window)
{
	for (shared_ptr<ElectricArc> e : electricArcs)
		e->draw(window);
	window.draw(instruction2);
}

Display LightningStorm::next()
{
	return nextDisplay;
}