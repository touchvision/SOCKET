
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_PORT 5555

int main()
{
	int serverSocket;
	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int addr_len = sizeof(clientAddr);
	int client;
	char buffer[200];
	int iDataNum;

	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind");
		return 1;
	}

	if(listen(serverSocket, 5) < 0)
	{
		perror("listen");
		return 1;
	}

	while(1)
	{
		printf("Listening on port: %d\n", SERVER_PORT);
		client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
		if(client < 0)
		{
			perror("accept");
			continue;
		}
		printf("\nrecv client data...n");
		printf("IP is %s\n", inet_ntoa(clientAddr.sin_addr));
		printf("Port is %d\n", htons(clientAddr.sin_port));
		while(1)
		{
			iDataNum = recv(client, buffer, 1024, 0);
			if(iDataNum < 0)
			{
				perror("recv");
				continue;
			}
			buffer[iDataNum] = '\0';
			if(strcmp(buffer, "quit") == 0)
				break;
			printf("%drecv data is %s\n", iDataNum, buffer);
			send(client, buffer, iDataNum, 0);
		}
	}
	return 0;
}
