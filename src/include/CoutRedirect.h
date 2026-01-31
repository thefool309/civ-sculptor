#pragma once

#include <sstream>
#include <streambuf>
#include <mutex>
#include <iostream>

class CoutRedirect {
	std::streambuf* old;
	std::ostringstream ss;
	std::mutex mootex;

public:
	CoutRedirect() : old(std::cout.rdbuf(ss.rdbuf())) {

	}
	~CoutRedirect() {
		std::cout.rdbuf(old);
	}

	std::string take() {
		std::lock_guard<std::mutex> lock(mootex);
		std::string out = ss.str();
		ss.str("");
		ss.clear();
		return out;
	}
};