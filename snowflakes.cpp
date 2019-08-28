#include <iostream>

#include "Environment.h"
#include "HexGrid.h"

void show_usage(void) {
	// TODO
	std::cout<<"./snowflakes "<<std::endl;
}

int main(int argc, char* argv[]) {
	float init_condition = 1.0;

	HexGrid grid(init_condition);

	grid.print();
}