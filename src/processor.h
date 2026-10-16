#pragma once

#include "memory.h"

#include <stdexcept>

class Processor
{
private:

	Memory m_memory;

	/*    Register File    *
	 * ------------------- */

	Word PC = 0x400;  // program counter
	
	Byte SP;  // stack pointer

	Byte A;  // accumulator
	Byte X;  // x index
	Byte Y;  // y index

	/*    Status Flags    *
	 * ------------------ */

	bool N;  // negative
	bool V;  // overflow
	bool B;  // break
	bool D;  // decimal
	bool I;  // interrupt
	bool Z;  // zero
	bool C;  // carry

public:

	auto Load(std::vector<uint8_t> const& prog, Word addr) -> void;
	auto Run() -> void;

private:

	auto Cycle() -> void;

	/*    Addressing Modes    *
	 * ---------------------- */

	auto GetImm() -> Byte;
	auto GetZpg() -> Byte&;
	auto GetZpx() -> Byte&;
	auto GetZpy() -> Byte&;
	auto GetAbs() -> Byte&;
	auto GetAbx() -> Byte&;
	auto GetAby() -> Byte&;
	auto GetInx() -> Byte&;
	auto GetIny() -> Byte&;

	auto GetAbsAddr() -> Word;
	auto GetIndAddr() -> Word;

	/*    Instructions    *
	 * ------------------ */

	auto ADC(Byte operand) -> void;
	auto AND(Byte operand) -> void;
	auto ASL(Byte& operand) -> void;
	auto BCC(Byte operand) -> void;
	auto BCS(Byte operand) -> void;
	auto BEQ(Byte operand) -> void;
	auto BIT(Byte operand) -> void;
	auto BMI(Byte operand) -> void;
	auto BNE(Byte operand) -> void;
	auto BPL(Byte operand) -> void;
	auto BRK() -> void;
	auto BVC(Byte operand) -> void;
	auto BVS(Byte operand) -> void;
	auto CLC() -> void;
	auto CLD() -> void;
	auto CLI() -> void;
	auto CLV() -> void;
	auto CMP(Byte operand) -> void;
	auto CPX(Byte operand) -> void;
	auto CPY(Byte operand) -> void;
	auto DEC(Byte& operand) -> void;
	auto DEX() -> void;
	auto DEY() -> void;
	auto EOR(Byte operand) -> void;
	auto INC(Byte& operand) -> void;
	auto INX() -> void;
	auto INY() -> void;
	auto JMP(Word operand) -> void;
	auto JSR(Word operand) -> void;
	auto LDA(Byte operand) -> void;
	auto LDX(Byte operand) -> void;
	auto LDY(Byte operand) -> void;
	auto LSR(Byte& operand) -> void;
	auto NOP() -> void;
	auto ORA(Byte operand) -> void;
	auto PHA() -> void;
	auto PHP() -> void;
	auto PLA() -> void;
	auto PLP() -> void;
	auto ROL(Byte& operand) -> void;
	auto ROR(Byte& operand) -> void;
	auto RTI() -> void;
	auto RTS() -> void;
	auto SBC(Byte operand) -> void;
	auto SEC() -> void;
	auto SED() -> void;
	auto SEI() -> void;
	auto STA(Byte& operand) -> void;
	auto STX(Byte& operand) -> void;
	auto STY(Byte& operand) -> void;
	auto TAX() -> void;
	auto TAY() -> void;
	auto TSX() -> void;
	auto TXA() -> void;
	auto TXS() -> void;
	auto TYA() -> void;

	/*    Status Flags    *
	 * ------------------ */

	/* Set the negative flag. */
	auto SetN(Byte value) -> void;

	/* Set the zero flag. */
	auto SetZ(Byte value) -> void;

	/*    Memory Access    *
     * ------------------- */

	/* Fetch one byte of memory at the program counter, increment the program counter by one. */
	auto FetchByte() -> Byte&;

	/* Fetch two bytes of memory at the program counter, increment the program counter by two. */
	auto FetchWord() -> Word&;

	/* Fetch one byte of memory from the specified address, do not increment the program counter. */
	auto ReadByte(Word address) -> Byte&;

	/* Fetch two bytes of memory from the specified address, do not increment the program counter. */
	auto ReadWord(Word address) -> Word&;

	/*    Other    * 
	 * ----------- */

	/* If the predicate matches, add the offset to the program counter. Otherwise, do nothing. */
	auto BranchRelative(bool predicate, Byte offset) -> void;

};
