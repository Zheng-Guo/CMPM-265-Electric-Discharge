#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <noise/noise.h>
#include "Matrix.h"
#include "Constants.h"

using namespace std;
using namespace sf;
using namespace noise;

class ElectricArc
{
private:
	Vector2f sourcePoint;
	float direction, length;
	vector<Vector2f> arcPath;
	float arcThickness;
	bool applyNoise;
	int branchingProbability;
	vector<shared_ptr<ElectricArc>> branches;
public:
	ElectricArc(Vector2f s = Vector2f(0, 0), float d=0,float l=10,float a = 1) :sourcePoint(s),
	direction(d),
	length(l),
	arcThickness(a),
	applyNoise(false),
	branchingProbability(0)
	{
		buildArc();
	}
	void buildArc();
	void setApplyNoise(bool b) { applyNoise = b; }
	void setBranchingProbability(int i) { branchingProbability = i; }
	void draw(RenderWindow &window);
};

void ElectricArc::buildArc()
{
	if(applyNoise)
	{
		
	}
	else
	{
		float x = sourcePoint.x;
		while(x-sourcePoint.x<=length)
		{
			arcPath.push_back(Vector2f(x, sourcePoint.y));
			x += 1;
		}
	}
}

void ElectricArc::draw(RenderWindow& window)
{
	for(Vector2f p:arcPath)
	{
		CircleShape c(arcThickness);
		c.setPosition(p);
		c.setFillColor(Color::White);
		c.setOutlineColor(Color::White);
		window.draw(c);
	}
	for (shared_ptr<ElectricArc> a : branches)
		a->draw(window);
}

