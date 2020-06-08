#版本三
CC=g++
CFLAGS=-g -Wall
target=server
src=$(wildcard *.cpp)
obj=$(patsubst %.cpp, %.o, $(src))

$(target):$(obj)
	$(CC) $(CFLAGS)  $^ -o $@ -lpthread
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -lpthread
clean:
	rm -rf $(target) $(obj)
