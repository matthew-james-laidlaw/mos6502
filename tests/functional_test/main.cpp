#include "processor.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <vector>

#ifndef KLAUS2M5_ROM_PATH
	#error "Requires KLAUS2M5_ROM_PATH to be defined as a path to the test ROM"
#endif

namespace fs = std::filesystem;

auto Main() -> void
{
	auto test_file = fs::path(KLAUS2M5_ROM_PATH);
	if (!fs::exists(test_file))
	{
		throw std::runtime_error(std::format("file does not exist: {}", test_file.string()));
	}

	auto infile = std::ifstream(test_file, std::ios::binary);
	if (!infile)
	{
		throw std::runtime_error(std::format("file failed to open: {}", test_file.string()));
	}

    auto prog = std::vector<uint8_t>(std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>());
	
    auto proc = Processor();
    proc.Load(prog, 0x0000);
	proc.Run();
}

auto main() -> int
{
	try
	{
		Main();
		return 0;
	}
	catch (std::exception const& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}
