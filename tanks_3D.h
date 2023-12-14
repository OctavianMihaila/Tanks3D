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
#define PI 3.14159265358979323846f
namespace m1 {
    class Tanks3D : public gfxc::SimpleScene {
    public:
        Tanks3D();
        ~Tanks3D();

        bool isOrtho = false;
        float orthoRight = 8.0f, orthoUp = 4.5f, orthoDown = -4.5f, orthoLeft = -8.0f;
        void Init() override;
        void CreateBarracks();
        void CreateEnemyTanks();

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void RenderShells(float deltaTimeSeconds);
        void RenderBarracks();
        void RenderEnemyTanks(float deltaTimeSeconds);
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

    protected:
        bool isLookingAround;
        glm::mat4 projectionMatrix;
        std::unordered_map<std::string, Mesh*> chassisMeshes;
        std::unordered_map<std::string, Shader*> chassisShaders;
        
        Tank *playerTank;
        Shell* shell;

        GameManager gameManager;
        Implemented::CameraAPI* camera;
        Renderer renderer;
    };
}
