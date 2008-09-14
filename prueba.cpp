#include <stdlib.h>
#include <iostream>
#include <dirent.h>

int main(int argc, char *argv[])
{
	int i = chdir(argv[1]);

	char cwd[255];

	getcwd(cwd, 255);

	printf("%d Current: %s\n", i, cwd);
	return 0;
}
