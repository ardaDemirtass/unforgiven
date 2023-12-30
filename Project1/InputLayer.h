#pragma once
#include <stdlib.h>
#include <vector>
#include "Neuron.h"
#include <string>
#include <iostream>
#include "Layer.h"

class InputLayer : public Layer
{
public:
	InputLayer(size_t non, string t) : Layer(non, t){}
};