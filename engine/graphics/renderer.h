// Renderer.h
#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "components/simple_scene.h"
#include "../../utils/camera.h"

#define CANNON_VERTICAL_AJUSTMENT_COEF 4.2f
#define CANNON_HORIZONTAL_AJUSTMENT_COEF 3.5f

class Renderer {
public:
    Renderer();
    ~Renderer();

    void RenderChassis(const std::unordered_map<std::string, Mesh*>& meshes,
                        const std::unordered_map<std::string, Shader*>& shaders,
                        Implemented::CameraAPI* camera,
                        const glm::mat4& projectionMatrix,
                        const glm::vec3& position,
                        float chassisRotationAngle,
                        const glm::vec3& trackColor,
                        const glm::vec3& bodyColor,
                        int trackDamageLevel,
                        bool isBodyDamaged);

    void Renderer::RenderTurret(std::string name, Mesh* mesh, Shader* shader,
                                Implemented::CameraAPI* camera,
                                const glm::mat4& projectionMatrix,
                                const glm::vec3& position,
                                float turretRotationAngle,
            					glm::vec3 color
    );

    void Renderer::RenderCannon(std::string name, Mesh* mesh, Shader* shader,
                                Implemented::CameraAPI* camera,
                                const glm::mat4& projectionMatrix,
                                const glm::vec3& position,
                                float turretRotationAngle,
                                float cannonRotationAngle,
                                glm::vec3 color
    );

    void Renderer::RenderShell(std::string name, Mesh* mesh, Shader* shader,
                                const glm::mat4& projectionMatrix,
                                const glm::vec3& position,
                                float turretRotationAngle,
                                float deltaTime
    );

    void Renderer::RenderBattlefield(std::string name, Mesh* mesh, Shader* shader,
                                    const glm::mat4& projectionMatrix,
                                    const glm::vec3& position);

    void Renderer::RenderBarracks(std::string name, Mesh* mesh, Shader* shader,
                                    Implemented::CameraAPI* camera,
                                    const glm::mat4& projectionMatrix,
                                    const glm::vec3& position);

private:
    // Other member variables and functions...
};