#pragma once

#include "memory.h"

#include <stdexcept>

class Processor
{
private:

	static const Word PC_START = 0x400;  // the initial value of the program counter
	static const Byte SP_START = 0xFF;   // the top of the stack which grows downwards
	static const Word BRK_VEC = 0xFFFE;  // the location jumped to during a break

	Memory m_memory;

	/*    Register File    *
	 * ------------------- */

	Word PC = PC_START;  // program counter
	Byte SP = SP_START;  // stack pointer
	Byte A = 0;          // accumulator
	Byte X = 0;          // x index
	Byte Y = 0;          // y index

	/*    Status Flags    *
	 * ------------------ */

	bool N = false;  // negative
	bool V = false;  // overflow
	bool B = false;  // break
	bool D = false;  // decimal
	bool I = false;  // interrupt
	bool Z = false;  // zero
	bool C = false;  // carry

public:

	/* Load a binary into memory at the given adderss. */
	auto Load(std::vector<uint8_t> const& prog, Word addr) -> void;

	/* Begin executing a loaded binary with the program counter starting at 0x0400. */
	auto Run() -> void;

private:

	/* Run a single instruction (fetch an opcode and its operands and execute it). */
	auto Cycle() -> bool;

	/* Execute a specific opcode, decoding the addressing mode from the opcode. */
	auto Execute(Byte opcode) -> void;

	/*    Addressing Modes    *
	 * ---------------------- */

	/* Immediate addressing mode, fetch and return a single byte. */
	auto GetImm() -> Byte;

	/* Zero-page addressing mode, fetch a zero-page address and return the value it points to. */
	auto GetZpg() -> Byte&;

	/* Zero-page addressing mode, fetch a zero-page address (incremented by X) and return the value it points to. */
	auto GetZpx() -> Byte&;

	/* Zero-page addressing mode, fetch a zero-page address (incremented by Y) and return the value it points to. */
	auto GetZpy() -> Byte&;

	/* Absolute addressing mode, fetch a full address and return the value it points to. */
	auto GetAbs() -> Byte&;

	/* Absolute addressing mode, fetch a full address (incremented by X) and return the value it points to. */
	auto GetAbx() -> Byte&;

	/* Absolute addressing mode, fetch a full address (incremented by Y) and return the value it points to. */
	auto GetAby() -> Byte&;

	/* Indirect addressing mode, fetch an address (incremented by X), this points to another address, return the value it points to. */
	auto GetInx() -> Byte&;
	
	/* Indirect addressing mode, fetch an address, this points to another address which is incremented by Y, return the value it points to. */
	auto GetIny() -> Byte&;

	/* Absolute addressing mode for JMP/JSR, return a 16-bit address rather than the value it points to. */
	auto GetAbsAddr() -> Word;

	/* Indirect addressing mode for JMP, fetch a 16-bit pointer and return the 16-bit address stored there. */
	auto GetIndAddr() -> Word;

	/*    Instructions    *
	 * ------------------ */

	/* Add memory to accumulator with carry. */
	auto ADC(Byte operand) -> void;

	/* And memory with accumulator. */
	auto AND(Byte operand) -> void;

	/* Shift left one bit. */
	auto ASL(Byte& operand) -> void;

	/* Branch on carry clear. */
	auto BCC(Byte operand) -> void;

	/* Branch on carry set. */
	auto BCS(Byte operand) -> void;

	/* Branch on result zero. */
	auto BEQ(Byte operand) -> void;

	/* Test bits in memory with accumulator. */
	auto BIT(Byte operand) -> void;

	/* Branch on result minux. */
	auto BMI(Byte operand) -> void;

	/* Branch on result not zero. */
	auto BNE(Byte operand) -> void;

	/* Branch on result plus. */
	auto BPL(Byte operand) -> void;

	/* Force break. */
	auto BRK() -> void;

	/* Branch on overflow clear. */
	auto BVC(Byte operand) -> void;

	/* Branch on overflow set. */
	auto BVS(Byte operand) -> void;

	/* Clear carry flag. */
	auto CLC() -> void;

	/* Clear decimal mode. */
	auto CLD() -> void;

	/* Clear interrupt disable bit. */
	auto CLI() -> void;

	/* Clear overflow flag. */
	auto CLV() -> void;

	/* Compare memory with accumulator. */
	auto CMP(Byte operand) -> void;

	/* Compare memory and index x. */
	auto CPX(Byte operand) -> void;

	/* Compare memory and index y. */
	auto CPY(Byte operand) -> void;

	/* Decrement memory by one. */
	auto DEC(Byte& operand) -> void;

	/* Decrement index x by one. */
	auto DEX() -> void;

	/* Decrement index y by one. */
	auto DEY() -> void;

	/* Exclusive or memory with accumulator. */
	auto EOR(Byte operand) -> void;

	/* Increment memory by one. */
	auto INC(Byte& operand) -> void;

	/* Increment index x by one. */
	auto INX() -> void;

	/* Increment index y by one. */
	auto INY() -> void;

	/* Jump to new location. */
	auto JMP(Word operand) -> void;

	/* Jump to new location saving return address. */
	auto JSR(Word operand) -> void;

	/* Load accumulator with memory. */
	auto LDA(Byte operand) -> void;

	/* Load index x with memory. */
	auto LDX(Byte operand) -> void;

	/* Load index y with memory. */
	auto LDY(Byte operand) -> void;

	/* Shift one bit right. */
	auto LSR(Byte& operand) -> void;

	/* No operation. */
	auto NOP() -> void;

	/* Or memory with accumulator. */
	auto ORA(Byte operand) -> void;

	/* Push accumulator on stack. */
	auto PHA() -> void;

	/* Push processor status on stack. */
	auto PHP() -> void;

	/* Pull accumulator from stack. */
	auto PLA() -> void;

	/* Pull processor status from stack. */
	auto PLP() -> void;

	/* Rotate one bit left. */
	auto ROL(Byte& operand) -> void;

	/* Rotate one bit right. */
	auto ROR(Byte& operand) -> void;

	/* Return from interrupt. */
	auto RTI() -> void;

	/* Return from subroutine. */
	auto RTS() -> void;

	/* Subtract memory from accumulator with borrow. */
	auto SBC(Byte operand) -> void;

	/* Set carry flag. */
	auto SEC() -> void;

	/* Set decimal flag. */
	auto SED() -> void;

	/* Set interrupt disable status. */
	auto SEI() -> void;

	/* Store accumulator in memory. */
	auto STA(Byte& operand) -> void;

	/* Store index x in memory. */
	auto STX(Byte& operand) -> void;

	/* Store index y in memory. */
	auto STY(Byte& operand) -> void;

	/* Transfer accumulator to index x. */
	auto TAX() -> void;

	/* Transfer accumulator to index y. */
	auto TAY() -> void;

	/* Transfer stack pointer to index x. */
	auto TSX() -> void;

	/* Transfer index x to accumulator. */
	auto TXA() -> void;

	/* Transfer index x to stack register. */
	auto TXS() -> void;

	/* Transfer index y to accumulator. */
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
	auto FetchWord() -> Word;

	/* Fetch one byte of memory from the specified address, do not increment the program counter. */
	auto ReadByte(Word address) -> Byte&;

	/* Fetch two bytes of memory from the specified address, do not increment the program counter. */
	auto ReadWord(Word address) -> Word;

	/*    Other    * 
	 * ----------- */

	/* If the predicate matches, add the offset to the program counter. Otherwise, do nothing. */
	auto BranchRelative(bool predicate, Byte offset) -> void;

	/* Push the given value onto the stack, decrement the stack pointer. */
	auto PushStack(Byte value) -> void;

	/* Pop a value from the stack, increment the stack pointer. */
	auto PopStack() -> Byte;
	
	/* Get a single-byte representation of the status flags. */
	auto GetStatusRegister() -> Byte;

	/* Create a single-byte representation of the status flags. */
	auto SetStatusRegister(Byte flags) -> void;

	/* Jump to the given interrupt vector, specify wether this is a software or hardware interrupt. */
	auto Interrupt(Word vector, bool software) -> void;

	/* Sum accumulator with operand in binary mode. */
	auto AddBinary(Byte operand) -> void;

	/* Sum accumulator with operand in decimal mode. */
	auto AddDecimal(Byte operand) -> void;

};
