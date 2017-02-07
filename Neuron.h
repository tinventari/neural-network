#pragma once

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<ctime>

#define f(x)  1/(1+(exp(-x)))
#define fprim(x) f(x)*(1-f(x))

using namespace std;

class Synapsis
{
	friend class Neuron;
	friend class Layer;
	friend class Network;

private:
	float weight;

public:
	~Synapsis();
	Synapsis();
};

class Neuron
{
	friend class Layer;
	friend class Network;

public:
	~Neuron();

private:	
	vector<Synapsis> weights;
	vector<Synapsis> prev_weights;

	Neuron();

	void Set_Weights(vector<Synapsis> & weights, int size);
	void Initialize_Weights();
	float Value;
	float Delta;
};