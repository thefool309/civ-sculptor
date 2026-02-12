#pragma once
/// @file CoutRedirect.h
/// @brief thread-safe stdout capture for redirecting cout to a string buffer

#include <sstream>
#include <streambuf>
#include <mutex>
#include <iostream>

/// @brief RAII wrapper that captures std::cout output into a string buffer
///
/// on construction, replaces cout's streambuf with an internal stringstream.
/// on destruction, restores the original streambuf. used by SimulationApi
/// to capture simulation log output for polling from python.
class CoutRedirect {
	std::streambuf* old;   ///< saved original cout streambuf
	std::ostringstream ss; ///< internal capture buffer
	std::mutex mootex;     ///< protects concurrent access to the buffer

public:
	/// @brief redirect cout to the internal buffer
	CoutRedirect() : old(std::cout.rdbuf(ss.rdbuf())) {

	}

	/// @brief restore cout to its original streambuf
	~CoutRedirect() {
		std::cout.rdbuf(old);
	}

	/// @brief take all captured output and clear the buffer
	/// @return everything written to cout since last take() call
	std::string take() {
		std::lock_guard<std::mutex> lock(mootex);
		std::string out = ss.str();
		ss.str("");
		ss.clear();
		return out;
	}
};
