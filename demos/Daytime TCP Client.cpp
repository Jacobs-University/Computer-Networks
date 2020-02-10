#include <iostream>
#include <WinSock2.h>

int main()
{
	// Initialize Winsock
	WSADATA wsaData;
	int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (res != NO_ERROR) {
		printf("WSAStartup failed: %d\n", res);
		return 1;
	}

	// Create a SOCKET for connecting to server
	SOCKET Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// The sockaddr_in structure specifies the address family, IP address, and port of the server to be connected to
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("129.6.15.28");
	servaddr.sin_port = htons(13);

	// Connect to server
	res = connect(Socket, (SOCKADDR*) &servaddr, sizeof(servaddr));
	if (res == SOCKET_ERROR) {
		closesocket(Socket);
		printf("Unable to connect to server: %ld\n", WSAGetLastError());
		WSACleanup();
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
			printf("recv failed: %d\n", WSAGetLastError());

	} while (res > 0);

	// cleanup
	closesocket(Socket);
	WSACleanup();

	return 0;
}