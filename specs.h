/*
 * cpu.h
 *
 *  Created on: Feb 12, 2017
 *      Author: Phi
 */

#ifndef SPECS_H_
#define SPECS_H_

#include "stdint.h"


uint8_t c_memory[0x0FFF];

uint8_t gfx_display[64*32];	// 64 x 32 pixel monochrome display

uint8_t key_input[16];	// 16-key hex keypad

typedef struct{
	uint8_t V[16];	// General purpose registers. VF is carry Flag, don't use
	uint16_t I;		// Index. Store memory Addresses. Only lowest 12 bits are used.
	uint8_t DT; 	// Delay Timer
	uint8_t ST;		// Sound Timer

	uint16_t PC;	// Program Counter
	uint8_t	SP;		// Stack Pointer
	uint16_t S[16];	// Stack
} registers;


#endif /* SPECS_H_ */
