#include <iostream>
#include "../src/include/Utils.h"
#include "Simulation.h"
inline int g_tests_passed = 0;
inline int g_tests_failed = 0;
/// <summary>
/// The framework for the testing macros. I built my own testing framework here, because it was easier than installing one imo.
/// </summary>
class TestFramework {
public:
	static void Summary();

	template<typename Callable>
	static void InvokeTest(Callable&& fn);
};

/// <summary>
/// the class where the test functions are written
/// </summary>
class Tests {
public:
	WorldSeed seed;
	Simulation sim;

	/// <summary>
	/// Default Constructor
	/// </summary>
	Tests() : seed(123456, "Testonia"), sim(seed) {
		sim.Generate10Civs();
	}
	/// <summary>
	/// Build from a `WorldSeed` object
	/// </summary>
	/// <param name="_seed"></param>
	Tests(WorldSeed _seed) : seed(_seed), sim(seed) {}
	/// <summary>
	/// Build from an rng_seed and a name (Builds world seed for you)
	/// </summary>
	/// <param name="rng_seed"></param>
	/// <param name="name"></param>
	Tests(uint64_t rng_seed, std::string name) : seed(rng_seed, name), sim(seed) {}
	
	/// <summary>
	/// Test `world::GetName()`
	/// </summary>
	void TestWorldGetName();
	
	/// <summary>
	/// Test `world::GetSeed()`
	/// </summary>
	void TestWorldGetSeed();
	
	/// <summary>
	/// Test `world::GenCivSeed()`
	/// this one is a special case because it can change from the default. 
	/// </summary>
	void TestWorldGenCivSeed();

	/// <summary>
	/// Test how the SimTime behaves in relation to running the SimLoop and ensure persistance between calls to SimLoop
	/// </summary>
	void TestSimLoop();

	void TestCivMakeTurn();

	/// <summary>
	/// Execute all tests
	/// </summary>
	void RunTests();

};

#define RUN_TEST(test, active) \
do { \
	if(active) { \
		std::cout << "\nRunning " << #test << "...\t"; \
		TestFramework::InvokeTest([&] { test(); }); \
	} \
	else { \
		std::cout << "\nTest: " << #test << " disabled...\n"; \
	} \
 } while(0) 

#define SUMMARY() \
do { \
	 TestFramework::Summary(); \
} while(0)

#define ASSERT_TRUE(con) \
do { \
	if (!(con)) throw std::runtime_error("Assert Failed!"); \
} while(0)


