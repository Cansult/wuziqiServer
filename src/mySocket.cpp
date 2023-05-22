#include "mySocket.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

mySocket::~mySocket() {
	close(listenfd);
}

void mySocket::errif(bool condition, const char* errmsg) {
	if (condition) {
		perror(errmsg);
		exit(EXIT_FAILURE);
	}
}

int mySocket::init(int port) {
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	/*
AF_INET: ipv4
SOCK_STREAM: 面向连接
0: TCP
	 */
	errif(listenfd == -1, "Failed to create socket");
	puts("Socket success");

	memset(&serveraddr, 0, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // or = inet_addr("127.0.0.1");
	serveraddr.sin_port = htons(port);

	errif(bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0 ,
			"Failed to bind");
	puts("Bind success");

	errif(listen(listenfd, SOMAXCONN) != 0, "Failed to listen");
	puts("Listen success");
	return 0;
}

int mySocket::connect() {
	socklen = sizeof(struct sockaddr_in);
	clientfd = accept(listenfd, (struct sockaddr*)&client_addr, (socklen_t*)&socklen);
	errif(clientfd == -1, "Failed to connect");
	printf("Client %s has connected", inet_ntoa(client_addr.sin_addr));
	return 0;
}

int mySocket::readInt(int* re) {
	int iret = recv(clientfd, buffer, sizeof(buffer), 0);
	if (iret == 0) 
		return -1;
	*re = 0;
	for (int i = 0; i < iret; i++) 
		*re = *re * 10 + buffer[i] - '0';
	return 0;
}

int mySocket::sendInt(int se) {
	int size = 0;
	do {
		buffer[size++] = se % 10 + '0';
		se /= 10;
	} while (se > 0);
	int iset = send(clientfd, buffer, size, 0);
	errif(iset == 0, "Failed to send");
	return 0;
}
