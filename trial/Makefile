# the compiler: gcc for C program, define as g++ for C++
 	CC= g++

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
	CFLAGS= -std=c++11 -O2 -s -Wall

  # the build target executable:
	TARGET= uuu
	SRC= essai1.cpp

all:	$(TARGET)

$(TARGET):	$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	$(RM) $(TARGET)
