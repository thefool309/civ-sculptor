#include <stdio.h>
#include <iostream>
#include "../include/World.h"

inline int g_tests_passed = 0;
inline int g_tests_failed = 0;
void SetColor(int colorVal) {std::cout << "\033[" << colorVal << "m";}
void ResetColor() { std::cout << "\033[0m"; }
#define RUN_TEST(test) \
do { \
	std::cout << "\nRunning " << #test << "...\t"; \
	try { \
		test(); \
		SetColor(92); \
		std::cout << "PASS\n"; \
		ResetColor(); \
		++g_tests_passed; \
	} \
	catch(std::exception& e) { \
		SetColor(31); \
		std::cout << "FAIL: " << e.what() << "\n"; \
		ResetColor(); \
		++g_tests_failed; \
	} \
	catch(...) {\
		SetColor(31); \
		std::cout << "FAIL: Unknown Exception\n"; \
		ResetColor(); \
		++g_tests_failed; \
	} \
 } while(0) 

#define ASSERT_TRUE(con) \
do { \
	if (!(con)) throw std::runtime_error("Assert Failed!"); \
} while(0)

class Tests {
public:
	World world = World(123456, "Testonia");

	

	void TestWorldGetName() {
		ASSERT_TRUE(world.getName() == "Testonia");
	}

	void TestWorldGetSeed() {
		ASSERT_TRUE(world.getSeed() == 123456);
	}

	void TestWorldGenCivSeed() {
		/*std::cout << "\nGenerateCivSeed Russia Hash : " << world.GenerateCivSeed("Russia").rng_seed << '\n';*/
		ASSERT_TRUE(world.GenerateCivSeed("Russia").name == "Russia");
		ASSERT_TRUE(world.GenerateCivSeed("Russia").rng_seed == 11649118993674644964); // expected rng_seed for russia with the given world seed
	}

	void RunTests() {
		RUN_TEST(TestWorldGetName);
		RUN_TEST(TestWorldGetSeed);
		RUN_TEST(TestWorldGenCivSeed);
	}

};

int main() {
	printf("Hello world I'm a test harness! :3\n\n");
	Tests tests;
	
	tests.RunTests();
}