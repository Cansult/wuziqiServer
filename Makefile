src=$(wildcard src/*.cpp)

main:
	g++ -std=c++11 -pthread -g \
	$(src) \
	main.cpp \
	-o main

th:
	g++ -pthread src/ThreadPool.cpp ThreadPoolTest.cpp -o ThreadPoolTest

test:
	g++ src/util.cpp src/Buffer.cpp src/Socket.cpp src/ThreadPool.cpp \
	-pthread \
	test.cpp -o test

clean:
	rm main && rm test
