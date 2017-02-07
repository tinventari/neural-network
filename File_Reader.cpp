#include"File_Reader.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

File_Reader::File_Reader()
{

}

File_Reader::~File_Reader()
{
		
}


int File_Reader::Get_Dimension()
{
	cv::Mat imageMat = cv::imread(sizeim, CV_LOAD_IMAGE_COLOR);

	if (imageMat.empty())
	{
		int e = 2;
		throw e;
		return -1;
	}

	int r= imageMat.rows;
	int c= imageMat.cols;
	imageMat.release();
	return r*c;
}


void File_Reader::Read_Expected(vector<int> & expected)
{
	
	ifstream file;
	file.open(expect);
	int temp;
	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> temp;
			expected.push_back(temp);
		}
		file.close();
	}
	else
	{
		int e = 1;
		throw e;
	}

}

