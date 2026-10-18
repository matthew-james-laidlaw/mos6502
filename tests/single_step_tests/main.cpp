#include <nlohmann/json.hpp>

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef SINGLE_STEP_TESTS_DIR
	#error "Requires SINGLE_STEP_TESTS_DIR to be defined as the test data directory"
#endif

namespace
{
	using Json = nlohmann::json;
	namespace fs = std::filesystem;

	struct MemoryByte
	{
		std::uint16_t address = 0;
		std::uint8_t value = 0;
	};

	struct CpuState
	{
		std::uint16_t pc = 0;
		std::uint8_t s = 0;
		std::uint8_t a = 0;
		std::uint8_t x = 0;
		std::uint8_t y = 0;
		std::uint8_t p = 0;
		std::vector<MemoryByte> ram;
	};

	enum class Access
	{
		Read,
		Write
	};

	struct BusCycle
	{
		std::uint16_t address = 0;
		std::uint8_t value = 0;
		Access access = Access::Read;
	};

	struct TestCase
	{
		std::string name;
		CpuState initial;
		CpuState final;
		std::vector<BusCycle> cycles;
	};

	auto ReadAccess(Json const& value) -> Access
	{
		auto const access = value.get<std::string>();
		if (access == "read")
		{
			return Access::Read;
		}
		if (access == "write")
		{
			return Access::Write;
		}
		throw std::runtime_error("cycle access must be 'read' or 'write'");
	}

	auto from_json(Json const& json, MemoryByte& value) -> void
	{
		if (!json.is_array() || json.size() != 2)
		{
			throw std::runtime_error("RAM entries must be [address, value] pairs");
		}
		value.address = json.at(0).get<std::uint16_t>();
		value.value = json.at(1).get<std::uint8_t>();
	}

	auto from_json(Json const& json, CpuState& state) -> void
	{
		json.at("pc").get_to(state.pc);
		json.at("s").get_to(state.s);
		json.at("a").get_to(state.a);
		json.at("x").get_to(state.x);
		json.at("y").get_to(state.y);
		json.at("p").get_to(state.p);
		json.at("ram").get_to(state.ram);
	}

	auto from_json(Json const& json, BusCycle& cycle) -> void
	{
		if (!json.is_array() || json.size() != 3)
		{
			throw std::runtime_error("cycles must be [address, value, access] triples");
		}
		cycle.address = json.at(0).get<std::uint16_t>();
		cycle.value = json.at(1).get<std::uint8_t>();
		cycle.access = ReadAccess(json.at(2));
	}

	auto from_json(Json const& json, TestCase& test) -> void
	{
		json.at("name").get_to(test.name);
		json.at("initial").get_to(test.initial);
		json.at("final").get_to(test.final);
		json.at("cycles").get_to(test.cycles);
	}
}

auto main() -> int
{
	try
	{
		auto const test_directory = fs::path(SINGLE_STEP_TESTS_DIR);
		auto files = std::vector<fs::path>();
		for (auto const& entry : fs::directory_iterator(test_directory))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".json")
			{
				files.push_back(entry.path());
			}
		}
		std::sort(files.begin(), files.end());
		if (files.empty())
		{
			throw std::runtime_error("no JSON test files found in " + test_directory.string());
		}

		auto total_tests = std::size_t{ 0 };
		for (auto const& path : files)
		{
			auto input = std::ifstream(path);
			if (!input)
			{
				throw std::runtime_error("failed to open JSON file: " + path.string());
			}

			auto json = Json::parse(input);
			auto const tests = json.get<std::vector<TestCase>>();
			total_tests += tests.size();
			std::cout << "Decoded " << tests.size() << " test cases from " << path.filename().string() << '\n';
		}

		std::cout << "Decoded " << total_tests << " test cases across " << files.size() << " files\n";
	}
	catch (std::exception const& error)
	{
		std::cerr << "failed to decode SingleStepTests: " << error.what() << '\n';
		return 1;
	}

	return 0;
}
