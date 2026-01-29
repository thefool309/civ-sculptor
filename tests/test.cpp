#include <stdio.h>
#include "../include/World.h"

inline int g_tests_passed = 0;
inline int g_tests_failed = 0;

#define RUN_TEST(test) \
do { \
	std::cout << "\nRunning " << #test << "...\t"; \
	try { \
		test(); \
		std::cout << "PASS\n"; \
		++g_tests_passed; \
	} \
	catch(std::exception& e) { \
		std::cout << "FAIL: " << e.what() << "\n"; \
		++g_tests_failed; \
	} \
	catch(...) {\
		std::cout << "FAIL: Unknown Exception\n"; \
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


	void RunTests() {
		RUN_TEST(TestWorldGetName);
		RUN_TEST(TestWorldGetSeed);
	}

};

int main() {
	printf("Hello world I'm a test harness! :3\n\n");
	Tests tests;
	
	tests.RunTests();
}