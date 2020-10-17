#include "header.h"
#define PORT 2267

int main(void)
{
	int sockfd1, sockfd2;
	char buf[256];
	struct sockaddr_in servAddr, clitAddr;
	int stringLen;
	int clitLen;

	if((sockfd1 = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket Error");
		exit(1);
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd1, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
	{
		perror("Bind Error");
		exit(1);
	}

	if(listen(sockfd1, 5) < 0)
	{
		perror("Listen Error");
		exit(1);
	}

	while(1)
	{
		clitLen = sizeof(clitAddr);
		if((sockfd2 = accept(sockfd1, (struct sockaddr*) &clitAddr, &clitLen)) < 0)
		{
			perror("Accept Error");
			exit(1);
		}

		if(recv(sockfd2, buf, sizeof(buf), 0) < 0)
		{
			perror("Receive Error");
			exit(1);
		}

		if(send(sockfd2, buf, sizeof(buf), 0) < 0)
		{
			perror("Send Error");
			exit(1);
		}
	}

	return 0;
}


