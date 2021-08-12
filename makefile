
all: clean executable clean

executable: components main
			g++ *.o -o main
main:
			g++ -c *.cpp

components: 
			g++ -c componentes/*.cpp

clean:
			rm -rf *.o
			rm -rf main