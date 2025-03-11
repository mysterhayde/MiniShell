#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int g_sig;

void handler(int signal)
{
	printf("Signal %d received\n", signal);
}

int main(void)
{
	struct sigaction sa;
	int byte_read;
	char buffer[70000];

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (1);
	}
	while (1)
	{
		byte_read = read(0, buffer, 70000);
		buffer[byte_read] = '\0';
		printf("%s\n", buffer);
		if (byte_read == 0)
			return (0);
	}
	return (0);
}