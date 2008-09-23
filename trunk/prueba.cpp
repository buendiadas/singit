#include <stdlib.h>
#include <iostream>
#include <dirent.h>

using namespace std;

int varGlobal;

class Prueba
{
	public:
	Prueba()
	{
		varGlobal = 1;
	}
};

int main(int argc, char *argv[])
{
	Prueba p;

	printf("Var global: %d\n", varGlobal);

	return 0;
}

