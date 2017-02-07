#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define expect "expected.txt"
#define sizeim "0.bmp"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "Neuron.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"


using namespace std;


class File_Reader
{
public:

	int width;
	int height;
	vector <int> expected;
	File_Reader();
	~File_Reader();
	
	void Read_Expected(vector<int> & expected);
	int Get_Dimension();

};