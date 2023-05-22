#include <thread>
#include <cstdio>

#include "src/mySocket.h"
int main() {
	mySocket a;
	int rec = a.init(9999);
	printf("%d", rec);
	return 0;
}
