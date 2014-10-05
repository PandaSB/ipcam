all: 
	g++ test.cpp gpioclass.cpp ipcamclass.cpp -lcurl -o test
clean:
	rm test
