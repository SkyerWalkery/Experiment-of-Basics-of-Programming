main: main.o AnaStr.o File.o Other.o Table.o 
	g++ -o main main.o AnaStr.o File.o Other.o Table.o -g
main.o: main.cpp
	g++ -c -o main.o main.cpp
AnaStr.o: AnaStr.cpp
	g++ -c -o AnaStr.o AnaStr.cpp
File.o: File.cpp
	g++ -c -o File.o File.cpp
Other.o: Other.cpp
	g++ -c -o Other.o Other.cpp
Table.o: Table.cpp
	g++ -c -o Table.o Table.cpp
clean:  
	rm -f *.o 




