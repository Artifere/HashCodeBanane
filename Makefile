# the compiler: gcc for C program, define as g++ for C++
 	CC= g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
	CFLAGS= -O2 -s -Wall

  # the build target executable:
	TARGET= test
	SRC= *.cpp

all:	$(TARGET)

$(TARGET):	$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	$(RM) $(TARGET)
