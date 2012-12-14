#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	struct flock f1 = { F_WRLCK, SEEK_SET, 0, 0, 0 };
	int fd;
	
	f1.l_pid = getpid();
	
	if(argc > 1)
		f1.l_type = F_RDLCK;
		
	if((fd = open("lockdemo.c", O_RDWR)) == -1)
	{
		perror("open");
		exit(1);
	}
	
	printf("Press <RETURN> to try to get lock: ");
	getchar();
	printf("Trying to get lock...");
	
	if(fcntl(fd, F_SETLKW, &f1) == -1)
	{
		perror("fcntl");
		exit(1);
	}
	
	printf("got lock\n");
	printf("Press <RETURN> to release lock: ");
	getchar();
	
	f1.l_type = F_UNLCK;
	
	if(fcntl(fd, F_SETLK, &f1) == -1) 
	{
		perror("fcntl");
		exit(1);
	}
	
	printf("Unlocked.\n");
	
	close(fd);
	
	return 0;
}
