CXX=g++
CXX_FLAGS=-std=c++11 -g -Wall

snowflakes: obj/snowflakes.o obj/Cell.o obj/HexGrid.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ 

obj/%.o: %.cpp obj
	$(CXX) $(CXX_FLAGS) -c $< -o $@ 

obj:
	mkdir -p obj

clean:
	rm obj/* snowflakes

.PHONY: clean