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

	static const size_t k_limit_limit = 0xFFFF;

	Byte m_data[k_limit_limit];

public:

	auto Load(std::vector<uint8_t> const& prog, Word addr) -> void;

	auto ReadByte(Word address) -> Byte&;
	auto ReadWord(Word address) -> Word&;

	auto WriteByte(Word address, Byte value) -> void;
	auto WriteWord(Word address, Word value) -> void;

};
