
#include "Chip8.hpp"

void Chip8::initialize() {
	reg.PC = 0x200;
	reg.SP = 0;
	reg.I = 0;
	reg.DT = 0;
	reg.ST = 0;

	// init graphics display
	for (int i = 0; i < 64*32; i++) {
		gfx_display[i] = 0;
	}

	// init memory
	for (int i = 0; i < 0x200; i++) {
		c_memory[i] = 0;
	}

	// init keypad
	for (int i = 0; i < 16; i++) {
		key_input[i] = 0;
	}

	// init the general purpose registers
	for (int i = 0; i < 16; i++) {
		reg.V[i] = 0;
	}

}

auto Chip8::instructions() -> void {
	// Fetch, 2 bytes long, stored big endian
	uint16_t opcode = ( (c_memory[reg.PC] << 8) | c_memory[reg.PC + 1] );

	// Decode and Execute
	switch(opcode & 0xF000) {
		case 0x0000:
			switch(opcode & 0x000F) {
				// 0x00E0 Clear Screen
				case 0x0000:	CLS(); 		break;
				// 0x00EE Return from subroutine
				case 0x000E:	RET(); 		break;

				default:
					printf("Unknown opcode 0x%X\n", opcode);
			}
		break;

		// 0x1nnn Jump to address nnn
		case 0x1000:	JP(opcode);				break;

		// 0x2NNN Call subroutine at nnn
		case 0x2000:	CALL(opcode);			break;

		// 0x3kkk Skips the next instruction if Vx = kk
		case 0x3000:	SE_VX_BYTE(opcode);		break;

		// 0x4xkk Skips the next instruction if vx != kk
		case 0x4000:	SNE(opcode);			break;

		// 0x5xy0 Skip next instruction if vx = vy.
		case 0x5000:	SE_VX_VY(opcode);		break;

		// 0x6xkk Set vx = kk
		case 0x6000:	LD_VX_BYTE(opcode);		break;

		// 0x7xkk Set vx = vx + kk
		case 0x7000:	ADD_VX_BYTE(opcode);	break;

		case 0x8000:
			switch(opcode & 0x000F) {
				// 0x8xy0 Set Vx = Vy
				case 0x0000:	 LD_VX_VY(opcode);			break;

				// 0x8xy1 Set Vx = Vx OR Vy
				case 0x0001: 	 OR_VX_VY(opcode);			break;

				// 0x8xy2 Set Vx = Vx AND Vy
				case 0x0002: 	 AND_VX_VY(opcode);			break;

				// 0x8xy3 Set Vx = Vx XOR Vy
				case 0x0003: 	 XOR_VX_VY(opcode);			break;

				// 0x8xy4 Set Vx = Vx + Vy, set VF = carry
				case 0x0004:	 ADD_VX_VY(opcode);			break;

				// 0x8xy5 Set Vx = Vx - Vy, set VF = NOT borrow
				case 0x0005:	 SUB_VX_VY(opcode);			break;

				// 0x8xy6 Set Vx = Vx SHR 1
				case 0x0006:	 SHR_VX(opcode); 			break;

				// 0x8xy7 Set Vx = Vy - Vx, set VF = NOT borrow
				case 0x0007:	 SUBN_VY_VX(opcode); 		break;

				// 0x8xyE Set Vx = Vx SHL 1
				case 0x000E: 	 SHL_VX(opcode);			break;

				default:
					printf("Unknown opcode 0x%X\n", opcode);
			}
		break;

		// TODO: FINISH LISTING OPCODES
		case 0x9000:	SNE_VX_VY(opcode);		break;

		case 0xA000:	LD_I_ADDR(opcode);		break;

		case 0xB000:	JP_VO_ADDR(opcode);		break;

		case 0xC000:	RND_VS_BYTE(opcode);	break;

		case 0xD000:	break;

		case 0xE000:	break;

		case 0xF000:	break;
	}

}

auto Chip8::CLS() -> void {
	for (int i = 0; i < 64*32; i++) {
		gfx_display[i] = 0;
	}
	reg.PC += 2;
}

auto Chip8::RET() -> void {
	reg.PC = reg.S[reg.SP--];
}

auto Chip8::JP(uint16_t opcode) -> void {
	reg.PC = (opcode & 0x0FFF);
}

auto Chip8::CALL(uint16_t opcode) -> void {
	reg.S[++reg.SP] = reg.PC;
	reg.PC = (opcode & 0x0FFF);
}

auto Chip8::SE_VX_BYTE(uint16_t opcode) -> void {
	if ( reg.V[ (opcode & 0x0F00) >> 8 ] == (opcode & 0x00FF) ) {
		reg.PC += 4;
	}
	else {
		reg.PC += 2;
	}
}

auto Chip8::SNE(uint16_t opcode) -> void {
	if ( reg.V[ (opcode & 0x0F00) >> 8 ] != (opcode & 0x00FF) ) {
		reg.PC += 4;
	}
	else {
		reg.PC += 2;
	}
}

auto Chip8::SE_VX_VY(uint16_t opcode) -> void {
	if ( reg.V[ (opcode & 0x0F00) >> 8] == (opcode & 0x00F0)) {
		reg.PC += 4;
	}
	else {
		reg.PC += 2;
	}
}

auto Chip8::LD_VX_BYTE(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) >> 8 ] = (opcode & 0x00FF);
	reg.PC += 2;
}

auto Chip8::ADD_VX_BYTE(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) >> 8 ] += (opcode & 0x00FF);
	reg.PC += 2;
}

auto Chip8::LD_VX_VY(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) >> 8] = reg.V[ (opcode & 0x00F0) >> 4];
	reg.PC += 2;
}

auto Chip8::OR_VX_VY(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) >> 8] |= reg.V[ (opcode & 0x00F0) >> 4];
	reg.PC += 2;
}

auto Chip8::AND_VX_VY(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) >> 8] &= reg.V[ (opcode & 0x00F0) >> 4];
	reg.PC += 2;
}

auto Chip8::XOR_VX_VY(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) >> 8] ^= reg.V[ (opcode & 0x00F0) >> 4];
	reg.PC += 2;
}

// Since we are dealing with 8-bit registers, we must first calculate the carry.
// We can't check if VX and VY is greater than 255 by adding because we are
// dealing with two 8-bit values using 8-bit ints.
auto Chip8::ADD_VX_VY(uint16_t opcode) -> void {
	if (reg.V[ (opcode & 0x0F00) >> 8 ] < reg.V[ (opcode & 0x00F0) >> 4 ])
		reg.V[0xF] = 1;
	else
		reg.V[0xF] = 0;

	reg.V[ (opcode & 0x0F00) >> 8] += reg.V[ (opcode & 0x00F0) >> 4];
	reg.PC += 2;
}

auto Chip8::SUB_VX_VY(uint16_t opcode) -> void {
	if (reg.V[ (opcode & 0x0F00) >> 8 ] > reg.V[ (opcode & 0x00F0) >> 4 ])
		reg.V[0xF] = 1;
	else
		reg.V[0xF] = 0;

	reg.V[ (opcode & 0x0F00) >> 8] -= reg.V[ (opcode & 0x00F0) >> 4];
	reg.PC += 2;
}

auto Chip8::SHR_VX(uint16_t opcode) -> void {
	reg.V[0xF] = reg.V[ (opcode & 0x0F00) >> 8 ] & 1;

	reg.V[ (opcode & 0x0F00) >> 8] >>= 1;
	reg.PC += 2;
}

auto Chip8::SUBN_VY_VX(uint16_t opcode) -> void {
	if (reg.V[ (opcode & 0x00F0) >> 4 ] > reg.V[ (opcode & 0x0F00) >> 8 ])
		reg.V[0xF] = 1;
	else
		reg.V[0xF] = 0;

	reg.V[ (opcode & 0x0F00) >> 8] = reg.V[ (opcode & 0x00F0) >> 4] - reg.V[ (opcode & 0x0F00) >> 8];
	reg.PC += 2;
}

auto Chip8::SHL_VX(uint16_t opcode) -> void {
	reg.V[0xF] = reg.V[ (opcode & 0x0F00) >> 8 ] >> 7;
	reg.V[ (opcode & 0x0F00) >> 8] <<= 1;
	reg.PC += 2;
}

auto Chip8::SNE_VX_VY(uint16_t opcode) -> void {
	if (reg.V[ (opcode & 0x0F00) ] != reg.V[ (opcode & 0x00F0) ])
		reg.PC += 4;
	else
		reg.PC += 2;
}

auto Chip8::LD_I_ADDR(uint16_t opcode) -> void {
	reg.I = 0x0FFF & opcode;
	reg.PC += 2;
}

auto Chip8::JP_VO_ADDR(uint16_t opcode) -> void {
	reg.PC = reg.V[0] + (opcode & 0x0FFF);
}

auto Chip8::RND_VS_BYTE(uint16_t opcode) -> void {
	reg.V[ (opcode & 0x0F00) ] = (rand() & 0xFF) & 0x00FF;
	reg.PC += 2;
}

// Finish This
auto Chip8::DRW_VX_VY_NIB(uint16_t opcode) -> void {

}
// Not really needed for now
//uint8_t Chip8::read(uint16_t addr) {
//	return c_memory[addr];
//}
//
//void Chip8::write(uint16_t addr, uint8_t data) {
//	c_memory[addr] = data;
//}


