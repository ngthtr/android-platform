#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>
const unsigned int CMD_PID = 123;

void handle_sigusr1(int sig)
{
    printf("Received SIGUSR1 signal from kernel, sig = %d!\n", sig);

    int fd = open("/dev/example_file", O_RDWR);
    const int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE);
    if (bytesRead == -1)
    {
        printf("Read example_file was failed\n");
        return;
    }

    // print the contents
    for (ssize_t i = 0; i < bytesRead; i++) {
        printf("%02x ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    close(fd); 
}

int main()
{
    int fd = open("/dev/example_file", O_RDWR);
    pid_t pid = getpid();
    printf("Current PID: %d\n", getpid());

    if (ioctl(fd, CMD_PID, getpid()) < 0)
    {
        printf("ioctl failed\n");
        return 0;
    }
    close(fd);

    if (signal(SIGUSR1, handle_sigusr1) == SIG_ERR) {
        perror("Error setting signal handler");
        exit(1);
    }

    while (1) {
        pause();  
    }

    return 0;
}
