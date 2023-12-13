// Turret.h
#pragma once

#include <string>
#include <glm/glm.hpp>
#include "core/gpu/mesh.h"

class Barracks {
public:
    Barracks::Barracks(Mesh* mesh, glm::vec3 position, std::string name);
    Barracks();
    ~Barracks();

    glm::vec3 getPosition();
    std::string getName();
    glm::vec3 getBoundingBoxSize();

private:
    Mesh* mesh;
    glm::vec3 position;
    std::string name;
    glm::vec3 boundingBox;
};

