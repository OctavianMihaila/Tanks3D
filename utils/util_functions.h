#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H

#include <glm/glm.hpp>
#include <cstdlib>

class UtilFunctions {
public:
    // Generate a random position inside a the center part of the map (20.0f).
    static glm::vec3 GenerateRandomPositionInMap() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-20.0f, 20.0f);
        float x = dis(gen);
        float z = dis(gen);

        return glm::vec3(x, 0.0f, z);
    }

private:
    UtilFunctions() {} // Prevent instantiation.
};

#endif
