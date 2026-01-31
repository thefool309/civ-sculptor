#include "Simulation.h"
void Simulation::Generate3Civs() {
	for (int i = 0; i < 3; i++) {
		CivSeed seed = CivSeed(0ULL, "");
		switch (i + 1) {
		case 1:
			seed = world.GenerateCivSeed("Caesar's Legion");
			break;
		case 2:
			seed = world.GenerateCivSeed("New California Republic");
			break;
		case 3:
			seed = world.GenerateCivSeed("The Children of Atom");
			break;
		default:
			seed = world.GenerateCivSeed("YOU MESSED UP");
			break;
		}

		
		Civilization newCiv = CivFactory::CreateCivilization(seed);
		
		civs.insert(std::pair<std::string, Civilization>(newCiv.get_name(), newCiv));

		
		std::cout << newCiv.get_name() << " created!!!\n";
	}
}
void Simulation::Generate5Civs() {
	for (int i = 0; i < 5; i++) {
		CivSeed seed = CivSeed(0ULL, "");
		switch (i + 1) {
		case 1:
			seed = world.GenerateCivSeed("Caesar's Legion");
			break;
		case 2:
			seed = world.GenerateCivSeed("New California Republic");
			break;
		case 3:
			seed = world.GenerateCivSeed("The Children of Atom");
			break;
		case 4:
			seed = world.GenerateCivSeed("Brotherhood of Steel");
			break;
		case 5:
			seed = world.GenerateCivSeed("Powder Gangers");
			break;
		default:
			seed = world.GenerateCivSeed("YOU MESSED UP");
			break;
		}

		
		Civilization newCiv = CivFactory::CreateCivilization(seed);
		
		civs.insert(std::pair<std::string, Civilization>(newCiv.get_name(), newCiv));

		
		std::cout << newCiv.get_name() << " created!!!\n";
		
	}
}
/// <summary>
/// Generate 10 civilizations (some themed on fallout factions). Do this to create a group of civs to play in the sim for testing purposes.
/// </summary>
void Simulation::Generate10Civs() {
	for (int i = 0; i < 10; i++) {
		CivSeed seed = CivSeed(0ULL, "");
		switch (i + 1) {
		case 1:
			seed = world.GenerateCivSeed("Caesar's Legion");
			break;
		case 2:
			seed = world.GenerateCivSeed("New California Republic");
			break;
		case 3:
			seed = world.GenerateCivSeed("The Children of Atom");
			break;
		case 4:
			seed = world.GenerateCivSeed("Brotherhood of Steel");
			break;
		case 5:
			seed = world.GenerateCivSeed("Powder Gangers");
			break;
		case 6:
			seed = world.GenerateCivSeed("New Vegas Strip");
			break;
		case 7:
			seed = world.GenerateCivSeed("The CommonWealth");
			break;
		case 8:
			seed = world.GenerateCivSeed("The Texan Empire");
			break;
		case 9:
			seed = world.GenerateCivSeed("The Florida Tribes");
			break;
		case 10:
			seed = world.GenerateCivSeed("The Ohio Tribunal");
			break;
		default:
			seed = world.GenerateCivSeed("YOU MESSED UP");
			break;
		}

		Civilization newCiv = CivFactory::CreateCivilization(seed);
		civs.insert(std::pair<std::string, Civilization>(newCiv.get_name(), newCiv));

		std::cout << newCiv.get_name() << " created!!!\n";
	}
}
/// <summary>
/// the core logic loop of the simulation. can be called in any increment as it takes a number of repititions and executes that many turns for every civilization 
/// </summary>
/// <param name="_ticksToLoop"> - number of ticks to loop for</param>
/// <returns>SimTick = uint64_t</returns>
SimTick Simulation::SimLoop(unsigned int _ticksToLoop) {
	for (int i = 0; i < _ticksToLoop; i++) {
		// TODO: Execute Sim Logic
		// each civ takes their turn
		for (auto& civ : civs) {	// the civs collection is a map, so it returns a std::pair<std::string, Civilization> the string is the name of the civ
			civ.second.MakeTurn();	// civ.second is value (Civilization)
		}
		
		std::cout << "End of Tick " << world.time.current_tick << '\n';

		// advance to next tick
		world.time.advance();
	}

	return world.time.current_tick;
}
