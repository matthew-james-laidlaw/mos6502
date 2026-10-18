#include "processor.h"

#include <iostream>

auto Processor::Load(std::vector<uint8_t> const& prog, Word addr) -> void
{
	m_memory.Load(prog, addr);
}

auto Processor::Run() -> void
{
	while (Cycle()) {}
}

auto Processor::Cycle() -> bool
{
	auto orig_pc = PC;
	auto opcode = FetchByte();

	try
	{
		Execute(opcode);
		if (PC == 0x3469)
		{
			std::cout << "Test Passed!" << std::endl;
			return false;
		}
	}
	catch (std::exception const& e)
	{
		throw std::runtime_error(std::format("{} (opcode '0x{:02X}' at PC '0x{:04X}')", e.what(), opcode, PC - 1));
	}

	if (PC == orig_pc)
	{
		throw std::runtime_error("Test Failed.");
	}

	return true;
}

auto Processor::Execute(Byte opcode) -> void
{
	switch (opcode)
	{
		// ADC
		case 0x69: { ADC(GetImm()); return; }
		case 0x65: { ADC(GetZpg()); return; }
		case 0x75: { ADC(GetZpx()); return; }
		case 0x6D: { ADC(GetAbs()); return; }
		case 0x7D: { ADC(GetAbx()); return; }
		case 0x79: { ADC(GetAby()); return; }
		case 0x61: { ADC(GetInx()); return; }
		case 0x71: { ADC(GetIny()); return; }

		// AND
		case 0x29: { AND(GetImm()); return; }
		case 0x25: { AND(GetZpg()); return; }
		case 0x35: { AND(GetZpx()); return; }
		case 0x2D: { AND(GetAbs()); return; }
		case 0x3D: { AND(GetAbx()); return; }
		case 0x39: { AND(GetAby()); return; }
		case 0x21: { AND(GetInx()); return; }
		case 0x31: { AND(GetIny()); return; }

		// ASL
		case 0x0A: { ASL(A);        return; }
		case 0x06: { ASL(GetZpg()); return; }
		case 0x16: { ASL(GetZpx()); return; }
		case 0x0E: { ASL(GetAbs()); return; }
		case 0x1E: { ASL(GetAbx()); return; }

		// BCC
		case 0x90: { BCC(GetImm()); return; }

		// BCS
		case 0xB0: { BCS(GetImm()); return; }

		// BEQ
		case 0xF0: { BEQ(GetImm()); return; }

		// BIT
		case 0x24: { BIT(GetZpg()); return; }
		case 0x2C: { BIT(GetAbs()); return; }

		// BMI
		case 0x30: { BMI(GetImm()); return; }

		// BNE
		case 0xD0: { BNE(GetImm()); return; }

		// BPL
		case 0x10: { BPL(GetImm()); return; }

		// BRK
		case 0x00: { BRK(); return; }

		// BVC
		case 0x50: { BVC(GetImm()); return; }

		// BVS
		case 0x70: { BVS(GetImm()); return; }

		// CLC
		case 0x18: { CLC(); return; }

		// CLD
		case 0xD8: { CLD(); return; }

		// CLI
		case 0x58: { CLI(); return; }

		// CLV
		case 0xB8: { CLV(); return; }

		// CMP
		case 0xC9: { CMP(GetImm()); return; }
		case 0xC5: { CMP(GetZpg()); return; }
		case 0xD5: { CMP(GetZpx()); return; }
		case 0xCD: { CMP(GetAbs()); return; }
		case 0xDD: { CMP(GetAbx()); return; }
		case 0xD9: { CMP(GetAby()); return; }
		case 0xC1: { CMP(GetInx()); return; }
		case 0xD1: { CMP(GetIny()); return; }

		// CPX
		case 0xE0: { CPX(GetImm()); return; }
		case 0xE4: { CPX(GetZpg()); return; }
		case 0xEC: { CPX(GetAbs()); return; }

		// CPY
		case 0xC0: { CPY(GetImm()); return; }
		case 0xC4: { CPY(GetZpg()); return; }
		case 0xCC: { CPY(GetAbs()); return; }

		// DEC
		case 0xC6: { DEC(GetZpg()); return; }
		case 0xD6: { DEC(GetZpx()); return; }
		case 0xCE: { DEC(GetAbs()); return; }
		case 0xDE: { DEC(GetAbx()); return; }

		// DEX
		case 0xCA: { DEX(); return; }

		// DEY
		case 0x88: { DEY(); return; }

		// EOR
		case 0x49: { EOR(GetImm()); return; }
		case 0x45: { EOR(GetZpg()); return; }
		case 0x55: { EOR(GetZpx()); return; }
		case 0x4D: { EOR(GetAbs()); return; }
		case 0x5D: { EOR(GetAbx()); return; }
		case 0x59: { EOR(GetAby()); return; }
		case 0x41: { EOR(GetInx()); return; }
		case 0x51: { EOR(GetIny()); return; }

		// INC
		case 0xE6: { INC(GetZpg()); return; }
		case 0xF6: { INC(GetZpx()); return; }
		case 0xEE: { INC(GetAbs()); return; }
		case 0xFE: { INC(GetAbx()); return; }

		// INX
		case 0xE8: { INX(); return; }

		// INY
		case 0xC8: { INY(); return; }

		// JMP
		case 0x4C: { JMP(GetAbsAddr()); return; }
		case 0x6C: { JMP(GetIndAddr()); return; }

		// JSR
		case 0x20: { JSR(GetAbsAddr()); return; }

		// LDA
		case 0xA9: { LDA(GetImm()); return; }
		case 0xA5: { LDA(GetZpg()); return; }
		case 0xB5: { LDA(GetZpx()); return; }
		case 0xAD: { LDA(GetAbs()); return; }
		case 0xBD: { LDA(GetAbx()); return; }
		case 0xB9: { LDA(GetAby()); return; }
		case 0xA1: { LDA(GetInx()); return; }
		case 0xB1: { LDA(GetIny()); return; }

		// LDX
		case 0xA2: { LDX(GetImm()); return; }
		case 0xA6: { LDX(GetZpg()); return; }
		case 0xB6: { LDX(GetZpy()); return; }
		case 0xAE: { LDX(GetAbs()); return; }
		case 0xBE: { LDX(GetAby()); return; }

		// LDY
		case 0xA0: { LDY(GetImm()); return; }
		case 0xA4: { LDY(GetZpg()); return; }
		case 0xB4: { LDY(GetZpx()); return; }
		case 0xAC: { LDY(GetAbs()); return; }
		case 0xBC: { LDY(GetAbx()); return; }

		// LSR
		case 0x4A: { LSR(A);        return; }
		case 0x46: { LSR(GetZpg()); return; }
		case 0x56: { LSR(GetZpx()); return; }
		case 0x4E: { LSR(GetAbs()); return; }
		case 0x5E: { LSR(GetAbx()); return; }

		// NOP
		case 0xEA: { NOP(); return; }

		// ORA
		case 0x09: { ORA(GetImm()); return; }
		case 0x05: { ORA(GetZpg()); return; }
		case 0x15: { ORA(GetZpx()); return; }
		case 0x0D: { ORA(GetAbs()); return; }
		case 0x1D: { ORA(GetAbx()); return; }
		case 0x19: { ORA(GetAby()); return; }
		case 0x01: { ORA(GetInx()); return; }
		case 0x11: { ORA(GetIny()); return; }

		// PHA
		case 0x48: { PHA(); return; }

		// PHP
		case 0x08: { PHP(); return; }

		// PLA
		case 0x68: { PLA(); return; }

		// PLP
		case 0x28: { PLP(); return; }

		// ROL
		case 0x2A: { ROL(A);        return; }
		case 0x26: { ROL(GetZpg()); return; }
		case 0x36: { ROL(GetZpx()); return; }
		case 0x2E: { ROL(GetAbs()); return; }
		case 0x3E: { ROL(GetAbx()); return; }

		// ROR
		case 0x6A: { ROR(A);        return; }
		case 0x66: { ROR(GetZpg()); return; }
		case 0x76: { ROR(GetZpx()); return; }
		case 0x6E: { ROR(GetAbs()); return; }
		case 0x7E: { ROR(GetAbx()); return; }

		// RTI
		case 0x40: { RTI(); return; }

		// RTS
		case 0x60: { RTS(); return; }

		// SBC
		case 0xE9: { SBC(GetImm()); return; }
		case 0xE5: { SBC(GetZpg()); return; }
		case 0xF5: { SBC(GetZpx()); return; }
		case 0xED: { SBC(GetAbs()); return; }
		case 0xFD: { SBC(GetAbx()); return; }
		case 0xF9: { SBC(GetAby()); return; }
		case 0xE1: { SBC(GetInx()); return; }
		case 0xF1: { SBC(GetIny()); return; }

		// SEC
		case 0x38: { SEC(); return; }

		// SED
		case 0xF8: { SED(); return; }

		// SEI
		case 0x78: { SEI(); return; }

		// STA
		case 0x85: { STA(GetZpg()); return; }
		case 0x95: { STA(GetZpx()); return; }
		case 0x8D: { STA(GetAbs()); return; }
		case 0x9D: { STA(GetAbx()); return; }
		case 0x99: { STA(GetAby()); return; }
		case 0x81: { STA(GetInx()); return; }
		case 0x91: { STA(GetIny()); return; }

		// STX
		case 0x86: { STX(GetZpg()); return; }
		case 0x96: { STX(GetZpy()); return; }
		case 0x8E: { STX(GetAbs()); return; }

		// STY
		case 0x84: { STY(GetZpg()); return; }
		case 0x94: { STY(GetZpx()); return; }
		case 0x8C: { STY(GetAbs()); return; }

		// TAX
		case 0xAA: { TAX(); return; }

		// TAY
		case 0xA8: { TAY(); return; }

		// TSX
		case 0xBA: { TSX(); return; }

		// TXA
		case 0x8A: { TXA(); return; }

		// TXS
		case 0x9A: { TXS(); return; }

		// TYA
		case 0x98: { TYA(); return; }

		// Unknown
		default: throw std::runtime_error(std::format("invalid opcode", opcode));
	}
}

/*    Addressing Modes    *
 * ---------------------- */

auto Processor::GetImm() -> Byte
{
	return FetchByte();
}

auto Processor::GetZpg() -> Byte&
{
	return ReadByte(FetchByte());
}

auto Processor::GetZpx() -> Byte&
{
	return ReadByte(static_cast<Byte>(FetchByte() + X));
}

auto Processor::GetZpy() -> Byte&
{
	return ReadByte(static_cast<Byte>(FetchByte() + Y));
}

auto Processor::GetAbs() -> Byte&
{
	return ReadByte(FetchWord());
}

auto Processor::GetAbx() -> Byte&
{
	return ReadByte(FetchWord() + X);
}

auto Processor::GetAby() -> Byte&
{
	return ReadByte(FetchWord() + Y);
}

auto Processor::GetInx() -> Byte&
{
	return ReadByte(ReadWord(static_cast<Byte>(FetchByte() + X)));
}

auto Processor::GetIny() -> Byte&
{
	return ReadByte(static_cast<Word>(ReadWord(FetchByte()) + Y));
}

auto Processor::GetAbsAddr() -> Word
{
	return FetchWord();
}

auto Processor::GetIndAddr() -> Word
{
	// NMOS bug: JMP at a page boundary e.g., 0x__FF takes its high byte from 0x__00
	const Word ptr = FetchWord();
	const Word hi_addr = static_cast<Word>((ptr & 0xFF00) | ((ptr + 1) & 0x00FF));
	return static_cast<Word>((ReadByte(hi_addr) << 8) | ReadByte(ptr));
}

/*    Instructions    *
 * ------------------ */

auto Processor::ADC(Byte operand) -> void
{
	if (D)
	{
		AddDecimal(operand);
	}
	else
	{
		AddBinary(operand);
	}
}

auto Processor::AND(Byte operand) -> void
{
	A &= operand;
	SetN(A);
	SetZ(A);
}

auto Processor::ASL(Byte& operand) -> void
{
	const auto original = operand;
	const auto shifted = static_cast<Word>(original) << 1;
	operand = static_cast<Byte>(shifted);

	C = shifted > 0xFF;

	SetN(operand);
	SetZ(operand);
}

auto Processor::BCC(Byte operand) -> void
{
	BranchRelative(!C, operand);
}

auto Processor::BCS(Byte operand) -> void
{
	BranchRelative(C, operand);
}

auto Processor::BEQ(Byte operand) -> void
{
	BranchRelative(Z, operand);
}

auto Processor::BIT(Byte operand) -> void
{
	N = (operand & 0b10000000) != 0;
	V = (operand & 0b01000000) != 0;
	Z = (A & operand) == 0;
}

auto Processor::BMI(Byte operand) -> void
{
	BranchRelative(N, operand);
}

auto Processor::BNE(Byte operand) -> void
{
	BranchRelative(!Z, operand);
}

auto Processor::BPL(Byte operand) -> void
{
	BranchRelative(!N, operand);
}

auto Processor::BRK() -> void
{
	++PC;
	Interrupt(BRK_VEC, true);
}

auto Processor::BVC(Byte operand) -> void
{
	BranchRelative(!V, operand);
}

auto Processor::BVS(Byte operand) -> void
{
	BranchRelative(V, operand);
}

auto Processor::CLC() -> void
{
	C = 0;
}

auto Processor::CLD() -> void
{
	D = 0;
}

auto Processor::CLI() -> void
{
	I = 0;
}

auto Processor::CLV() -> void
{
	V = 0;
}

auto Processor::CMP(Byte operand) -> void
{
	Byte result = A - operand;
	SetN(result);
	SetZ(result);
	C = A >= operand;
}

auto Processor::CPX(Byte operand) -> void
{
	Byte result = X - operand;
	SetN(result);
	SetZ(result);
	C = X >= operand;
}

auto Processor::CPY(Byte operand) -> void
{
	Byte result = Y - operand;
	SetN(result);
	SetZ(result);
	C = Y >= operand;
}

auto Processor::DEC(Byte& operand) -> void
{
	operand -= 1;
	SetN(operand);
	SetZ(operand);
}

auto Processor::DEX() -> void
{
	--X;
	SetN(X);
	SetZ(X);
}

auto Processor::DEY() -> void
{
	--Y;
	SetN(Y);
	SetZ(Y);
}

auto Processor::EOR(Byte operand) -> void
{
	A ^= operand;
	SetN(A);
	SetZ(A);
}

auto Processor::INC(Byte& operand) -> void
{
	++operand;
	SetN(operand);
	SetZ(operand);
}

auto Processor::INX() -> void
{
	++X;
	SetN(X);
	SetZ(X);
}

auto Processor::INY() -> void
{
	++Y;
	SetN(Y);
	SetZ(Y);
}

auto Processor::JMP(Word operand) -> void
{
	PC = operand;
}

auto Processor::JSR(Word operand) -> void
{
	const Word ret = PC - 1;
	PushStack(static_cast<Byte>(ret >> 8));
	PushStack(static_cast<Byte>(ret & 0xFF));
	PC = operand;
}

auto Processor::LDA(Byte operand) -> void
{
	A = operand;
	SetN(A);
	SetZ(A);
}

auto Processor::LDX(Byte operand) -> void
{
	X = operand;
	SetN(X);
	SetZ(X);
}

auto Processor::LDY(Byte operand) -> void
{
	Y = operand;
	SetN(Y);
	SetZ(Y);
}

auto Processor::LSR(Byte& operand) -> void
{
	C = (operand & 0b00000001) != 0;
	operand >>= 1;
	N = false;
	SetZ(operand);
}

auto Processor::NOP() -> void
{
	return;
}

auto Processor::ORA(Byte operand) -> void
{
	A |= operand;
	SetN(A);
	SetZ(A);
}

auto Processor::PHA() -> void
{
	PushStack(A);
}

auto Processor::PHP() -> void
{
	PushStack(GetStatusRegister());
}

auto Processor::PLA() -> void
{
	A = PopStack();
	SetN(A);
	SetZ(A);
}

auto Processor::PLP() -> void
{
	SetStatusRegister(PopStack());
}

auto Processor::ROL(Byte& operand) -> void
{
	const bool carry_out = (operand & 0x80) != 0;
	operand = static_cast<Byte>((operand << 1) | (C ? 0x01 : 0x00));
	C = carry_out;
	SetN(operand);
	SetZ(operand);
}

auto Processor::ROR(Byte& operand) -> void
{
	const bool carry_out = (operand & 0x01) != 0;
	operand = static_cast<Byte>((operand >> 1) | (C ? 0x80 : 0x00));
	C = carry_out;
	SetN(operand);
	SetZ(operand);
}

auto Processor::RTI() -> void
{
	SetStatusRegister(PopStack());
	const Byte lo = PopStack();
	const Byte hi = PopStack();
	PC = static_cast<Word>((hi << 8) | lo);
}

auto Processor::RTS() -> void
{
	const Byte lo = PopStack();
	const Byte hi = PopStack();
	PC = static_cast<Word>((hi << 8) | lo) + 1;
}

auto Processor::SBC(Byte operand) -> void
{
	if (!D)
	{
		AddBinary(static_cast<Byte>(~operand));
		return;
	}

	const Byte original = A;
	const int borrow = C ? 0 : 1;
	AddBinary(static_cast<Byte>(~operand));

	int lo = (original & 0x0F) - (operand & 0x0F) - borrow;
	int hi = (original >> 4) - (operand >> 4);
	if (lo & 0x10) { lo -= 6; --hi; }
	if (hi & 0x10) { hi -= 6; }
	A = static_cast<Byte>((hi << 4) | (lo & 0x0F));
}

auto Processor::SEC() -> void
{
	C = 1;
}

auto Processor::SED() -> void
{
	D = 1;
}

auto Processor::SEI() -> void
{
	I = 1;
}

auto Processor::STA(Byte& operand) -> void
{
	operand = A;
}

auto Processor::STX(Byte& operand) -> void
{
	operand = X;
}

auto Processor::STY(Byte& operand) -> void
{
	operand = Y;
}

auto Processor::TAX() -> void
{
	X = A;
	SetN(X);
	SetZ(X);
}

auto Processor::TAY() -> void
{
	Y = A;
	SetN(Y);
	SetZ(Y);
}

auto Processor::TSX() -> void
{
	X = SP;
	SetN(X);
	SetZ(X);
}

auto Processor::TXA() -> void
{
	A = X;
	SetN(A);
	SetZ(A);
}

auto Processor::TXS() -> void
{
	SP = X;
}

auto Processor::TYA() -> void
{
	A = Y;
	SetN(A);
	SetZ(A);
}

/*    Status Flags    *
 * ------------------ */

auto Processor::SetN(Byte value) -> void
{
	N = (value & 0b10000000) != 0;
}

auto Processor::SetZ(Byte value) -> void
{
	Z = value == 0;
}

/*    Memory Access
 * ------------------- */

auto Processor::FetchByte() -> Byte&
{
	return m_memory.ReadByte(PC++);
}

auto Processor::FetchWord() -> Word
{
	auto lo = m_memory.ReadByte(PC++);
	auto hi = m_memory.ReadByte(PC++);
	auto result = static_cast<Word>(static_cast<Word>(hi) << 8 | static_cast<Word>(lo));
	return result;
}

auto Processor::ReadByte(Word address) -> Byte&
{
	return m_memory.ReadByte(address);
}

auto Processor::ReadWord(Word address) -> Word
{
	const Byte lo = ReadByte(address);
	const Byte hi = ReadByte(static_cast<Byte>(address + 1));
	return static_cast<Word>((hi << 8) | lo);
}

/*    Other    *
 * ----------- */

auto Processor::BranchRelative(bool predicate, Byte offset) -> void
{
	if (predicate)
	{
        const auto displacement = static_cast<SByte>(offset);
        PC = static_cast<Word>(PC + displacement);
	}
}

auto Processor::PushStack(Byte value) -> void
{
	ReadByte(0x0100 + SP) = value;
	--SP;
}

auto Processor::PopStack() -> Byte
{
	++SP;
	return ReadByte(0x0100 + SP);
}

auto Processor::GetStatusRegister() -> Byte
{
	Byte flags = 0;
	flags |= static_cast<Byte>(N) << 7;
	flags |= static_cast<Byte>(V) << 6;
	flags |= 1 << 5;
	flags |= 1 << 4;
	flags |= static_cast<Byte>(D) << 3;
	flags |= static_cast<Byte>(I) << 2;
	flags |= static_cast<Byte>(Z) << 1;
	flags |= static_cast<Byte>(C);
	return flags;
}

auto Processor::SetStatusRegister(Byte flags) -> void
{
	N = ((flags >> 7) & 1) != 0;
	V = ((flags >> 6) & 1) != 0;
	D = ((flags >> 3) & 1) != 0;
	I = ((flags >> 2) & 1) != 0;
	Z = ((flags >> 1) & 1) != 0;
	C = (flags & 1) != 0;
}

auto Processor::Interrupt(Word vector, bool software) -> void
{
	PushStack(static_cast<Byte>(PC >> 8));
	PushStack(static_cast<Byte>(PC & 0xFF));

	Byte flags = GetStatusRegister();
	if (!software)
	{
		flags &= static_cast<Byte>(~0x10);
	}
	PushStack(flags);

	I = true;
	PC = static_cast<Word>(ReadByte(vector) | (ReadByte(vector + 1) << 8));
}

auto Processor::AddBinary(Byte operand) -> void
{
	const Byte original = A;
	const Word sum = static_cast<Word>(original + operand + (C ? 1 : 0));
	A = static_cast<Byte>(sum);

	C = sum > 0xFF;
	V = (~(original ^ operand) & (original ^ A) & 0x80) != 0;

	SetN(A);
	SetZ(A);
}

auto Processor::AddDecimal(Byte operand) -> void
{
	const Byte original = A;
	const int carry_in = C ? 1 : 0;

	int lo = (original & 0x0F) + (operand & 0x0F) + carry_in;
	if (lo > 0x09) { lo += 0x06; }

	int hi = (original >> 4) + (operand >> 4) + (lo > 0x0F ? 1 : 0);

	Z = static_cast<Byte>(original + operand + carry_in) == 0;
	N = (hi & 0x08) != 0;
	V = (~(original ^ operand) & (original ^ (hi << 4)) & 0x80) != 0;

	if (hi > 0x09) { hi += 0x06; }
	C = hi > 0x0F;

	A = static_cast<Byte>((hi << 4) | (lo & 0x0F));
}
