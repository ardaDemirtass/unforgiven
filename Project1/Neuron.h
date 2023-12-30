#pragma once
#include <stdlib.h>
#include <iostream>

using namespace std;
class Neuron 
{
private:
	double weight;
	double input;
	double output;
	string type;
	double toSigmoid(double x)
	{
		return x / (1.0f + abs(x));
	}

public:
	Neuron(string t) : type(t)
	{
		//þimdilik weight'e 2 verek
		this->weight = 2.0f;
		this->input = 0.0f;
		this->output = 0.0f;
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
	void setInput(double i)
	{
		this->input = i;
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