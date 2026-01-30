#pragma once
#include "Const.h"
/// <summary>
/// ResourceType is an enumeration class that defines various types of resources, 
/// such as Food, Water, and Metal, using an underlying type of uint8_t to represent them efficiently.
/// </summary>
enum class ResourceType : uint8_t {
	Food,
	Water,
	Wood,
	Stone,
	Metal,
	Gold,
	Oil,
	NuclearMat,

	COUNT_RT
};

static_assert(
	std::size(Const::ResourceTypeNames) == static_cast<size_t>(ResourceType::COUNT_RT), 
	"Resource Type Names out of sync!");


struct Resources {
	ResourceType type;
	uint64_t amount;

	Resources(ResourceType _type, uint64_t _amount) : type(_type), amount(_amount) {
		
	}
};

struct ResourceDeposit {
	Resources resources;
	ResourceType extractionResource;
	int extractionCost;
	bool renewable;
	int regenRate;

	ResourceDeposit(ResourceType _resourceType = ResourceType::Food,
		uint64_t _amount = 30,
		ResourceType _extractionResource = ResourceType::Food,
		int _extractionCost = 5,
		bool _renewable = true,
		int regenRate = 5)
		: resources(_resourceType, _amount),
		  extractionResource(_extractionResource),
		  extractionCost(_extractionCost) {}

	ResourceDeposit(Resources _resources,
		ResourceType _extractionResource = ResourceType::Food,
		int _extractionCost = 5,
		bool _renewable = true,
		int regenRate = 5)
		: resources(_resources),
		  extractionResource(_extractionResource),
		  extractionCost(_extractionCost) {}

	
};

struct Debt {
	// in the case of the debt the amount represents the amount owed.
	Resources resource;

	std::string civID;

	Debt(std::string _civID, Resources _resource) : resource(_resource), civID(_civID) {}

	Debt(std::string _civID, ResourceType type, unsigned int amount) : civID(_civID), resource(Resources(type, amount)) {}
};