#pragma once

#include "components/simple_scene.h"
#include "utils/camera.h"
#include "engine/graphics/renderer.h"
#include "engine/game_manager.h"
#include "models/tank.h"
#include "utils/util_functions.h"

#define MOUSE_SENSITIVITY_OX 0.01f
#define DISTANCE_TO_TANK 3.0f
#define HEIGHT_ABOVE_TANK 1.5f

namespace m1
{
    class Tanks3D : public gfxc::SimpleScene
    {
    public:
        Tanks3D();
        ~Tanks3D();

        bool isOrtho = false;
        float orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5f, orthoLeft = -8.0f;

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat4 projectionMatrix;
        bool isLookingAround;

        GameManager gameManager;
        Implemented::CameraAPI* camera;
        Renderer renderer;
        std::unordered_map<std::string, Mesh*> chassisMeshes;
        std::unordered_map<std::string, Shader*> chassisShaders;
        Tank playerTank;
        Shell *shell;
    };
}   // namespace m1
