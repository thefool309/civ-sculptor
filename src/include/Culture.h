#pragma once
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

	COUNT_TA
};
/// <summary>
/// various figures decided from all the civs traits as a whole
/// </summary>
struct CulturalSummary {

	
	// a civilizations preference for structured power and rank
	// lower score means a flatter more egalitarian society
	// higher score means a more authoritarian society
	float avg_hierarchy_bias = 0;	
	// a civilizations preference for group needs over individual needs
	// lower score means a more individualistic attitude
	// higher score means a more collectivist attitude
	float avg_collectivism = 0;
	// how much a society takes risks in strategy, innovation, and expansion.
	// lower score the society is more cautious
	// higher score the society is more risky
	float avg_risk_tolerance = 0;
	// how capable a society is to adapt to changing conditions. Environmental, technological, cultural
	// lower score the society is more resistant to changing conditions and struggles with them
	// higher score the society handles changing conditions with understanding and patience
	float avg_adaptability = 0;		// averages of all traits

	float variance_hierarchy = 0;	
	float variance_collectivism = 0;
	float variance_risk_tolerance = 0;
	float variance_adaptability = 0;	// measured internal diversity

	int trait_count = 0;		// number of active traits
};
/// <summary>
/// a single trait of the society that is placed into a collection of traits, the four scores will effect how a civilization makes decisions.
/// </summary>
struct CulturalTrait {
	std::string traitID;
	std::string name;
	TraitArchetype archetype;   

	// hierarchy_bias is how authoritarian the trait is. If it promotes a strict vertical power structure then it has a high hierarchy_bias
	float hierarchy_bias;       // continuous axes
	// how much a trait prefers group needs over individual needs. 
	float collectivism;
	// how much a trait promotes risk taking either in expansion, innovation, or strategy
	float risk_tolerance;
	// traits ability to help the civ adjust to changing conditions
	float adaptability;
};