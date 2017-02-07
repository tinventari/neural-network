
#define _CRTDBG_MAP_ALLOC
#include"Network.h"
#include<windows.h>
#include <stdlib.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif


int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));

	Network Net;
	
	Net.Learn(1, 0.01, 22, 0);

	Net.Test();
	
	system("pause");

	return 0;
}
