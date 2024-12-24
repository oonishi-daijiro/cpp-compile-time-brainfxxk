#include <iostream>

#include "brainfxxks.hpp" // brainfxxk programs

// need to call this macro before include brainfxxk_runtime.hpp
run_this_program(hello_world);

#include "brainfxxk_runtime.hpp"

int main() { std::cout << unwrap<brainfxxk<>::out>::value; }
