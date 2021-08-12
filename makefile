
all: clean executable clean

executable: main
			g++ *.o -o main
main:
			g++ -c *.cpp
clean:
			rm -rf *.o
			rm -rf main