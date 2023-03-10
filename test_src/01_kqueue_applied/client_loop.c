#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(void)
{
	int sock = 0; long valread;
	struct sockaddr_in serv_addr;
	char *message = "GET";
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses text form to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	int cnt = 0;
	while (1)
	{
		write(sock, message, 14);
//		send(sock, message, strlen(message), 0);
		printf("------------------message sent-------------------\n");
		valread = read(sock, buffer, 33);
		printf("%s\n", buffer);
//		printf("------------------message received-------------------\n");
		usleep(3 * 1000 * 1000);
	}
//	system("netstat -an | grep 8090");
	close(sock);
	return 0;
}
