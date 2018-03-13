/*
 * Chip8.hpp
 *
 *  Created on: Feb 12, 2017
 *      Author: Phi
 *
 *      Using this as a reference
 *      http://mattmik.com/files/chip8/mastering/chip8.html
 */

#ifndef CHIP8_HPP_
#define CHIP8_HPP_

#include <iostream>
#include "stdint.h"
#include "stdio.h"


typedef struct{
	uint8_t V[16];	// General purpose registers. VF is carry Flag, don't use
	uint16_t I;		// Index. Store memory Addresses. Only lowest 12 bits are used.
	uint8_t DT; 	// Delay Timer
	uint8_t ST;		// Sound Timer

	uint16_t PC;	// Program Counter
	uint8_t	SP;		// Stack Pointer
	uint16_t S[16];	// Stack
} registers;

class Chip8 {
public:
	Chip8() {}
	auto initialize() -> void;
	auto instructions() -> void;
	auto read(uint16_t addr) -> uint8_t;
	auto write(uint16_t addr, uint8_t data) -> void;

	// Instructions
	auto CLS() -> void;
	auto RET() -> void;
	auto JP(uint16_t opcode) -> void;
	auto CALL(uint16_t opcode) -> void;
	auto SE_VX_BYTE(uint16_t opcode) -> void;
	auto SNE(uint16_t opcode) -> void;
	auto SE_VX_VY(uint16_t opcode) -> void;
	auto LD_VX_BYTE(uint16_t opcode) -> void;
	auto ADD_VX_BYTE(uint16_t opcode) -> void;
	auto LD_VX_VY(uint16_t opcode) -> void;
	auto OR_VX_VY(uint16_t opcode) -> void;
	auto AND_VX_VY(uint16_t opcode) -> void;
	auto XOR_VX_VY(uint16_t opcode) -> void;
	auto ADD_VX_VY(uint16_t opcode) -> void;
	auto SUB_VX_VY(uint16_t opcode) -> void;
	auto SHR_VX(uint16_t opcode) -> void;
	auto SUBN_VY_VX(uint16_t opcode) -> void;
	auto SHL_VX(uint16_t opcode) -> void;
	auto SNE_VX_VY(uint16_t opcode) -> void;
	auto LD_I_ADDR(uint16_t opcode) -> void;
	auto JP_VO_ADDR(uint16_t opcode) -> void;
	auto RND_VS_BYTE(uint16_t opcode) -> void;
	auto DRW_VX_VY_NIB(uint16_t opcode) -> void;

	registers reg;
	uint8_t c_memory[0x1000];		// 4096 memory locations
	uint8_t gfx_display[64*32];		// 64 x 32 pixel monochrome display
	uint8_t key_input[16];			// 16-key hex keypad
};

#endif /* CHIP8_HPP_ */
