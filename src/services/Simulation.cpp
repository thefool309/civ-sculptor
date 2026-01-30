#include "Simulation.h"

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
			break;
		}

		Utils::SetColor(95);
		Civilization newCiv = CivFactory::CreateCivilization(seed);
		Utils::ResetColor();
		civs.insert(std::pair<std::string, Civilization>(newCiv.get_name(), newCiv));

		Utils::SetColor(96);
		std::cout << newCiv.get_name() << " created!!!\n";
		Utils::ResetColor();
	}
}

SimTick Simulation::SimLoop(unsigned int _ticksToLoop) {
	for (int i = 0; i < _ticksToLoop; i++) {
		// TODO: Execute Sim Logic

		// each civ takes their turn
		for (auto& civ : civs) {
			civ.second.MakeTurn();
		}
		Utils::SetColor(97);
		std::cout << "End of Tick " << world.time.current_tick << '\n';
		Utils::ResetColor();

		// advance to next tick
		world.time.advance();
	}

	return world.time.current_tick;
}
