#include"Network.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

Network::~Network()
{
	
}

Network::Network()
{
	try 
	{
		//read->Read_Expected(expected);
		read.Read_Expected(expected);
	}
	catch (int e)
	{
		cerr << "Error occured reading the expected values file. Error number " << e<< endl;
		system("PAUSE");
		exit(1);
	}

	try
	{
		//n_neurons.push_back(read->Get_Dimension());
		n_neurons.push_back(read.Get_Dimension());
	}

	catch (int e)
	{
		cerr << "Error occured reading image " << sizeim << " to get dimensions of the images. Error number " << e << endl;
		system("PAUSE");
		exit(2);
	}

	n_neurons.push_back(n_hidden);
	n_neurons.push_back(n_output);

	vector<Layer> temp_network;
	Layer input_layer(n_neurons[0]);
	temp_network.push_back(input_layer);

	for (int size = 1; size < n_neurons.size() - 1; ++size)
	{
		Layer temp(n_neurons[size]);
		temp_network.push_back(temp);
	}

	Layer output_layer(n_neurons[n_neurons.size() - 1]);
	temp_network.push_back(output_layer);
	Push_Network(temp_network);
	
	temp_network.clear();
}

void Network::Push_Network(vector<Layer> &temp_network)
{
	this->network = temp_network;
}

void Network::Randomize()
{
	for (int i = 0; i < n_neurons.size() - 1; ++i)
	{
		for (int j = 0; j < n_neurons[i]; ++j)
		{
			int n = n_neurons[i + 1];

			{
				network[i].layer[j].Set_Weights(network[i].layer[j].weights, n);
				network[i].layer[j].Initialize_Weights();
				network[i].layer[j].Set_Weights(network[i].layer[j].prev_weights, n);
			}
		}
	}
}

bool Network::Populate(int number)
{
	string tmp;
	string name;

	sprintf((char*)name.c_str(), "%d", number);
	name = name.c_str();
	name = name + ".bmp";

	cv::Mat imageMat = cv::imread(name, CV_LOAD_IMAGE_COLOR);

	if (imageMat.empty())
	{
		int e = 10;
		throw e;
	}

	cv::Mat grayscaleMat(imageMat.size(), CV_8U);

	cv::cvtColor(imageMat, grayscaleMat, CV_BGR2GRAY);

	cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());

	float k;
	int m = grayscaleMat.cols;

	for (int i = 0; i <grayscaleMat.rows; i++)
	{
		for (int j = 0; j < m; j++)
		{
			k = grayscaleMat.at<char>(i, j);
			if (k < 0)
				k *= -1;

			network[0].layer[i*m + j].Value = k;
		}

	}

	binaryMat.release();
	grayscaleMat.release();
	imageMat.release();

	return 0;
}

void Network::Calculate()
{
	for (int i = 1; i < n_neurons.size(); ++i)
	{
		for (int j = 0; j < n_neurons[i]; ++j)
		{
			network[i].layer[j].Value = 0;

			for (int n = 0; n < n_neurons[i - 1]; n++)
			{
				network[i].layer[j].Value += network[i - 1].layer[n].Value * network[i - 1].layer[n].weights[j].weight;
			}

			network[i].layer[j].Value = f(network[i].layer[j].Value);

		}
	}
}

void Network::Calc_Error()
{

	for (int i = 0; i <n_neurons[n_neurons.size() - 1]; ++i)
	{
		if (i != expected[count])
		{
			network[n_neurons.size() - 1].layer[i].Delta = (0 - network[n_neurons.size() - 1].layer[i].Value)*fprim(network[n_neurons.size() - 1].layer[i].Value);
			error += pow((0 - network[n_neurons.size() - 1].layer[i].Value), 2);
		}

		else
		{
			network[n_neurons.size() - 1].layer[i].Delta = (1 - network[n_neurons.size() - 1].layer[i].Value)*fprim(network[n_neurons.size() - 1].layer[i].Value);
			error += pow((1 - network[n_neurons.size() - 1].layer[i].Value), 2);
		}
	}
}

void Network::Back_Prop()
{

	for (int i = n_neurons.size() - 2; i > 0; --i)
	{
		for (int j = 0; j < n_neurons[i]; ++j)
		{
			network[i].layer[j].Delta = 0;

			for (int n = 0; n < network[i + 1].layer.size(); ++n)
			{

				network[i].layer[j].Delta += network[i + 1].layer[n].Delta * network[i].layer[j].weights[n].weight;

			}

			network[i].layer[j].Delta *= fprim(network[i].layer[j].Value);

		}

	}

}

void Network::Adjust_Weights()
{
	vector<Synapsis>temp_weights;

	for (int i = 0; i < n_neurons.size() - 1; ++i)
	{
		for (int j = 0; j < n_neurons[i]; ++j)
		{

			network[i].layer[j].prev_weights = network[i].layer[i].weights;

		}
	}



	for (int i = 0; i < n_neurons.size() - 1; ++i)
	{
		for (int j = 0; j < n_neurons[i]; ++j)
		{
			temp_weights = network[i].layer[j].weights;

			for (int n = 0; n < network[i].layer[j].weights.size(); ++n)
			{

				network[i].layer[j].weights[n].weight += (momentum*(network[i].layer[j].weights[n].weight
					- network[i].layer[j].prev_weights[n].weight)
					+ step*network[i].layer[j].Value*network[i + 1].layer[n].Delta);

			}

			network[i].layer[j].prev_weights = temp_weights;

		}

	}
	temp_weights.clear();

}

void Network::Run(int count)
{
	Populate(count);
	Calculate();
	Calc_Error();
	Back_Prop();
	Adjust_Weights();
}

void Network::Learn(float step2, float lmse, int files, float momentum2)
{

	float mse = 1;
	int epochs = 0;
	step = step2;
	momentum = momentum2;

	cout << "Press any key to stop" << endl;
	clock_t start = clock();
	Randomize();

	while (mse > lmse && !_kbhit())
	{
		mse = 0;

		while (count < files)
		{
			Run(count);
			mse += error / (n_neurons[n_neurons.size() - 1] + 1);
			error = 0;
			epochs++;
			count++;

		}
		count = 0;
		cout << "mse: " << mse << endl;
	}
	clock_t end = clock();
	system("CLS");
	cout << "mse: " << mse << endl;
	cout << "Epochs: "<< epochs << endl;
	cout << endl << "Network leaarned in: " << (end - start) / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

bool Network::Test()
{
	signed int l = 0;
	int num;

	cout << "Enter the name of bitmap which you want to check, -1 to leave: ";
	cin >> l;

	while (l != -1)
	{
		try
		{
			num = Call(l);
		}

		catch (int e)
		{
			
			cerr << "Error occured reading the image, error code " << e << endl;
			cin >> l;
			continue;
		}

		cout << "The image shows number " << num;
		cout.precision(3);
		cout << " with certainty " << network[n_neurons.size() - 1].layer[num].Value * 100 << "%" << endl;
		
		cin >> l;
	}

	return 1;
}

int Network::Call(int file)
{
	try
	{
		Populate(file);
	}
	catch (int e)
	{
		throw e;
		return -1;
	}

	Calculate();

	float max = 0;
	int num = 0;
	for (int i = 0; i < n_neurons[n_neurons.size() - 1]; ++i)
	{
		if (network[n_neurons.size() - 1].layer[i].Value > max)
		{
			max = network[n_neurons.size() - 1].layer[i].Value;
			num = i;

		}
	}

	return num;
}