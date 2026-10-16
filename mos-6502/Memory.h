#pragma once

#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>

using Byte = uint8_t;
using SByte = int8_t;

using Word = uint16_t;

class Memory
{
private:

	static const size_t kMemoryLimit = 0xFFFF;

	Byte mData[kMemoryLimit];

public:

	auto readByte(Word address) -> Byte&
	{
		return mData[address];
	}

	auto readWord(Word address) -> Word&
	{
		if ((size_t)address + sizeof(Word) > kMemoryLimit)
		{
			throw std::runtime_error(std::format("out-of-bounds read of {} byte(s) in range [0x{:08X}, 0x{:08X}], the valid range is [0x0000, 0xFFFF]", sizeof(Word), address, (size_t)address + sizeof(Word)));
		}
		return *reinterpret_cast<Word*>(&mData[address]);
	}

	auto writeByte(Word address, Byte value) -> void
	{
		std::memcpy(&mData[address], &value, sizeof(Byte));
	}

	auto writeWord(Word address, Word value) -> void
	{
		if ((size_t)address + sizeof(Word) > kMemoryLimit)
		{
			throw std::runtime_error(std::format("out-of-bounds write of {} byte(s) in range [0x{:08X}, 0x{:08X}], the valid range is [0x0000, 0xFFFF]", sizeof(Word), address, (size_t)address + sizeof(Word)));
		}
		std::memcpy(&mData[address], &value, sizeof(Word));
	}

};
