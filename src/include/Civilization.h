#include <string>
#include <unordered_map>
#include "RandomEngine.h"

enum ResourceType {
	gold = 0,
	
	COUNT_RT
};
/// <summary>
///	An enum representing domains of decision.
/// 
/// TraitArchetype Definitions
///
///Social:
///Governs how agents value, trust, and cooperate with one another.
///
///Authority :
///	Governs how power is structured, justified, and obeyed.
///
///	Identity :
///	Governs who is considered part of the group and under what conditions.
///
///	Knowledge :
///	Governs how beliefs are formed, validated, and preserved.
///
///	Adaptation :
///	Governs how behavior and institutions change in response to pressure.
///
///	Conflict :
///	Governs thresholds, norms, and escalation of violence.
///
///	Economy :
///	Governs how resources are produced, allocated, and incentivized.
///
///	Temporal :
///	Governs how past and future are weighted in decision - making.
///
///	Environment :
///	Governs interaction with, extraction from, and care for surroundings.
///
///	Meta :
///	Governs persistence, inheritance, and mutability of traits themselves.
/// </summary>
enum class TraitArchetype {
	Social,
	Authority,
	Identity,
	Knowledge,
	Adaptation,
	Conflict,
	Economic,
	Temporal,
	Environmental,
	Meta,

	COUNT
};
/// <summary>
/// various figures decided from all the civs traits as a whole
/// </summary>
struct CulturalSummary {
	float avg_hierarchy_bias = 0;	// an average of all traits
	float avg_collectivism = 0;
	float avg_risk_tolerance = 0;
	float avg_adaptability = 0;

	float variance_hierarchy = 0;	// measured internal diversity
	float variance_collectivism = 0;
	float variance_risk_tolerance = 0;
	float variance_adaptability = 0;

	int trait_count = 0;		// number of active traits
};
/// <summary>
/// 
/// </summary>
struct CulturalTrait {
	std::string traitID;
	TraitArchetype archetype;   // warfare, trade, religion, governance
	float hierarchy_bias;       // continuous axes
	float collectivism;
	float risk_tolerance;
	float adaptability;
};

struct Resources {
	ResourceType type;
	unsigned int amount;
	
	Resources(ResourceType _type, unsigned int _amount) : type(_type), amount(_amount) {}
};

struct Debt {
	// in the case of the debt the amount represents the amount owed.
	Resources resource;

	std::string civID;

	Debt(std::string _civID, Resources _resource) : resource(_resource), civID(_civID) {}

	Debt(std::string _civID, ResourceType type, unsigned int amount) : civID(_civID), resource(Resources(type, amount)) {}
};

class Civilization {
	std::string civID;
	std::string name = "Testonia";
	long population = 2;
	std::unordered_map<ResourceType, Resources> resource_map;
	long research_points = 0;
	CulturalSummary cultural_summ;
	std::unordered_map<int, CulturalTrait> trait_map;
	RandomEngine rng;
	CivSeed seed;

public:
	Civilization(const std::string& _civID, const std::string& _name, CivSeed _seed) : civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed) {
		resource_map.insert(std::pair<ResourceType, Resources>(ResourceType::gold, Resources(ResourceType::gold, 100)));
	}

	Civilization(const std::string& _civID, const std::string& _name, CivSeed _seed, const unsigned int& _pop, const std::unordered_map<ResourceType, Resources>& _resources)
		: civID(_civID), name(_name), seed(_seed), rng(_seed.rng_seed), population(_pop), resource_map(_resources) {
	}

	std::string get_name() {
		return name;
	}

	long get_population() {
		return population;
	}

	long get_research_points() {
		return research_points;
	}

	std::unordered_map<ResourceType, Resources> get_resource_map() {
		return resource_map;
	}

	void add_resource(ResourceType type, unsigned int amount);

};