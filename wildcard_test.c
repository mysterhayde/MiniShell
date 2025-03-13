#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	DIR *dir;
	struct dirent *readed;

	dir = opendir("/home/hdougoud/Documents/MiniShell");
	if (dir == NULL)
	{
		perror("open dir failed");
		return (0);
	}
	for (int i = 0; i < 15; i++)
	{
		readed = readdir(dir);
		if (readed == NULL)
		{
			perror("readed failed");
			return (0);
		}
		printf("%d	", readed->d_type);
		printf("%s\n", readed->d_name);
	}
	return (1);
}