#include "processor.h"

#include <fstream>
#include <vector>

auto main() -> int
{
	auto test_file = "../6502_65C02_functional_tests/bin_files/6502_functional_test.bin";

	auto infile = std::ifstream(test_file, std::ios::binary);
    auto prog = std::vector<uint8_t>(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>());

    auto proc = Processor();

    proc.Load(prog, 0x0000);
	proc.Run();

	return 0;
}
