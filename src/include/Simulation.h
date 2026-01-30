#pragma once
#include <unordered_map>
#include "World.h"
#include "CivFactory.h"
#include "Utils.h"
/// <summary>
/// Our "God object" or the object that controls all objects beneath it. This is kind of the glue that puts our puzzle together.
/// 
/// See tests/test.h and tests/test.cpp for samples
/// </summary>
class Simulation {
private:
	
public:
	World world;
	std::unordered_map<std::string, Civilization> civs;
	
	Simulation(WorldSeed _seed) : world(_seed) {}

	void Generate10Civs();

	SimTick SimLoop(unsigned int _ticksToLoop);


};