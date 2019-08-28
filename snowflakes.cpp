#include <iostream>
#include <chrono>
 
#include "HexGrid.h"

static const bool DEBUG = true;

void show_usage(void) {
	std::cout<<"./snowflakes "<<std::endl;
}

int main(int argc, char* argv[]) {
	float init_condition = 1.0;

	HexGrid grid(init_condition);	

	if (DEBUG) grid.print();

	for (int i = 0; i < 100; i++ ) {
		// Record start time
		auto start = std::chrono::high_resolution_clock::now();
		grid.process_all();
		// Record end time
		auto end = std::chrono::high_resolution_clock::now();
		if (DEBUG) grid.print();
		std::chrono::duration<double> elapsed = end - start;
		if (DEBUG) std::cout<<"Elapsed time: "<<elapsed.count()<<"s"<<std::endl;
	}
	return 0;
}