#include "memory.h"

auto Memory::Load(std::vector<uint8_t> const& prog, Word addr) -> void
{
	for (size_t i = 0; i < prog.size(); ++i)
	{
		m_data[addr + i] = prog[i];
	}
}

auto Memory::ReadByte(Word address) -> Byte&
{
    return m_data[address];
}

auto Memory::ReadWord(Word address) -> Word&
{
    if ((size_t)address + sizeof(Word) >= k_mem_limit)
    {
        throw std::runtime_error(std::format("out-of-bounds read of {} byte(s) in range [0x{:08X}, 0x{:08X}], the valid range is [0x0000, 0xFFFF]", sizeof(Word), address, (size_t)address + sizeof(Word)));
    }
    return *reinterpret_cast<Word*>(&m_data[address]);
}

auto Memory::WriteByte(Word address, Byte value) -> void
{
    std::memcpy(&m_data[address], &value, sizeof(Byte));
}

auto Memory::WriteWord(Word address, Word value) -> void
{
    if ((size_t)address + sizeof(Word) >= k_mem_limit)
    {
        throw std::runtime_error(std::format("out-of-bounds write of {} byte(s) in range [0x{:08X}, 0x{:08X}], the valid range is [0x0000, 0xFFFF]", sizeof(Word), address, (size_t)address + sizeof(Word)));
    }
    std::memcpy(&m_data[address], &value, sizeof(Word));
}
