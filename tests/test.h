/// @file test.h
/// @brief custom testing framework and test definitions

#include <iostream>
#include "../src/include/Utils.h"
#include "Simulation.h"
inline int g_tests_passed = 0;
inline int g_tests_failed = 0;

/// @brief lightweight testing framework with pass/fail tracking
///
/// provides InvokeTest() to run callables with exception-based assertions,
/// and Summary() to print results. uses ANSI colors for output.
class TestFramework {
public:
	/// @brief print the pass/fail summary to stdout
	static void Summary();

	/// @brief run a test callable, catching any exceptions as failures
	/// @tparam Callable invocable type (lambda, function pointer, etc)
	/// @param fn the test function to execute
	template<typename Callable>
	static void InvokeTest(Callable&& fn);
};

/// @brief collection of test cases for the simulation
///
/// constructs a full simulation with 10 civs on the default seed for testing.
/// each test method validates a specific aspect of the simulation.
class Tests {
public:
	WorldSeed seed;   ///< the world seed used for tests
	Simulation sim;   ///< the simulation instance under test

	/// @brief default constructor - uses seed 123456 and generates 10 civs
	Tests() : seed(123456, "Testonia"), sim(seed) {
		sim.Generate10Civs();
	}
	/// @brief construct from a pre-built WorldSeed
	/// @param _seed the world seed to use
	Tests(WorldSeed _seed) : seed(_seed), sim(seed) {}
	/// @brief construct from raw seed values
	/// @param rng_seed the rng seed value
	/// @param name the world name
	Tests(uint64_t rng_seed, std::string name) : seed(rng_seed, name), sim(seed) {}

	/// @brief test World::getName() returns expected value
	void TestWorldGetName();

	/// @brief test World::getSeed() returns expected value
	void TestWorldGetSeed();

	/// @brief test CivFactory::GenerateCivSeed() produces correct deterministic hashes
	void TestCivFactoryGenCivSeed();

	/// @brief test SimLoop tick persistence across multiple calls
	void TestSimLoop();

	/// @brief test map text output to cout
	void TestMapPrintCout();

	/// @brief test that a civilization can execute MakeTurn()
	void TestCivMakeTurn();

	/// @brief execute all test cases and print summary
	void RunTests();

};

/// @brief run a test function if active, or print disabled message
/// @param test the test method to invoke
/// @param active whether this test should run
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

/// @brief print the test summary
#define SUMMARY() \
do { \
	 TestFramework::Summary(); \
} while(0)

/// @brief assert a condition, throwing on failure
/// @param con the condition to assert
#define ASSERT_TRUE(con) \
do { \
	if (!(con)) throw std::runtime_error("Assert Failed!"); \
} while(0)


