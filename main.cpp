//============================================================================
// Name        : chip8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Chip8.hpp"
using namespace std;

int main() {
	// Main game emulator loop goes here
	uint16_t i =  0x0A00;
	uint8_t j = (i & 0x0F00);
	cout << (int)j;
	return 0;
}
