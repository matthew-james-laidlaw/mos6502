#include "Processor.h"

auto Processor::Cycle() -> void
{
	auto opcode = FetchByte();

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
		default: throw std::runtime_error(std::format("invalid opcode {}", opcode));
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
	return ReadByte(FetchByte() + X);
}

auto Processor::GetZpy() -> Byte&
{
	return ReadByte(FetchByte() + Y);
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
	return ReadByte(ReadWord(FetchByte() + X));
}

auto Processor::GetIny() -> Byte&
{
	return ReadByte(ReadWord(FetchByte()) + Y);
}

auto Processor::GetAbsAddr() -> Word
{
	return FetchWord();
}

auto Processor::GetIndAddr() -> Word
{
	return ReadWord(FetchByte());
}

/*    Instructions    *
 * ------------------ */

auto Processor::ADC(Byte operand) -> void
{
	const auto original = A;
	const auto sum = static_cast<Word>(original) + operand + C;
	A = static_cast<Byte>(sum);

	C = sum > 0xFF;
	V = (~(original ^ operand) & (original ^ A) & 0x80) != 0;

	SetN(A);
	SetZ(A);
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

	SetN(A);
	SetZ(A);
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
	throw std::runtime_error("not implemented");
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
	throw std::runtime_error("not implemented");
}

auto Processor::CPX(Byte operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::CPY(Byte operand) -> void
{
	throw std::runtime_error("not implemented");
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
	SetN(X);
	SetZ(X);
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
	throw std::runtime_error("not implemented");
}

auto Processor::JSR(Word operand) -> void
{
	throw std::runtime_error("not implemented");
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
	X = operand;
	SetN(X);
	SetZ(X);
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
	throw std::runtime_error("not implemented");
}

auto Processor::PHP() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::PLA() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::PLP() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::ROL(Byte& operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::ROR(Byte& operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::RTI() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::RTS() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::SBC(Byte operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::SEC() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::SED() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::SEI() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::STA(Byte& operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::STX(Byte& operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::STY(Byte& operand) -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::TAX() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::TAY() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::TSX() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::TXA() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::TXS() -> void
{
	throw std::runtime_error("not implemented");
}

auto Processor::TYA() -> void
{
	throw std::runtime_error("not implemented");
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
	return mMemory.readByte(PC++);
}

auto Processor::FetchWord() -> Word&
{
	return mMemory.readWord(PC++);
}

auto Processor::ReadByte(Word address) -> Byte&
{
	return mMemory.readByte(address);
}

auto Processor::ReadWord(Word address) -> Word&
{
	return mMemory.readWord(address);
}

/*    Other    *
 * ----------- */

auto Processor::BranchRelative(bool predicate, Byte offset) -> void
{
	if (predicate)
	{
		PC += static_cast<SByte>(offset);
	}
}
