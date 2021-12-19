#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include <cstdlib>
#include "Constants.h"


class Pipe
{
public:
	Pipe(sf::Texture& PipeDownTex, sf::Texture& UpPipeTex, float scale);
	// update the pipe
	void Update(float deltaTime, float PipeSpeed);
	// print the pipe
	void PrintPipe(sf::RenderWindow& wnd);
	float GetEndPosition() { return position + PipeDown.getScale().x * PipeDown.getTexture()->getSize().x; }
	float GetStartPosition() { return position; }
	float GetHight() { return hight; }
	float GetDis() { return pipeDis; }


private:
	float position;
	float hight;
	float pipeDis;
	sf::Sprite PipeDown;
	sf::Sprite PipeUp;
};

