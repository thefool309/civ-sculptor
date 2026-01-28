#include <string>
#include <unordered_map>

enum ResourceType {

};

enum TraitArchetype {

};

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

struct CulturalTrait {
	int traitID;
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

	int civID;

	Debt(int _civID, Resources _resource) : resource(_resource), civID(_civID) {}

	Debt(int _civID, ResourceType type, unsigned int amount) : civID(_civID), resource(Resources(type, amount)) {}
};

class Civilization {
	int civID;
	std::string name = "Testonia";
	long population = 2;
	std::unordered_map<ResourceType, Resources> resource_map;
	long research_points = 0;
	CulturalSummary cultural_summ;
	std::unordered_map<TraitArchetype, CulturalTrait> trait_map;

public:
	Civilization(const int& _civID, const std::string& _name, const unsigned int& _pop, const std::unordered_map<ResourceType, Resources>& _resources)
		: civID(_civID), name(_name), population(_pop), resource_map(_resources) {
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

	void add_resource(ResourceType type, unsigned int amount) {
		auto it = resource_map.find(type);
		
		if (it != resource_map.end()) {
			it->second.amount += amount;
		}
		else {
			resource_map.emplace(type, Resources(type, amount));
		}
	}

};