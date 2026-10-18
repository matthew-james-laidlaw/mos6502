# MOS 6502 Emulator

This is a hobby project that seeks to emulate the MOS 6502. The goal of this project is not necessarily to run 6502 programs but rather to better understand processor internals and assembly language.

## Building & Running

```bash
# build the core emulator library and tests
cmake -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# on multi-config generators (e.g., Visual Studio)
.\build\bin\Release\functional_test.exe
.\build\bin\Release\single_step_tests.exe

# on single-config generators (e.g., Unix Makefiles)
./build/bin/functional_test
./build/bin/single_step_tests
```

## Testing Methodology

There are two test suites used for testing the emulator, chosen for their comprehensive coverage of the 6502 ISA.

The [functional test](https://github.com/klaus2m5/6502_65c02_functional_tests) from github user Klaus Dormann [(Klaus2m5)](https://github.com/klaus2m5) is loaded into memory and executed. The test succeeds if address `0x3469` is reached, printing "Test Passed!". Otherwise the test will fail with message "Test Failed".

The [single step tests](https://github.com/SingleStepTests/65x02) provide an exhaustive list of instructions with expected pre and post-conditions to assert against.
