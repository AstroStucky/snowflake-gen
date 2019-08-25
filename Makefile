CXX=g++
CXX_FLAGS=-std=c++11 -g -Wall

snowflakes: snowflakes.o
	g++ -o $@

obj/%.o: %.cpp obj
	g++ -c $^ -o $@ 

obj:
	mkdir -p obj

clean:
	rm obj/* snowflakes

.PHONY: clean