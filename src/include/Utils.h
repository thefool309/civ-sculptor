#pragma once

#include <iostream>
#include "Resources.h"

class Utils {
public:
    static void SetColor(int colorVal) { std::cout << "\033[" << colorVal << "m"; }
    static void ResetColor() { std::cout << "\033[0m"; }
    static std::string ConvertResourceTypeToStringLiteral(ResourceType _type) {
        return Const::ResourceTypeNames[static_cast<size_t>(_type)];
    }
};