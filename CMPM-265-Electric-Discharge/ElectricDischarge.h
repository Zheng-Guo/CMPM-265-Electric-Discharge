#pragma once
#include <cstdlib>
#include <ctime>
#include <SFML\Graphics.hpp>
#include "Constants.h"

using namespace sf;
using namespace std;

class ElectricDischarge
{
private:
	RenderWindow window;
	Clock clock;
	Time time1, time2, time3;
public:
	ElectricDischarge():window(VideoMode(Window_Width, Window_Height), "Particle Systems", Style::Close | Style::Titlebar)
	{
		window.setPosition(Vector2i(100, 100));
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
		}
		time3 = clock.getElapsedTime();
		time2 = time3 - time1;
		time1 = time3;
		window.clear();
		window.display();
	}
}
