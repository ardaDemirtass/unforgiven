#pragma once
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
class Neuron 
{
private:
	double weight;
	double input;
	double output;
	double bias;
	string type;
	double toSigmoid(double x)
	{
		return x / (1.0f + abs(x));
	}
	double generateRandomWeight()
	{
		srand(69);
		return (double)rand() / (double)RAND_MAX;

	}

public:
	Neuron(string t) : type(t)
	{
		//þimdilik weight'e 2 verek
		this->weight = this->generateRandomWeight() * 10.0;
		this->input = 0.0f;
		this->output = 0.0f;
		this->bias = 0.0f;
	}
	double getWeight()
	{
		return this->weight;
	}
	void setWeight(double w)
	{
		this->weight = w;
	}
	double getInput()
	{
		return input;
	}
	double getOutput()
	{
		return this->output;
	}
	double getBias()
	{
		return this->bias;
	}
	void setBias(double b)
	{
		this->bias = b;
	}
	void setInput(double i)
	{
		this->input = i + this->bias;
		this->output = toSigmoid(this->input);
	}
	void setOutput()
	{
		this->output = this->toSigmoid(this->input);
	}
	string getType()
	{
		return this->type;
	}
};