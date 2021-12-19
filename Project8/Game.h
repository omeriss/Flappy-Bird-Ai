#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <algorithm>
#include "Pipe.h"
#include "Bird.h"

using namespace std;

class Game
{
public:
	Game();
	// start the game
	virtual void Start() = 0;
	// load date: textures, fonts
	virtual void LoadData();
	// load the background
	virtual void LoadBackGround();
	// update sfml events
	virtual void UpdateEvents();
	// udpate the game
	virtual void Update(float deltaTime) = 0;
	// print the game on the screen
	virtual void Print() = 0;
	// update the pipe lists
	virtual void HandlePipes(float deltaTime, Bird* bird);

protected:
	sf::RenderWindow* window;

	float scale;

	sf::Texture backGroundTex;
	sf::Texture groundTex;
	sf::Texture BirdTex;
	sf::Texture PipeUPTex;
	sf::Texture PipeDownTex;

	sf::Font font;

	sf::Sprite backGround;
	sf::Sprite Ground;

	sf::Text scoreTxt;

	sf::Clock deltaClock;

	list<Pipe> beforePipeList;
	list<Pipe> afterPipeList;

	float timeFromPipes;
	float timeToSpawn;
	float pipeDis;
	int score;
};

class UserGame : public Game {
public:
	UserGame();
	void Start();
	void Print();
	void Update(float deltaTime);

private:
	Bird* bird;

};

class AiGame : public Game {
public:
	AiGame(string baseFile ="0", string saveFile = "0");
	void Start();
	void Print();
	void Update(float deltaTime);
	// mutate the birds
	void mutate();

private:
	// arr of ai birds
	AiBird** birds;
	int countDead = 0;
	string baseFile;
	string saveFile;
	// the birds to mutate
	vector<AiBird*> MutateBirds;

};

