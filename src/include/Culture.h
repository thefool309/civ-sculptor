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