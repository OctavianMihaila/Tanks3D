// Renderer.cpp
#include "Renderer.h"

Renderer::Renderer() {
    // Initialize other members
}

Renderer::~Renderer() {
    // Clean up resources
}

// TODO: REFACTORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR

void Renderer::RenderChassis(const std::unordered_map<std::string, Mesh*>& meshes,
                            const std::unordered_map<std::string, Shader*>& shaders,
                            Implemented::CameraAPI* camera,
                            const glm::mat4& projectionMatrix,
                            const glm::vec3& position,
                            float chassisRotationAngle) {
    for (const auto& entry : meshes) {
        const std::string& componentName = entry.first;
        Mesh* mesh = entry.second;
        Shader* shader = shaders.at(componentName);  // Assuming shaders have the same names as components

        if (mesh && shader) {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, position);
            modelMatrix = glm::rotate(modelMatrix, chassisRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

            shader->Use();
            glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
            glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
            glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            mesh->Render();
        }
    }
}

void Renderer::RenderTurret(std::string name, Mesh *mesh, Shader *shader,
                            Implemented::CameraAPI *camera,
                            const glm::mat4& projectionMatrix,
                            const glm::vec3& position,
                            float turretRotationAngle) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, turretRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Renderer::RenderCannon(std::string name, Mesh* mesh, Shader* shader,
    Implemented::CameraAPI* camera,
    const glm::mat4& projectionMatrix,
    const glm::vec3& position,
    float turretRotationAngle,
    float cannonRotationAngle) {

    // Translating and rotating the cannon to the turret's position.
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, turretRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    // Moving the cannon upwards or downwards depending on the cannon's rotation angle.
    glm::mat4 cannonRotationMatrix = glm::mat4(1.0f);
    cannonRotationMatrix = glm::rotate(cannonRotationMatrix, cannonRotationAngle, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = modelMatrix * cannonRotationMatrix;

    // Small ajustments so that the cannon and the turret are aligned correctly.
    glm::vec3 cannonTranslation = glm::vec3(0.0f, -(cannonRotationAngle / CANNON_VERTICAL_AJUSTMENT_COEF),
                                            -(cannonRotationAngle / CANNON_HORIZONTAL_AJUSTMENT_COEF));
    glm::mat4 cannonTranslationMatrix = glm::mat4(1.0f);
    cannonTranslationMatrix = glm::translate(cannonTranslationMatrix, cannonTranslation);
    modelMatrix = modelMatrix * cannonTranslationMatrix;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Renderer::RenderShell(std::string name, Mesh* mesh, Shader* shader,
    const glm::mat4& projectionMatrix,
    const glm::vec3& position,
    float turretRotationAngle,
    float deltaTime) {

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);

    //// Scale it a little bit
    modelMatrix = glm::scale(modelMatrix, glm::vec3(3.0f, 3.0f, 3.0f));

    // rotate the bullet based on the turret's rotation angle
    modelMatrix = glm::rotate(modelMatrix, turretRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));


    shader->Use();
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void Renderer::RenderBattlefield(std::string name, Mesh* mesh, Shader* shader,
    const glm::mat4& projectionMatrix,
    const glm::vec3& position) {
    
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);

    shader->Use();

    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}