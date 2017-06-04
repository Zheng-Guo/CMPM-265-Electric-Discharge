#include <SFML/Graphics.hpp>
#include <noise/noise.h>
#include <iostream>

int main()
{
	noise::module::Perlin myModule;

	double v = myModule.GetValue(0.5, 0.5, 0.5);

	std::cout << v << std::endl;
	system("pause");
	return 0;
}
