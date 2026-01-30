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

void Tests::TestWorldGenCivSeed() {
	/*std::cout << "\nGenerateCivSeed Russia Hash : " << world.GenerateCivSeed("Russia").rng_seed << '\n';*/
	ASSERT_TRUE(sim.world.GenerateCivSeed("Russia").name == "Russia");
	ASSERT_TRUE(sim.world.GenerateCivSeed("Russia").rng_seed == 11649118993674644964); // expected rng_seed for russia with the given world seed
}

void Tests::TestCivMakeTurn() {
	sim.civs.at("Brotherhood of Steel").MakeTurn();

	ASSERT_TRUE(false);
}

void Tests::RunTests() {
	RUN_TEST(TestWorldGetName, true);
	RUN_TEST(TestWorldGetSeed, true);
	RUN_TEST(TestWorldGenCivSeed, true); // should only be marked active if on default seed
	RUN_TEST(TestCivMakeTurn, true);
	SUMMARY();
}
