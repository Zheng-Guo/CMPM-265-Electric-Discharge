#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include "Form.h"
#include "Constants.h"

using namespace sf;
using namespace std;

class MainMenu : public Form
{
private:
	vector<Text> optionText;
	Text instruction1, instruction2;
	Font font;
	int currentSelection;
	Display nextDisplay;
public:
	MainMenu(int windowWidth = 100, int windowHeight = 100) :Form(windowWidth, windowHeight),
		currentSelection(0),
		nextDisplay(Display::Menu)
	{
		font.loadFromFile("Tinos-Regular.ttf");
		Text text;
		text.setFont(font);
		text.setString("Electric Arc Demo");
		text.setCharacterSize(Menu_Option_Character_Size);
		text.setPosition(Menu_Option_X, Menu_Option_Initial_Y + optionText.size()*Menu_Option_Interval);
		optionText.push_back(text);
		text.setString("Lightning Storm");
		text.setPosition(Menu_Option_X, Menu_Option_Initial_Y + optionText.size()*Menu_Option_Interval);
		optionText.push_back(text);
		text.setString("Continuous Discharge");
		text.setPosition(Menu_Option_X, Menu_Option_Initial_Y + optionText.size()*Menu_Option_Interval);
		optionText.push_back(text);
		instruction1.setFont(font);
		instruction1.setString("Press Up/Down arrow key to select the display.");
		instruction1.setCharacterSize(Instruction_Character_Size);
		instruction1.setFillColor(Color::White);
		instruction1.setPosition(Menu_Instruction_X, Menu_Instruction_Y);
		instruction2.setFont(font);
		instruction2.setString("Press Enter to select the menu.");
		instruction2.setCharacterSize(Instruction_Character_Size);
		instruction2.setFillColor(Color::White);
		instruction2.setPosition(Menu_Instruction_X, Menu_Instruction_Y + 30);
	}
	virtual void processEvent(Event event, RenderWindow& window) override;
	virtual void update(float deltaTime) override;
	virtual void render(RenderWindow &window) override;
	virtual Display next() override;
};

void MainMenu::processEvent(Event event, RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (currentSelection > 0)
			--currentSelection;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (currentSelection < optionText.size() - 1)
			++currentSelection;
	}
	if (Keyboard::isKeyPressed(Keyboard::Return)) {
		if (currentSelection == 0)
			nextDisplay = Display::Demo;
		if (currentSelection == 1)
			nextDisplay = Display::Storm;
		if (currentSelection == 2)
			nextDisplay = Display::Continuous;
	}
}

void MainMenu::update(float deltaTime)
{

}

void MainMenu::render(RenderWindow& window)
{
	for (int i = 0; i < optionText.size(); ++i) {
		if (i == currentSelection)
			optionText[i].setFillColor(Color::Red);
		else
			optionText[i].setFillColor(Color::White);
		window.draw(optionText[i]);
	}
	window.draw(instruction1);
	window.draw(instruction2);
}

Display MainMenu::next()
{
	return nextDisplay;
}
