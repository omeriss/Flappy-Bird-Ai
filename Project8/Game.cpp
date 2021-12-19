#include "Game.h"

Game::Game() {
	window = new sf::RenderWindow(sf::VideoMode(ScreenW, ScreenH), "FB");
}

void Game::LoadData() {
    if (!groundTex.loadFromFile("Ground.png"))
        cout << "can't load" << endl;
    if (!backGroundTex.loadFromFile("background-day.png"))
        cout << "can't load" << endl;
    if (!BirdTex.loadFromFile("Fbird.png"))
        cout << "can't load" << endl;
    if (!PipeUPTex.loadFromFile("pipe-up.png"))
        cout << "can't load" << endl;
    if (!PipeDownTex.loadFromFile("pipe-down.png"))
        cout << "can't load" << endl;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "cant load" << endl;
    }
}

void Game::LoadBackGround() {
    scale = ScreenH / (float)backGroundTex.getSize().y;
    backGround.setTexture(backGroundTex);
    backGround.setScale(scale, scale);
    Ground.setTexture(groundTex);
    Ground.setScale(scale, scale);
    Ground.setPosition(0, (backGroundTex.getSize().y - groundTex.getSize().y) * scale);
    scoreTxt.setPosition(ScreenW / 2, ScreenH / 15);
    scoreTxt.setFont(font);
    scoreTxt.setScale(scale , scale );
    scoreTxt.setString("0");
    scoreTxt.setOrigin(scoreTxt.getLocalBounds().width / 2, 0);
}

void Game::UpdateEvents() {
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Game::HandlePipes(float deltaTime, Bird* bird) {
    timeToSpawn -= deltaTime;

    if (timeToSpawn <= 0) {
        beforePipeList.push_back(Pipe(PipeDownTex, PipeUPTex, scale));
        timeToSpawn = timeFromPipes;
        timeFromPipes -= PipeSpwamRateInc;
        timeFromPipes = max(timeFromPipes, MinPipeRate);
    }

    for (auto i = beforePipeList.begin(); i != beforePipeList.end(); i++) {
        i->Update(deltaTime, 150);
    }

    for (auto i = afterPipeList.begin(); i != afterPipeList.end(); i++) {
        i->Update(deltaTime, 150);
    }

    if (beforePipeList.begin() != beforePipeList.end() && bird->PassedPipe(*beforePipeList.begin())) {
        afterPipeList.push_back(*beforePipeList.begin());
        beforePipeList.pop_front();
        score++;
        scoreTxt.setString(to_string(score));
        scoreTxt.setOrigin(scoreTxt.getLocalBounds().width / 2, 0);
    }

    if (afterPipeList.begin() != afterPipeList.end() && afterPipeList.begin()->GetEndPosition() < 0) {
        afterPipeList.pop_front();
    }
}

UserGame::UserGame():Game() {;
}

void UserGame::Print(){
    window->clear();
    window->draw(backGround);
    bird->PrintBird(*window);
    for (auto i = beforePipeList.begin(); i != beforePipeList.end(); i++) {
        i->PrintPipe(*window);
    }
    for (auto i = afterPipeList.begin(); i != afterPipeList.end(); i++) {
        i->PrintPipe(*window);
    }
    window->draw(Ground);
    window->draw(scoreTxt);
    window->display();
}

void UserGame::Update(float deltaTime) {

    if (beforePipeList.begin() != beforePipeList.end())
        bird->Update(deltaTime, &(*beforePipeList.begin()));
    else
        bird->Update(deltaTime, NULL);

    if (bird->Died()) {
        bird = new PlayerBird(BirdTex, scale);
        beforePipeList.clear();
        afterPipeList.clear();
        timeFromPipes = StartPipeSpawnRate;
        score = 0;
        scoreTxt.setString(to_string(score));
        scoreTxt.setOrigin(scoreTxt.getLocalBounds().width / 2, 0);
    }
}


void UserGame::Start() {
	LoadData();
    LoadBackGround();

    srand((unsigned)time(NULL));

    deltaClock.restart();
    window->setFramerateLimit(60 * Speed);

    timeFromPipes = StartPipeSpawnRate;
    timeToSpawn = 0;

    score = 0;

    bird = new PlayerBird(BirdTex, scale);

    while (window->isOpen())
    {
        UpdateEvents();
        float deltaTime = deltaClock.getElapsedTime().asSeconds();
        //cout << deltaTime << endl;
        deltaClock.restart();
        HandlePipes(deltaTime, bird);
        Update(deltaTime);
        Print();
    }
}

AiGame::AiGame(string baseFile , string saveFile):Game() {
    this->baseFile = baseFile;
    this->saveFile = saveFile;
}

void AiGame::Print() {
    window->clear();
    window->draw(backGround);
    for (int i = 0; i < NumOfAiBirds; i++) {
        if(!birds[i]->Died())
            birds[i]->PrintBird(*window);
    }
    for (auto i = beforePipeList.begin(); i != beforePipeList.end(); i++) {
        i->PrintPipe(*window);
    }
    for (auto i = afterPipeList.begin(); i != afterPipeList.end(); i++) {
        i->PrintPipe(*window);
    }
    window->draw(Ground);
    window->draw(scoreTxt);
    window->display();
}

void AiGame::mutate()
{
    int bestBird = MutateBirds.size() - 1;

    birds[NumOfBirdsToMutate] = new AiBird(BirdTex, scale, birds[NumOfBirdsToMutate - 1], 0);

    for (int j = 0; j < NumOfBirdsToMutate; j++) {
        birds[j] = new AiBird(BirdTex, scale, MutateBirds[j], 0);
    }

    if (score == 0) {
        for (int j = NumOfBirdsToMutate + 1; j < NumOfAiBirds / 4; j++) {
            birds[j] = new AiBird(BirdTex, scale);
        }
        for (int j = NumOfBirdsToMutate / 4; j < NumOfAiBirds / 2; j++) {
            birds[j] = new AiBird(BirdTex, scale, birds[NumOfBirdsToMutate], 20);
        }
        for (int j = NumOfAiBirds / 2; j < NumOfAiBirds; j++) {
            birds[j] = new AiBird(BirdTex, scale, MutateBirds[bestBird], 20);
        }
    }
    else {
        for (int j = NumOfBirdsToMutate + 1; j < NumOfAiBirds / 2; j++) {
            birds[j] = new AiBird(BirdTex, scale, MutateBirds[bestBird], 20);
        }
        for (int j = NumOfAiBirds / 2; j < NumOfAiBirds; j++) {
            birds[j] = new AiBird(BirdTex, scale, MutateBirds, 20);
        }
    }
}

void AiGame::Update(float deltaTime) {


    for (int i = 0; i < NumOfAiBirds; i++) {
        if (!birds[i]->Died()) {

            if (beforePipeList.begin() != beforePipeList.end())
                birds[i]->Update(deltaTime, &(*beforePipeList.begin()));
            else
                birds[i]->Update(deltaTime, NULL);

            if (birds[i]->Died()) {

                countDead++;

                cout << countDead << endl;

                if (countDead >= NumOfAiBirds - NumOfBirdsToMutate) {
                    MutateBirds.push_back(new AiBird(BirdTex, scale, birds[i], 0));
                }

                if (countDead == NumOfAiBirds - 1 && saveFile != "0") {
                    for (int i = 0; i < NumOfAiBirds; i++) {
                        if (!birds[i]->Died()) {
                            birds[i]->SaveToFile(saveFile);
                        }
                    }
                }
                if (countDead == NumOfAiBirds) {
                    cout << i << endl;

                    mutate();
                    /*
                    int bestBird = MutateBirds.size() - 1;

                    birds[NumOfBirdsToMutate] = new AiBird(BirdTex, scale, birds[NumOfBirdsToMutate-1], 0);

                    for (int j = 0; j < NumOfBirdsToMutate; j++) {
                        birds[j] = new AiBird(BirdTex, scale,MutateBirds[j], 0);
                    }

                    if (score == 0) {
                        for (int j = NumOfBirdsToMutate + 1; j < NumOfAiBirds / 4; j++) {
                            birds[j] = new AiBird(BirdTex, scale);
                        }
                        for (int j = NumOfBirdsToMutate/4; j < NumOfAiBirds /2; j++) {
                            birds[j] = new AiBird(BirdTex, scale, birds[NumOfBirdsToMutate], 20);
                        }
                        for (int j = NumOfAiBirds / 2; j < NumOfAiBirds; j++) {
                            birds[j] = new AiBird(BirdTex, scale, MutateBirds[bestBird], 20);
                        }
                    }
                    else {
                        for (int j = NumOfBirdsToMutate + 1; j < NumOfAiBirds / 2; j++) {
                            birds[j] = new AiBird(BirdTex, scale, MutateBirds[bestBird], 20);
                        }
                        for (int j = NumOfAiBirds / 2; j < NumOfAiBirds; j++) {
                            birds[j] = new AiBird(BirdTex, scale, MutateBirds, 20);
                        }
                    }
                    */
                    MutateBirds.clear();
                    beforePipeList.clear();
                    afterPipeList.clear();

                    if (score > 30 || timeFromPipes <=MinPipeRate) {
                        timeFromPipes = MinPipeRate;
                    }
                    else
                        timeFromPipes = StartPipeSpawnRate;

                    score = 0;
                    scoreTxt.setString(to_string(score));
                    scoreTxt.setOrigin(scoreTxt.getLocalBounds().width / 2, 0);

                    countDead = 0;
                    //deltaClock.restart();
                }
            }
        }
    }
}

void AiGame::Start() {
    LoadData();
    LoadBackGround();

    srand((unsigned)time(NULL));

    deltaClock.restart();
    window->setFramerateLimit(60 * Speed);

    timeFromPipes = StartPipeSpawnRate;
    timeToSpawn = 0;

    score = 0;


    birds = new AiBird*[NumOfAiBirds];

    for (int i = 0; i < NumOfAiBirds; i++) {
        if (baseFile != "0") {
            birds[i] = new AiBird(BirdTex, scale,baseFile);
        }
        else {
            birds[i] = new AiBird(BirdTex, scale);
        }
    }

    while (window->isOpen())
    {
        UpdateEvents();
        float deltaTime = deltaClock.getElapsedTime().asSeconds();
        //cout << deltaTime << endl;
        deltaClock.restart();
        HandlePipes(deltaTime * Speed, birds[0]);
        Update(deltaTime * Speed);
        Print();
    }
    
}
