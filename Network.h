#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include"Neuron.h"
#include"Layer.h"
#include"Network.h"
#include"File_Reader.h"
#include<conio.h>


#define n_output 10
#define n_hidden 37

class Network
{
public:
	void Learn(float step, float lmse, int files, float momentum);
	int Call(int file);
	bool Test();
	Network();
	~Network();
private:
	float error;
	float step = 1;
	float momentum=0.4;
	int count;

	vector<int> n_neurons;
	vector<Layer> network;
	vector<int> expected;

	File_Reader read;
	
	void Push_Network(vector<Layer> &temp_network);
	void Randomize();
	bool Populate(int number);
	void Calculate();
	void Calc_Error();
	void Back_Prop();
	void Adjust_Weights();
	void Run(int count);
	
	
};