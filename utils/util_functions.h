#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <glm/glm.hpp>
#include <cstdlib> // for std::rand

class UtilFunctions {
public:
    // Generate a random position inside a the center part of the map (25.0f).
    static glm::vec3 GenerateRandomPositionInMap() {
        float x = static_cast<float>(std::rand()) / RAND_MAX * 25.0f;
        float z = static_cast<float>(std::rand()) / RAND_MAX * 25.0f;
        return glm::vec3(x, 0.0f, z);
    }

    // Add other utility functions as needed

private:
    // Private constructor to prevent instantiation
    UtilFunctions() {}
};

#endif
