#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <glm/glm.hpp>
#include <cstdlib> // for std::rand

class UtilFunctions {
public:
    // Generate a random position inside a the center part of the map (20.0f).
    static glm::vec3 GenerateRandomPositionInMap() {
        // Use a random device to seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Define the distribution for x and z coordinates
        std::uniform_real_distribution<float> dis(-20.0f, 20.0f);

        // Generate random values for x and z
        float x = dis(gen);
        float z = dis(gen);

        return glm::vec3(x, 0.0f, z);
    }

    // Add other utility functions as needed

private:
    // Private constructor to prevent instantiation
    UtilFunctions() {}
};

#endif
