#pragma once
#include <memory>
#include <cstdlib>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "MainMenu.h"
#include "ElectricArcDemo.h"

using namespace sf;
using namespace std;

class ElectricDischarge
{
private:
	RenderWindow window;
	Clock clock;
	Time time1, time2, time3;
	Display currentDisplay;
	shared_ptr<Form> currentForm;
public:
	ElectricDischarge():window(VideoMode(Window_Width, Window_Height), "Electric Discharge", Style::Close | Style::Titlebar)
	{
		window.setPosition(Vector2i(100, 100));
		currentForm = make_shared<MainMenu>(Window_Width, Window_Height);
		srand(time(NULL));
	}
	void run();
};

void ElectricDischarge::run()
{
	time1 = clock.getElapsedTime();
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			currentForm->processEvent(event);
			if (currentDisplay != currentForm->next())
			{
				currentDisplay = currentForm->next();
				switch (currentDisplay)
				{
				case Display::Menu: currentForm = make_shared<MainMenu>(Window_Width, Window_Height); break;
				case Display::Demo: currentForm = make_shared<ElectricArcDemo>(Window_Width, Window_Height); break;
				//case Display::LightningStorm: currentForm = make_shared<DissolvingEffectDisplay>(Window_Width, Window_Height); break;
				}
			}
		}
		time3 = clock.getElapsedTime();
		time2 = time3 - time1;
		time1 = time3;
		window.clear();
		currentForm->update(time2.asSeconds());
		currentForm->render(window);
		window.display();
	}
}
