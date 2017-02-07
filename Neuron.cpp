#include"Neuron.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Neuron::Neuron()
{

}

Neuron::~Neuron()
{
	
}
	
void Neuron::Set_Weights(vector<Synapsis> & weights, int size)
{
	Synapsis weight;
	for (int n = 0; n < size; ++n)
	weights.push_back(weight);
}

void Neuron::Initialize_Weights()
{
	for (int n = 0; n < this->weights.size(); ++n)
		this->weights[n].weight = ((float)rand() / ((float)(RAND_MAX)+(float)(1)))-0.5;
}

Synapsis::~Synapsis()
{
	
}

Synapsis::Synapsis()
{

}