#pragma once

#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>
#include <vector>

using Byte = uint8_t;
using SByte = int8_t;
using Word = uint16_t;

class Memory
{
private:

	static const size_t k_mem_limit = 0xFFFF;
	Byte m_data[k_mem_limit];

public:

	/* Load a binary into memory at the given adderss. */
	auto Load(std::vector<uint8_t> const& prog, Word addr) -> void;

	/* Read one byte from memory at the given address. */
	auto ReadByte(Word address) -> Byte&;

	/* Read two bytes from memory at the given address. */
	auto ReadWord(Word address) -> Word&;

	/* Write one byte to memory at the given address. */
	auto WriteByte(Word address, Byte value) -> void;

	/* Write two bytes of memory at the given address. */
	auto WriteWord(Word address, Word value) -> void;

};
