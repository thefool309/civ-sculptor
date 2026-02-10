#pragma once
/// @file Resources.h
/// @brief resource types, deposits, and debt structures

#include "Const.h"
#include <string>

/// @brief enumeration of all resource types in the simulation
///
/// backed by uint8_t for compact storage. COUNT_RT is used as a sentinel
/// to track the total number of resource types.
enum class ResourceType : uint8_t {
	Food,
	Water,
	Wood,
	Stone,
	Metal,
	Gold,
	Oil,
	NuclearMat,

	COUNT_RT ///< sentinel value, total number of resource types
};

static_assert(
	std::size(Const::ResourceTypeNames) == static_cast<size_t>(ResourceType::COUNT_RT),
	"Resource Type Names out of sync!");

/// @brief a quantity of a specific resource type
struct Resources {
    ResourceType type;  ///< which resource this represents
    uint64_t amount;    ///< how much of the resource

    /// @param _type resource type
    /// @param _amount initial quantity
    Resources(ResourceType _type, uint64_t _amount) : type(_type), amount(_amount) {

    }
};

/// @brief a resource deposit on a tile, with extraction cost and regeneration
///
/// deposits sit on map tiles and can be extracted by civilizations. some are
/// renewable and regenerate over time, others deplete permanently.
struct ResourceDeposit {
	Resources resources;              ///< the underlying resource and amount
	ResourceType extractionResource;  ///< resource type needed to extract
	int extractionCost;               ///< cost per extraction
	bool renewable;                   ///< whether this deposit regenerates
	int regenRate;                    ///< regeneration rate per tick (if renewable)

	/// @param _resourceType type of resource in the deposit
	/// @param _amount initial quantity available
	/// @param _extractionResource resource required to extract
	/// @param _extractionCost cost per extraction operation
	/// @param _renewable whether the deposit regenerates
	/// @param _regenRate how much regenerates per tick
	ResourceDeposit(ResourceType _resourceType = ResourceType::Food,
		uint64_t _amount = 30,
		ResourceType _extractionResource = ResourceType::Food,
		int _extractionCost = 5,
		bool _renewable = true,
		int _regenRate = 5)
		: resources(_resourceType, _amount),
		  extractionResource(_extractionResource),
		  extractionCost(_extractionCost),
		  renewable(_renewable),
		  regenRate(_regenRate) {}

	/// @param _resources pre-built Resources object
	/// @param _extractionResource resource required to extract
	/// @param _extractionCost cost per extraction operation
	/// @param _renewable whether the deposit regenerates
	/// @param _regenRate how much regenerates per tick
	ResourceDeposit(Resources _resources,
		ResourceType _extractionResource = ResourceType::Food,
		int _extractionCost = 5,
		bool _renewable = true,
		int _regenRate = 5)
		: resources(_resources),
		  extractionResource(_extractionResource),
		  extractionCost(_extractionCost),
		  renewable(_renewable),
		  regenRate(_regenRate) {}


};

/// @brief represents a debt owed by one civilization to another
struct Debt {
	Resources resource; ///< the resource and amount owed

	std::string civID;  ///< identifier of the debtor civilization

	/// @param _civID debtor civ identifier
	/// @param _resource the owed resource
	Debt(std::string _civID, Resources _resource) : resource(_resource), civID(_civID) {}

	/// @param _civID debtor civ identifier
	/// @param type type of resource owed
	/// @param amount quantity owed
	Debt(std::string _civID, ResourceType type, unsigned int amount) : civID(_civID), resource(Resources(type, amount)) {}
};
