#include "Bird.h"

Bird::Bird(sf::Texture& BirdTex, float scale) {
	birdSprite.setTexture(BirdTex);
	birdSprite.setOrigin(BirdTex.getSize().x / 2, BirdTex.getSize().y / 2);
	birdSprite.setPosition(ScreenW/4, ScreenH/2);
	birdSprite.setScale(scale, scale);
	r = BirdTex.getSize().x * scale / 2;
	velocity = 0;
	isDead = false;
}

void Bird::PrintBird(sf::RenderWindow& wnd) {
	wnd.draw(birdSprite);
}

bool Bird::IsCollided(Pipe* nextPipe) {
	if (nextPipe && birdSprite.getPosition().x + r >= nextPipe->GetStartPosition() && nextPipe->GetEndPosition() >= birdSprite.getPosition().x - r) {
		return (birdSprite.getPosition().y + r*0.7 > nextPipe->GetHight() || birdSprite.getPosition().y - r*0.7 < nextPipe->GetHight() - nextPipe->GetDis());
	}
	return birdSprite.getPosition().y > 400 * birdSprite.getScale().x || birdSprite.getPosition().y < r;
}

void Bird::Update(float deltaTime, Pipe* nextPipe) {
	if (IsJumping(nextPipe))
		velocity = JmpSpeed;
	else
		velocity -= deltaTime * Gravity;

	if (velocity > 0)
		birdSprite.setRotation(-20);
	else
		birdSprite.setRotation(std::min(-20 - velocity / 10, 80.0f));

	birdSprite.setPosition(birdSprite.getPosition().x, birdSprite.getPosition().y - velocity * deltaTime * birdSprite.getScale().x);

	if (IsCollided(nextPipe)) {
		isDead = true;
	}
}

bool Bird::PassedPipe(Pipe& pipe) {
	return pipe.GetEndPosition() < birdSprite.getPosition().x - r;
}

PlayerBird::PlayerBird(sf::Texture& BirdTex, float scale):Bird(BirdTex, scale) {
	jmpLastFrame = false;
}

bool PlayerBird::IsJumping(Pipe* nextPipe) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (jmpLastFrame)
			return false;
		return jmpLastFrame = true;
	}
	else
		jmpLastFrame = false;
	return false;
}

AiBird::AiBird(sf::Texture& BirdTex, float scale) :Bird(BirdTex, scale) {
	network = new NeuralNetwork();
}

AiBird::AiBird(sf::Texture& BirdTex, float scale, AiBird* base, int change) : Bird(BirdTex, scale) {
	network = new NeuralNetwork(base->network, change);
}

AiBird::AiBird(sf::Texture& BirdTex, float scale, vector<AiBird*> base, int change) : Bird(BirdTex, scale) {
	vector<NeuralNetwork*> baseN;
	for (auto u : base) {
		baseN.push_back(u->network);
	}
	network = new NeuralNetwork(baseN, change);
}


AiBird::AiBird(sf::Texture& BirdTex, float scale, string fileName) : Bird(BirdTex, scale) {
	network = new NeuralNetwork(fileName);
}

bool AiBird::IsJumping(Pipe* nextPipe) {
	if (nextPipe) {
		double AiInput[] = {birdSprite.getPosition().y/birdSprite.getScale().x, velocity, nextPipe->GetHight() / birdSprite.getScale().x, (nextPipe->GetHight() + nextPipe->GetDis()) / birdSprite.getScale().x,(nextPipe->GetEndPosition() - birdSprite.getPosition().x) / birdSprite.getScale().x };
		return network->Calc(AiInput);
	}
	double AiInput[] = { birdSprite.getPosition().y / birdSprite.getScale().x, velocity, ScreenH/ 2 / birdSprite.getScale().x, (ScreenH / 2 + 100* birdSprite.getScale().x) / birdSprite.getScale().x,(ScreenW - birdSprite.getPosition().x) / birdSprite.getScale().x };
	return network->Calc(AiInput);
}

void AiBird::SaveToFile(string fileName) {
	network->SaveToFile(fileName);
}

