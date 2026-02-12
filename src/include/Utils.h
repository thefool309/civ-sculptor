#pragma once
/// @file Utils.h
/// @brief utility functions for console output and type conversions

#include <iostream>
#include "Resources.h"

/// @brief static utility helpers for console colors and type conversions
class Utils {
public:
    /// @brief set terminal text color using ANSI escape codes
    /// @param colorVal ANSI color code (e.g. 92 for green, 31 for red)
    static void SetColor(int colorVal) { std::cout << "\033[" << colorVal << "m"; }

    /// @brief reset terminal text color to default
    static void ResetColor() { std::cout << "\033[0m"; }

    /// @brief convert a ResourceType enum to its string name
    /// @param _type the resource type to convert
    /// @return human-readable resource name from Const::ResourceTypeNames
    static std::string ConvertResourceTypeToStringLiteral(ResourceType _type) {
        return Const::ResourceTypeNames[static_cast<size_t>(_type)];
    }
};
