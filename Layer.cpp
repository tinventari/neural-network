#include"Layer.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Layer::Layer(int number_final)
{
	vector<Neuron> temp_layer;
	for (int number = 1; number <= number_final; ++number)
	{
		Neuron temp;
		temp_layer.push_back(temp);
		
	}
	Push_Layer(temp_layer);

	temp_layer.clear();
}

Layer::~Layer()
{

}

void Layer::Push_Layer(const vector<Neuron> &temp_layer)
{
	this->layer = temp_layer;
	
}
