#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	(void)argv;
	if(argc==1)
	{
		system("./mirage_sdl & ./mirage_gtk");
	}
	return 0;
}