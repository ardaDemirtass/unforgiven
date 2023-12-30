#pragma once
#include <stdlib.h>
#include <vector>
#include "Neuron.h"
#include <string>
#include <iostream>
using namespace std;

class Layer
{
protected:
	vector<Neuron> Neurons;
	size_t numberOfNeurons;
	string type;

private:
	void addNeurons()
	{
		for (size_t i = 0; i < numberOfNeurons; i++)
		{
			this->Neurons.push_back(Neuron(this->type));
		}
	}

public:
	Layer(size_t non, string t) : numberOfNeurons(non), type(t) {
		this->addNeurons();
	}
	vector<Neuron> &getNeurons()
	{
		return this->Neurons;
	}
	size_t getNumberOfNeurons()
	{
		return this->numberOfNeurons;
	}
	string getType()
	{
		return this->type;
	}
};
