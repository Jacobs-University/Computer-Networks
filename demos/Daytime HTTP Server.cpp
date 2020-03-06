#include "types.h"
#include <iostream>
#include <time.h>

int main()
{
	const bool plainText = false;
	
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(80);

	// Bind socket
	res = bind(Socket, reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));
	if (res < 0) {
		printf("Error at bind()\n");
		return 1;
	}
	
	// Wait for connections
	res = listen(Socket, SOMAXCONN);
	if (res < 0) {
		printf("Error at listen()\n");
		return 1;
	}

	// Serving the clients
	struct sockaddr_in cliaddr;
	memset(&cliaddr, 0, sizeof(cliaddr));
	socklen_t cliaddr_len = sizeof(cliaddr);
	for (;;) {
		int connfd = static_cast<int>(accept(Socket, reinterpret_cast<sockaddr*>(&cliaddr), &cliaddr_len));
		printf("Connection from %s\n", inet_ntoa(cliaddr.sin_addr));

		time_t ticks = time(nullptr);
		std::string timeString(ctime(&ticks));
		timeString += "\n";
		
		std::string buff;
		// Jest sending the time
		//buff = timeString;

		// HTML page with time
		buff = "<!DOCTYPE html>\n";
		buff += "<html lang=\"en\">\n";
		buff += "<head>\n";
		buff += "  <meta charset=\"utf-8\">\n";
		buff += "  <title>CN Time Server</title>\n";
		buff += "</head>\n";
		buff += "<body>\n";
		buff += "  <h1 align='center'>The current time in Jacobs University:</h1>\n";
		buff += "  <h2 align='center'>" + timeString + "</h2>\n";
		buff += "</body>\n";
		buff += "</html>\n";

		std::string http = "HTTP/1.1 200 OK\n";
		http = http + "Content-Length: " + std::to_string(buff.size()) + "\n";
		if (plainText) {
			http += "Content-Type: text/plain; charset=utf-8\n\n";
		}
		else {
			http += "Content-Type: text/html; charset=utf-8\n\n";
		}
			
		http += buff;
		send(connfd, http.c_str(), http.size(), 0);
		

#ifdef WIN32
		closesocket(connfd);
#else
		close(connfd);
#endif
	}


	return 0;
}


