#pragma once
#include"Neuron.h"

class Layer
{

	friend class Network;
public:
	~Layer();

private:
	

	vector<Neuron> layer;

	Layer(int number_final);
	void Push_Layer(const vector<Neuron> &temp_layer);
};