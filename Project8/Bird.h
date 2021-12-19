#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Constants.h"
#include "Pipe.h"
#include "NeuralNetwork.h"


// base virtual bird class
class Bird
{
public:
	Bird(sf::Texture& BirdTex, float scale);
	// print the bird on the screen
	void PrintBird(sf::RenderWindow& wnd);
	// update the bird
	void Update(float deltaTime, Pipe* nextPipe);
	// check if the bird is collided with the pipe
	bool IsCollided(Pipe* nextPipe);
	// return if the bird passed the pipe
	bool PassedPipe(Pipe& pipe);
	// retue if the bird is dead
	bool Died() { return isDead; };
	
protected:
	bool isDead;
	sf::Sprite birdSprite;
	virtual bool IsJumping(Pipe* nextPipe) = 0;
	float velocity;
	float r;

};

// player bird
class PlayerBird :public Bird {
public:
	PlayerBird(sf::Texture& BirdTex, float scale);
private:
	bool IsJumping(Pipe* nextPipe);
	bool jmpLastFrame;
};

// ai bird
class AiBird :public Bird {
public:
	AiBird(sf::Texture& BirdTex, float scale);
	AiBird(sf::Texture& BirdTex, float scale, AiBird* base, int change);
	AiBird(sf::Texture& BirdTex, float scale, vector<AiBird*> base, int change);
	AiBird(sf::Texture& BirdTex, float scale, string fileName);
	// save the nn to a file
	void SaveToFile(string fileName);
private:
	bool IsJumping(Pipe* nextPipe);
	NeuralNetwork* network;
};
