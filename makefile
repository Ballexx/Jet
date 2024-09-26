output: server.o request.o main.o
	g++ obj/server.o obj/request.o obj/main.o -o run

server.o: server.cpp
	g++ -c server.cpp -o obj/server.o

request.o: request.cpp 
	g++ -c request.cpp -o obj/request.o

main.o : main.cpp
	g++ -c main.cpp -o obj/main.o

clean:
	rm *.o output