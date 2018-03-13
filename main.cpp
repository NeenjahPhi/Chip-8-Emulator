//============================================================================
// Name        : chip8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Chip8.hpp"
#include "stdio.h"
using namespace std;

int main() {
	// Main game emulator loop goes here
	Chip8 chip8;
	chip8.initialize();
	chip8.reg.V[3] = 5;
	chip8.reg.V[5] = 8;
	chip8.SUBN_VY_VX(0x835E);
	std::cout << (int) chip8.reg.V[3] << std::endl;
	return 0;
}
