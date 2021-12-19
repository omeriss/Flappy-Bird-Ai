#include "NeuralNetwork.h"

double inline GetRand() {
	return (rand() % 2001 - 1000.0) / 1000.0;
}

double inline func(double x) {
	return max(x, 0.0);
}

double inline GetModVal(double x, int change) {
	return x * (rand() % (change * 2 + 1) - (double)change + 100.0) / 100.0;
}

NeuralNetwork::NeuralNetwork() {

	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			bias[i][j] = GetRand();
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			inputW[i][j] = GetRand();
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				hiddenWs[k][i][j]= GetRand();
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			outputW[i][j] = GetRand();
		}
	}
}

NeuralNetwork::NeuralNetwork(string fileName) {

	std::ifstream file(fileName, std::ofstream::binary);
	if (!file) {
		cout << "cant open file\n";
		return;
	}

	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			file.read((char*)&bias[i][j], sizeof(double));
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			file.read((char*)&inputW[i][j], sizeof(double));
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				file.read((char*)&hiddenWs[k][i][j], sizeof(double));
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			file.read((char*)&outputW[i][j], sizeof(double));
		}
	}
}

NeuralNetwork::NeuralNetwork(NeuralNetwork* base, int change) {
	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			this->bias[i][j] = GetModVal(base->bias[i][j], change);
		}
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			inputW[i][j] = GetModVal(base->inputW[i][j], change);
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				hiddenWs[k][i][j] = GetModVal(base->hiddenWs[k][i][j], change);
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			outputW[i][j] = GetModVal(base->outputW[i][j], change);
		}
	}
}

NeuralNetwork::NeuralNetwork(vector<NeuralNetwork*> base, int change) {
	layers[0].resize(NumOfNodesInInput);
	layers[NumOfHiddenLayers + 1].resize(NumOfNodesInOutput);
	bias[NumOfHiddenLayers].resize(NumOfNodesInOutput);

	for (int i = 1; i <= NumOfHiddenLayers; i++) {
		layers[i].resize(NumOfNodesInHidden);
		bias[i - 1].resize(NumOfNodesInHidden);
	}

	int baseSize = base.size();

	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			bias[i][j] = GetModVal(base[rand() % baseSize]->bias[i][j], change);
		}
	}


	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			inputW[i][j] = GetModVal(base[rand() % baseSize]->inputW[i][j], change);
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				hiddenWs[k][i][j] = GetModVal(base[rand() % baseSize]->hiddenWs[k][i][j], change);
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			outputW[i][j] = GetModVal(base[rand() % baseSize]->outputW[i][j], change);
		}
	}
}

bool NeuralNetwork::Calc(double* input) {
	for (int i = 0; i < NumOfNodesInInput; i++) {
		layers[0][i] = input[i];
	}

	for (int i = 0; i < NumOfNodesInHidden; i++) {
		layers[1][i] = bias[0][i] = 0;
		for (int j = 0; j < NumOfNodesInInput; j++) {
			layers[1][i] += layers[0][j] * inputW[i][j];
		}
		layers[1][i] = func(layers[1][i]);
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			layers[k + 2][i] = bias[k + 1][i] = 0; // remove 0 for bias
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				layers[k + 2][i] += layers[k + 1][j] * hiddenWs[k][i][j];
			}
			layers[k + 2][i] = func(layers[k + 2][i]);
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		layers[NumOfHiddenLayers + 1][i] = bias[NumOfHiddenLayers][i] = 0;  // remove 0 for bias
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			layers[NumOfHiddenLayers + 1][i] += layers[NumOfHiddenLayers][j] * outputW[i][j];
		}
		layers[NumOfHiddenLayers + 1][i] = func(layers[NumOfHiddenLayers + 1][i]);
	}

	return layers[NumOfHiddenLayers + 1][0] > layers[NumOfHiddenLayers + 1][1];
}

void NeuralNetwork::SaveToFile(string fileName) {
	std::ofstream file(fileName, std::ofstream::binary);
	if(!file) {
		cout << "cant open file\n";
		return;
	}
	
	for (int i = 0; i <= NumOfHiddenLayers; i++) {
		int vlen = bias[i].size();
		for (int j = 0; j < vlen; j++) {
			file.write((const char*)&(bias[i][j]), sizeof(double));
		}
	}


	for (int i = 0; i < NumOfNodesInHidden; i++) {
		for (int j = 0; j < NumOfNodesInInput; j++) {
			file.write((const char*)&(inputW[i][j]), sizeof(double));
		}
	}

	for (int k = 0; k < NumOfHiddenLayers - 1; k++) {
		for (int i = 0; i < NumOfNodesInHidden; i++) {
			for (int j = 0; j < NumOfNodesInHidden; j++) {
				file.write((const char*)&(hiddenWs[k][i][j]), sizeof(double));
			}
		}
	}

	for (int i = 0; i < NumOfNodesInOutput; i++) {
		for (int j = 0; j < NumOfNodesInHidden; j++) {
			file.write((const char*)&(outputW[i][j]), sizeof(double));
		}
	}
}
