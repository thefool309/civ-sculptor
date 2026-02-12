/// @file test.cpp
/// @brief test implementations and main test harness entry point

#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include "../src/include/World.h"
#include "../src/include/Civilization.h"
#include "test.h"
#include "../src/include/Simulation.h"
#include <functional>

int main() {
	printf("Hello world I'm a test harness! :3\n\n");
	Tests tests;

	tests.RunTests();
}

void TestFramework::Summary() {
	std::cout << "\n----------------------------------------\n";
	std::cout << "                Summary";
	std::cout << "\n----------------------------------------\n";
	std::cout << "Passing tests: ";
	Utils::SetColor(92);
	std::cout << g_tests_passed << '\n';
	Utils::ResetColor();
	std::cout << "Failing tests: ";
	Utils::SetColor(31);
	std::cout << g_tests_failed << '\n';
	Utils::ResetColor();
}
template<typename Callable>
void TestFramework::InvokeTest(Callable&& fn) {
		try {
			std::invoke(std::forward<Callable>(fn));
			Utils::SetColor(92);
			std::cout << "PASS\n";
			Utils::ResetColor();
			++g_tests_passed;
		}
		catch (std::exception& e) {
			Utils::SetColor(31);
			std::cout << "FAIL: " << e.what() << "\n";
			Utils::ResetColor();
			++g_tests_failed;
		}
		catch (...) {
			Utils::SetColor(31);
			std::cout << "FAIL: Unknown Exception\n";
			Utils::ResetColor();
			++g_tests_failed;
		}
}

void Tests::TestWorldGetName() {
	ASSERT_TRUE(sim.world.getName() == "Testonia");
}

void Tests::TestWorldGetSeed() {
	ASSERT_TRUE(sim.world.getSeed() == 123456);
}

void Tests::TestCivFactoryGenCivSeed() {
	/*std::cout << "\nGenerateCivSeed Russia Hash : " << world.GenerateCivSeed("Russia").rng_seed << '\n';*/
	ASSERT_TRUE(CivFactory::GenerateCivSeed("Russia", sim.world.getSeed()).name == "Russia");
	ASSERT_TRUE(CivFactory::GenerateCivSeed("Russia", sim.world.getSeed()).rng_seed == 11649118993674644964); // expected rng_seed for russia with the default test world seed
}

void Tests::TestSimLoop() {

	ASSERT_TRUE(sim.SimLoop(10) == 10); // this returns 10, because the first tick starts 0 this could be a year, a month, a week, an hour or any other measure of time
	ASSERT_TRUE(sim.SimLoop(5) == 15);
	ASSERT_TRUE(sim.SimLoop(5) == 20);	// tests persistance of time between runs of loop
	/*ASSERT_TRUE(sim.SimLoop(1000) == 1020);*/ //because we're starting at 20
	// with the way we've built the time system we could run x amount of moves at a time to possibly create a "fast_forward" or "slow_down" command
}

void Tests::TestMapPrintCout() {
	sim.world.map.writeMapToCout();
}

void Tests::TestCivMakeTurn() {
	sim.civs.at("Brotherhood of Steel").MakeTurn();

	ASSERT_TRUE(false);
}

void Tests::RunTests() {
	RUN_TEST(TestWorldGetName, true);
	RUN_TEST(TestWorldGetSeed, true);
	RUN_TEST(TestCivFactoryGenCivSeed, true); // should only be marked active if on default seed
	RUN_TEST(TestCivMakeTurn, false);
	RUN_TEST(TestSimLoop, false);
	RUN_TEST(TestMapPrintCout, true);
	SUMMARY();
}
