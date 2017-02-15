/*
 * Chip8.hpp
 *
 *  Created on: Feb 12, 2017
 *      Author: Phi
 */

#ifndef CHIP8_HPP_
#define CHIP8_HPP_

#include "specs.h"

class Chip8 {
public:
	auto initialize() -> void;
	auto instructions() -> void;
	auto read(uint16_t addr) -> uint8_t;
	auto write(uint16_t addr, uint8_t data) -> void;
private:
	registers reg;
};

void Chip8::initialize() {
	reg.PC = 0x200;
	reg.SP = 0;
	reg.I = 0;
	reg.DT = 0;
	reg.ST = 0;

	for (uint8_t i : gfx_display) {
		gfx_display[i] = 0;
	}
}

void Chip8::instructions() {
	uint16_t opcode = ( c_memory[reg.PC] << 8 | c_memory[++reg.PC] );

	switch(opcode) {

	}
}


uint8_t Chip8::read(uint16_t addr) {
	return c_memory[addr];
}

void Chip8::write(uint16_t addr, uint8_t data) {
	c_memory[addr] = data;
}

#endif /* CHIP8_HPP_ */
