#ifndef MYSOCKET
#define MYSOCKET

#define BUFFER_SIZE 100
#define SOMAXCONN 128 // 最大监听队列长度

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
class mySocket {
	int listenfd, socklen, clientfd;
	struct sockaddr_in serveraddr, client_addr;
	char buffer[BUFFER_SIZE];
	void errif(bool condition, const char* errmsg);

	public:
	~mySocket();
	int init(int port);
	int connect();
	int readInt(int* re);
	int sendInt(int se);
};

#endif
