#include "header.h"
#define STR_SIZE 100

int main(int argc, char* argv[])
{
	struct sockaddr_in addr;
	char str[STR_SIZE];
	char buf[256];
	int stringLen;
	int sockfd;
	int filefd;
	char* servIP;
	int servPort;

	
	if(argc != 3)
	{
		printf("<Usage>: ./client <IP> <PORT>\n");
		exit(1);
	}

	servIP = argv[1];
	servPort = atoi(argv[2]);

	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket Error");
		exit(1);
	}

	memset(&addr, 0, sizeof(addr)); // initialize 0 in sin_zeros[8]
	addr.sin_family = PF_INET;
	addr.sin_port = htons(servPort);
	addr.sin_addr.s_addr = inet_addr(servIP);

	if(connect(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
	{
		perror("Connect Error");
		exit(1);
	}

	fgets(str, STR_SIZE, stdin);
	stringLen = strlen(str);
	if(send(sockfd, str, stringLen, 0) < 0)
	{
		perror("Send Error");
		exit(1);
	}

	if(recv(sockfd, buf, stringLen, 0) < 0)
	{
		perror("Receive Error");
		exit(1);
	}
	
	filefd = creat("result", 0644);
	write(filefd, buf, stringLen);
	close(filefd);
	close(sockfd);
	return 0;
}	
