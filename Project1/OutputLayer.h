#pragma once
#include <stdlib.h>
#include <vector>
#include "Neuron.h"
#include <string>
#include <iostream>
#include "Layer.h"

class OutputLayer : public Layer
{
public:
	OutputLayer(size_t non, string t) : Layer(non, t) {};
};