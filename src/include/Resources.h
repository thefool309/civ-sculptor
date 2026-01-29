#pragma once

enum ResourceType {
	gold = 0,

	COUNT_RT
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