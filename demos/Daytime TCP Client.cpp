#include "types.h"
#include <iostream>

int main()
{
	int res;
	
#ifdef WIN32
	// Initialize Winsock
	WSADATA wsaData;
	res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		printf("WSAStartup failed: %d\n", res);
		return 1;
	}
#endif

	// Create a SOCKET for connecting to server
	int Socket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));
	if (Socket <= 0) {
		printf("Error at socket()\n");
		return 1;
	}

	// The sockaddr_in structure specifies the address family, IP address, and port of the server to be connected to
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("129.6.15.28");
	servaddr.sin_port = htons(13);

	// Connect to server
	res = connect(Socket, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));
	if (res < 0) {
		printf("Unable to connect to server\n");
		return 1;
	}

	// Receive until the peer closes the connection
	const int MAXLINE = 256;
	char recvbuf[MAXLINE + 1];
	do {
		res = recv(Socket, recvbuf, MAXLINE, 0);
		if (res > 0) {
			recvbuf[res] = 0;
			printf("%s\n", recvbuf);
		}
		else if (res == 0)
			printf("Connection closed\n");
		else
			printf("Error at recv()\n");

	} while (res > 0);

	return 0;
}
