#include "Pipe.h"
#include <iostream>

Pipe::Pipe(sf::Texture& PipeDownTex, sf::Texture& UpPipeTex, float scale) {
	pipeDis = 100 * scale;

	int rnd = std::rand();
	hight = rnd % (int)((ScreenH/4)*3 - pipeDis - 40 * scale)  + pipeDis + 20 * scale;

	position = ScreenW;
	PipeDown.setTexture(PipeDownTex);
	PipeDown.setScale(scale, scale);
	PipeDown.setOrigin(0, PipeDownTex.getSize().y);
	PipeUp.setTexture(UpPipeTex);
	PipeUp.setScale(scale, scale);

	PipeUp.setPosition(position, hight);
	PipeDown.setPosition(position, hight - pipeDis);
}

void Pipe::Update(float deltaTime, float pipeSpeed) {
	position -= pipeSpeed * deltaTime * PipeDown.getScale().x;
	PipeUp.setPosition(position, PipeUp.getPosition().y);
	PipeDown.setPosition(position, PipeDown.getPosition().y);
}

void Pipe::PrintPipe(sf::RenderWindow& wnd) {
	wnd.draw(PipeUp);
	wnd.draw(PipeDown);
}