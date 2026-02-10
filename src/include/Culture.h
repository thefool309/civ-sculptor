#pragma once
/// @file Culture.h
/// @brief cultural trait system - archetypes, traits, and cultural summaries

/// @brief domains of decision that traits can belong to
///
/// each trait is categorized under one archetype. the archetype determines
/// which aspect of civilization behavior the trait primarily influences.
///
/// - **Social**: how agents value, trust, and cooperate with one another
/// - **Authority**: how power is structured, justified, and obeyed
/// - **Identity**: who is considered part of the group and under what conditions
/// - **Knowledge**: how beliefs are formed, validated, and preserved
/// - **Adaptation**: how behavior and institutions change in response to pressure
/// - **Conflict**: thresholds, norms, and escalation of violence
/// - **Economic**: how resources are produced, allocated, and incentivized
/// - **Temporal**: how past and future are weighted in decision-making
/// - **Environmental**: interaction with, extraction from, and care for surroundings
/// - **Meta**: persistence, inheritance, and mutability of traits themselves
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

	COUNT_TA ///< sentinel value, total number of archetypes
};

/// @brief aggregate statistics computed from all of a civilization's traits
///
/// these values summarize the overall cultural tendencies of a civilization
/// and are used in decision-making calculations.
struct CulturalSummary {

	/// preference for structured power and rank.
	/// lower = more egalitarian, higher = more authoritarian
	float avg_hierarchy_bias = 0;
	/// preference for group needs over individual needs.
	/// lower = more individualistic, higher = more collectivist
	float avg_collectivism = 0;
	/// willingness to take risks in strategy, innovation, and expansion.
	/// lower = more cautious, higher = more risk-taking
	float avg_risk_tolerance = 0;
	/// capability to adapt to changing conditions (environmental, technological, cultural).
	/// lower = resistant to change, higher = handles change well
	float avg_adaptability = 0;

	float variance_hierarchy = 0;       ///< internal diversity of hierarchy bias
	float variance_collectivism = 0;    ///< internal diversity of collectivism
	float variance_risk_tolerance = 0;  ///< internal diversity of risk tolerance
	float variance_adaptability = 0;    ///< internal diversity of adaptability

	int trait_count = 0;  ///< number of active traits
};

/// @brief a single cultural trait that influences civilization decision-making
///
/// traits are placed into a collection and their four axis scores collectively
/// determine how a civilization behaves. each trait belongs to a TraitArchetype
/// that categorizes its domain of influence.
struct CulturalTrait {
	std::string traitID;          ///< unique identifier for this trait
	std::string name;             ///< human-readable trait name
	TraitArchetype archetype;     ///< which domain this trait belongs to

	/// how authoritarian the trait is. promotes strict vertical power = high value
	float hierarchy_bias;
	/// how much this trait prefers group needs over individual needs
	float collectivism;
	/// how much this trait promotes risk taking in expansion, innovation, or strategy
	float risk_tolerance;
	/// this trait's ability to help the civ adjust to changing conditions
	float adaptability;
};
