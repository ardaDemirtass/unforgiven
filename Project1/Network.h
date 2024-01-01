#pragma once
#include <stdlib.h>
#include <iostream>
#include "Layer.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "Neuron.h"

using namespace std;

class Network
{
private:
	vector<Layer> layers;
	size_t numberOfLayers;
	double calcCost(vector<double> xtrain, vector<double> ytrain)
	{
		double cost = 0;
		for (size_t x = 0; x < xtrain.size(); x++)
		{
			cost += (this->predict(xtrain[x]) - ytrain[x]) * (this->predict(xtrain[x]) - ytrain[x]);
		}
		return cost / xtrain.size();
	}
public:
	Network()
	{
		this->numberOfLayers = 0;
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
	void learn(vector<double> xtrain, vector<double> ytrain, size_t epoch)
	{
		vector<Layer> newLayers = this->getLayers();
		double e = 1e-3;
		for (size_t ep = 0; ep < epoch; ep++)
		{
			double cost = this->calcCost(xtrain, ytrain);
			cout << "epoch : " << ep << "  cost : " << cost << "  " << endl;
			for (size_t x = 0; x < xtrain.size(); x++)
			{
				for (size_t l = 0; l < this->numberOfLayers; l++)
				{
					Layer& currentLayer = this->layers[l];
					Layer& newCurrentLayer = newLayers[l];
					for (size_t n = 0; n < currentLayer.getNumberOfNeurons(); n++)
					{
						//cout << "leyer : " << l << "neuron : " << n << endl;
						Neuron& neuron = currentLayer.getNeurons()[n];
						Neuron& newNeuron = newCurrentLayer.getNeurons()[n];
						double cost = this->calcCost(xtrain, ytrain);
						double saved = neuron.getWeight();
						neuron.setWeight(neuron.getWeight() + e);
						newNeuron.setWeight((this->calcCost(xtrain, ytrain) - cost) / e);
						neuron.setWeight(saved);
						//cout << "neuron : " << neuron.getWeight() << endl;
					}
				}
				this->resetInputs();
			}
			this->changeWeight(newLayers);
		}
	}
	void changeWeight(vector<Layer> newLayers)
	{
		double rate = 1e-1;
		for (size_t l = 0; l < this->numberOfLayers; l++)
		{
			Layer& currentLayer = this->layers[l];
			Layer newCurrentLayer = newLayers[l];
			for (size_t n = 0; n < currentLayer.getNumberOfNeurons(); n++)
			{
				Neuron& neuron = currentLayer.getNeurons()[n];
				Neuron newNeuron = newCurrentLayer.getNeurons()[n];
				neuron.setWeight(neuron.getWeight() - rate * newNeuron.getWeight());
			}
		}
	}
	void resetInputs()
	{
		for (size_t l = 0; l < this->numberOfLayers; l++)
		{
			Layer& currentLayer = this->layers[l];
			for (size_t n = 0; n < this->layers[l].getNumberOfNeurons(); n++)
			{
				currentLayer.getNeurons()[n].setInput(0);
			}
		};
	}
	double predict(double value)
	{
		this->resetInputs();
		for (size_t l = 0; l < this->numberOfLayers; l++)
		{
			Layer& currentLayer = this->layers[l];
			for (size_t n = 0; n < this->layers[l].getNumberOfNeurons(); n++)
			{
				if (this->layers[l].getType() == "InputLayer")
				{
					//Layer lr = this->layers[l];
					currentLayer.getNeurons()[n].setInput(value);
				}
				else
				{
					Layer& preLayer = this->layers[l - 1];
					for (size_t prevN = 0; prevN < preLayer.getNumberOfNeurons(); prevN++)
					{
						currentLayer.getNeurons()[n].setInput(currentLayer.getNeurons()[n].getInput() + preLayer.getNeurons()[prevN].getWeight() * preLayer.getNeurons()[prevN].getOutput());
					}
				}
				//cout << "noron anlik deger : " << currentLayer.getNeurons()[n].getInput() << " noron tipi : " << currentLayer.getNeurons()[n].getType() << endl;
			}
		}
		Layer& outLayer = this->layers[this->numberOfLayers - 1];
		Neuron& outNeuron = outLayer.getNeurons()[outLayer.getNumberOfNeurons() - 1];
		//this->prediction = outNeuron.getInput();
		return outNeuron.getOutput();
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
	void setLayers(vector<Layer> layers)
	{
		this->layers = layers;
	}
};