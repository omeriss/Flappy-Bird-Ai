#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define NumOfHiddenLayers 2
#define NumOfNodesInHidden 8
#define NumOfNodesInInput 5
#define NumOfNodesInOutput 2

typedef double HiddenW[NumOfNodesInHidden][NumOfNodesInHidden];

// input: 
// bird h
// down pipe h
// up pipe h
// bird speed
// bird dis to pipe

// output:
// 1. jump
// 2. not to jump

class NeuralNetwork
{
public:
	vector<double> layers[NumOfHiddenLayers+2];
	vector<double> bias[NumOfHiddenLayers+1];
	double inputW[NumOfNodesInHidden][NumOfNodesInInput];
	double outputW[NumOfNodesInOutput][NumOfNodesInHidden];
	HiddenW hiddenWs[NumOfHiddenLayers - 1];
	NeuralNetwork();
	NeuralNetwork(string fileName);
	NeuralNetwork(NeuralNetwork* base, int change);
	NeuralNetwork(vector<NeuralNetwork*> base, int change);
	// calc the nn
	bool Calc(double* input);
	// save the nn to a file
	void SaveToFile(string fileName);
};

