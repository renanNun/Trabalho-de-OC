TARGET=main

CC=g++

OBJS=*.o

RM= rm -rf

all: clean exec main 
		

main:
		$(CC) $(OBJS) -o $(TARGET)
exec: 
		$(CC) -c Sources/*.cpp
			
clean:
			$(RM) *.o
			$(RM) main