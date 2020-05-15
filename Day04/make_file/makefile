CC=g++
CFLAGS=-g -Wall
target=app
src=$(wildcard *.cpp)
obj=$(patsubst %.cpp, %.o, $(src))

$(target):$(obj)
	$(CC) $(CFLAGS)  $^ -o $@
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -rf $(target) $(obj)