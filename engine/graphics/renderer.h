#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include "components/simple_scene.h"
#include "../../utils/camera.h"
#include "../../models/tank.h"
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
                        Tank *playerTank);

    void Renderer::RenderTurret(std::string name, Mesh* mesh, Shader* shader,
                                Implemented::CameraAPI* camera,
                                const glm::mat4& projectionMatrix,
                                Tank* playerTank);

    void Renderer::RenderCannon(std::string name, Mesh* mesh, Shader* shader,
                                Implemented::CameraAPI* camera,
                                const glm::mat4& projectionMatrix,
                                Tank* playerTank);

    void Renderer::RenderShell(std::string name, Mesh* mesh, Shader* shader,
                                const glm::mat4& projectionMatrix,
                                Shell* shell,
                                float deltaTime);

    void Renderer::RenderBattlefield(std::string name, Mesh* mesh, Shader* shader,
                                    Implemented::CameraAPI* camera,
                                    const glm::mat4& projectionMatrix,
                                    const glm::vec3& position);

    void Renderer::RenderBarracks(std::string name, Mesh* mesh, Shader* shader,
                                    Implemented::CameraAPI* camera,
                                    const glm::mat4& projectionMatrix,
                                    const glm::vec3& position);
};