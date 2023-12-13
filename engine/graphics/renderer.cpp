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
    float chassisRotationAngle,
    const glm::vec3& trackColor,
    const glm::vec3& bodyColor,
    int trackDamageLevel,
    bool isBodyDamaged) { // Add color as an argument
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

            if (std::string(shader->GetName()) == "track") {
				int colorLoc = glGetUniformLocation(shader->program, "color");
				glUniform3f(colorLoc, trackColor.r, trackColor.g, trackColor.b);

                // Set the deformation parameter based on the damaged state
                int deformationParameterLoc = glGetUniformLocation(shader->program, "deformationParameter");
                glUniform1f(deformationParameterLoc, trackDamageLevel);
			}

            if (std::string(shader->GetName()) == "body") {
				int colorLoc = glGetUniformLocation(shader->program, "baseColor");
				glUniform3f(colorLoc, bodyColor.r, bodyColor.g, bodyColor.b);

                int deformationParameterLoc = glGetUniformLocation(shader->program, "deformationParameter");
                glUniform1f(deformationParameterLoc, isBodyDamaged ? 1.0f : 0.0f);
			}

            mesh->Render();
        }
    }
}

void Renderer::RenderTurret(std::string name, Mesh *mesh, Shader *shader,
                            Implemented::CameraAPI *camera,
                            const glm::mat4& projectionMatrix,
                            const glm::vec3& position,
                            float turretRotationAngle,
                            glm::vec3 color) {
                            
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, turretRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int colorLoc = glGetUniformLocation(shader->program, "baseColor");
    glUniform3f(colorLoc, color.r, color.g, color.b);

    mesh->Render();
}

void Renderer::RenderCannon(std::string name, Mesh* mesh, Shader* shader,
    Implemented::CameraAPI* camera,
    const glm::mat4& projectionMatrix,
    const glm::vec3& position,
    float turretRotationAngle,
    float cannonRotationAngle,
    glm::vec3 color) {

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

    int colorLoc = glGetUniformLocation(shader->program, "baseColor");
    glUniform3f(colorLoc, color.r, color.g, color.b);

    mesh->Render();
}

void Renderer::RenderShell(std::string name, Mesh* mesh, Shader* shader,
    const glm::mat4& projectionMatrix,
    const glm::vec3& position,
    float turretRotationAngle,
    float deltaTime) {

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);

    // rotate the bullet based on the turret's rotation angle
    modelMatrix = glm::rotate(modelMatrix, turretRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    //// Scale it a little bit
    modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 2.0f, 2.0f));

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

void Renderer::RenderBarracks(std::string name, Mesh* mesh, Shader* shader,
    Implemented::CameraAPI* camera,
    const glm::mat4& projectionMatrix,
    const glm::vec3& position) {

    // Translating and rotating the barracks to the desired position.
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}
