#pragma once
/// @file CivFactory.h
/// @brief factory for creating civilizations from seeds, names, or text files

#include "Civilization.h"

/// @brief static factory for creating Civilization instances
///
/// handles seed generation via FNV-1a hashing, single civ creation,
/// and batch creation from text file lists. maintains an auto-incrementing
/// CivId counter for unique identification.
class CivFactory {
private:
    static CivId currentCivId; ///< auto-incrementing id counter

	/// @brief read civilization names from a text file (one per line)
	/// @param _filepath path to the text file
	/// @return vector of civilization name strings
	static std::vector<std::string> ReadCivNamesFromTxt(std::string& _filepath);
public:

    /// @brief generate a deterministic CivSeed from a name and world seed
    ///
    /// uses FNV-1a hash: the name bytes are hashed first, then the world seed
    /// is XOR'd in to make it deterministic per-world.
    /// @param name civilization name to hash
    /// @param _worldSeed the world's master rng seed
    /// @return CivSeed with the computed hash and name
    static CivSeed GenerateCivSeed(std::string name, uint64_t _worldSeed);

	/// @brief create a civilization directly from a pre-built CivSeed
	/// @param seed the seed containing rng seed and name
	/// @return fully constructed Civilization
	static Civilization CreateCivilization(CivSeed seed);

	/// @brief create a civilization from a name and world seed (generates seed internally)
	/// @param name civilization name
	/// @param _worldSeed the world's master rng seed
	/// @return fully constructed Civilization
	static Civilization CreateCivilization(std::string name, uint64_t _worldSeed);

	/// @brief batch-create civilizations from a text file of names
	///
	/// reads names from the file, shuffles them using the provided rng,
	/// then creates a Civilization for each name.
	/// @param _filepath path to the text file containing names
	/// @param _worldSeed the world's master rng seed
	/// @param rng random engine used to shuffle the name list
	/// @return map of civilization name to Civilization object
	static std::unordered_map<std::string, Civilization> GenCivsFromList(std::string _filepath, uint64_t _worldSeed, RandomEngine rng);

};


