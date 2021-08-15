TARGET=main

CC=g++

OBJS=*.o

RM= rm -rf

all: exec main clean
		

main:
		$(CC) $(OBJS) -o $(TARGET)
exec: 
		$(CC) -c *.cpp
			
clean:
			$(RM) *.o