#pragma once
#include <stdlib.h>
#include <iostream>
#include "Layer.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"

using namespace std;

class Network
{
private:
	vector<Layer> layers;
	double prediction;
	double loss;
	size_t numberOfLayers;
public:
	Network()
	{
		this->loss = 0;
		this->numberOfLayers = 0;
		this->prediction = 0;
	}
	vector<Layer> getLayers() 
	{
		return this->layers;
	}
	void addInputLayer(size_t non) 
	{
		this->layers.push_back(InputLayer(non, "InputLayer"));
		this->numberOfLayers += 1;
	}
	void addHiddenLayer(size_t non)
	{
		this->layers.push_back(HiddenLayer(non, "HiddenLayer"));
		this->numberOfLayers += 1;
	}
	void addOutpuLayer(size_t non)
	{
		this->layers.push_back(OutputLayer(non, "OutputLayer"));
		this->numberOfLayers += 1;
	}
	void learn(vector<double> x, vector<double> y, size_t epoch)
	{
		for (size_t i = 0; i < epoch; i++)
		{
			this->loss = 0;
				for (size_t l = 0; l < this->layers.size(); l++)
				{
					Layer layer = this->layers[l];
					vector<Neuron> neurons = layer.getNeurons();
					for (size_t n = 0; n < neurons.size(); n++)
					{
						if (l == 0)
						{
							for (size_t d = 0; d < x.size(); d++)
							{
								neurons[n].setInput(x[d]);
							}
						}
						else
						{
							Layer preLayer = this->layers[l - 1];
							double neuronInput = 0;
							for (size_t n = 0; n < preLayer.getNeurons().size(); n++)
							{
								neuronInput += preLayer.getNeurons()[n].getOutput() * preLayer.getNeurons()[n].getWeight();
							}
							neurons[n].setInput(neuronInput);
							neurons[n].setOutput();
							if (l == this->layers.size() - 1)
							{
								this->prediction = neurons[n].getOutput();
							}
						}
					}
				}	
		}
	}
	void predict(double value)
	{
		for (size_t l = 0; l < this->numberOfLayers; l++)
		{
			for (size_t n = 0; n < this->layers[l].getNumberOfNeurons(); n++)
			{
				if (this->layers[l].getType() == "InputLayer")
				{
					Layer lr = this->layers[l];
					lr.getNeurons()[n].setInput(value);
					this->layers[l] = lr;
				}
				else
				{
					Layer preLayer = this->layers[l - 1];
					for (size_t prevN = 0; prevN < preLayer.getNumberOfNeurons(); prevN++)
					{
						this->layers[l].getNeurons()[n].setInput(this->layers[l].getNeurons()[n].getInput() + preLayer.getNeurons()[prevN].getWeight() * preLayer.getNeurons()[prevN].getInput());
					}
				}
				cout << "noron anlik deger : " << this->layers[l].getNeurons()[n].getInput() << " noron tipi : " << this->layers[l].getNeurons()[n].getType() << endl;
			}
		}
		Layer outLayer = this->layers[this->numberOfLayers - 1];
		Neuron outNeuron = outLayer.getNeurons()[outLayer.getNumberOfNeurons() - 1];
		this->prediction = outNeuron.getOutput();
	}
	double getPrediction()
	{
		return this->prediction;
	}
	void displayNetwork()
	{
		for (size_t l = 0; l < this->numberOfLayers; l++)
		{
			cout << this->layers[l].getType() << "     ";
		}
		cout << endl;
		for (size_t l = 0; l < this->numberOfLayers; l++)
		{
			cout << this->layers[l].getNumberOfNeurons() << "               ";
		}
	}
};