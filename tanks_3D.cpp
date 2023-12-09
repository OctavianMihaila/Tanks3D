#include "lab_m1/tema2/tanks_3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tanks3D::Tanks3D(){
}


Tanks3D::~Tanks3D()
{
}


void Tanks3D::Init()
{
    Mesh* mesh = nullptr;
    Shader* shader = nullptr;
    renderCameraTarget = false;
    renderer = Renderer();
    camera = new Implemented::CameraAPI();
    Chassis chassis = Chassis();
    Cannon cannon = Cannon();
    Turret turret = Turret();
    playerTank = Tank(chassis, turret, cannon);
    
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    mesh = new Mesh("track");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank components"), "track.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("turret");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank components"), "turret.obj");
	meshes[mesh->GetMeshID()] = mesh;

	mesh = new Mesh("body");
	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank components"), "body.obj");
	meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("cannon");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank components"), "cannon.obj");
    meshes[mesh->GetMeshID()] = mesh;

	shader = new Shader("track");
	shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TrackVertexShader.glsl"), GL_VERTEX_SHADER);
	shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TrackFragmentShader.glsl"), GL_FRAGMENT_SHADER);
	shader->CreateAndLink();
	shaders[shader->GetName()] = shader;

    shader = new Shader("body");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "BodyVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "BodyFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

	shader = new Shader("turret");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TurretVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TurretFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

    shader = new Shader("cannon");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "CannonVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "CannonFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

    chassisMeshes = {
        {"track", meshes["track"]},
        {"body", meshes["body"]},
    };

    chassisShaders = {
        {"track", shaders["track"]},
        {"body", shaders["body"]},
    };
}


void Tanks3D::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // Dark grey color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}



void Tanks3D::Update(float deltaTimeSeconds)
{
    if (playerTank.isMoving()) {
        playerTank.move(deltaTimeSeconds);
    }

    if (playerTank.isAiming()) {
        playerTank.aim(deltaTimeSeconds);
    }


    renderer.RenderChassis(chassisMeshes, chassisShaders, camera, projectionMatrix, playerTank.getPosition(), playerTank.getChassis()->getRotationAngle());
    renderer.RenderTurret("turret", meshes["turret"], shaders["turret"], camera, projectionMatrix, playerTank.getPosition(), playerTank.getTurret()->getRotationAngle());
    renderer.RenderCannon("cannon", meshes["cannon"], shaders["cannon"], camera, projectionMatrix, playerTank.getPosition(), playerTank.getTurret()->getRotationAngle(), playerTank.getCannon()->getRotationAngle());
}


void Tanks3D::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tanks3D::OnInputUpdate(float deltaTime, int mods)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_U)) {
            camera->TranslateForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_H)) {
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_J)) {
            camera->TranslateForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_K)) {
            camera->TranslateRight(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            camera->TranslateUpward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            camera->TranslateUpward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_O)) {
            orthoLeft = -8.0f;
            orthoRight = 8.0f;
            orthoUp = 4.5f;
            orthoDown = -4.5;
            projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
            isOrtho = true;
        }

        if (window->KeyHold(GLFW_KEY_L)) {
            projectionMatrix = glm::perspective(90.f, 2.f, 2.f, 200.0f);
            isOrtho = false;
        }

        if (window->KeyHold(GLFW_KEY_K)) {
            projectionMatrix = glm::perspective(45.f, 2.f, 2.f, 200.0f);
            isOrtho = false;
        }

        if (window->KeyHold(GLFW_KEY_1)) {
            orthoLeft += deltaTime * cameraSpeed;
            projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
            isOrtho = true;
        }

        if (window->KeyHold(GLFW_KEY_2)) {
            orthoLeft -= deltaTime * cameraSpeed;
            projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
            isOrtho = true;
        }

    }

}


void Tanks3D::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_W) {
        playerTank.setMovingState(true, FORWARD);
    }

    if (key == GLFW_KEY_S) {
        playerTank.setMovingState(true, BACKWARD);
    }

    if (key == GLFW_KEY_A) {
		playerTank.setMovingState(true, LEFT);
	}

    if (key == GLFW_KEY_D) {
        playerTank.setMovingState(true, RIGHT);
    }

    if (key == GLFW_KEY_Q) {
        playerTank.setCannonAimingState(true, UP);
    }

    if (key == GLFW_KEY_E) {
		playerTank.setCannonAimingState(true, DOWN);
    }
}


void Tanks3D::OnKeyRelease(int key, int mods)
{
    if (key == GLFW_KEY_O) {
        orthoLeft = -8.0f;
        orthoRight = 8.0f;
        orthoUp = 4.5f;
        orthoDown = -4.5;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
        isOrtho = true;
    }

    if (key == GLFW_KEY_P) {
        projectionMatrix = glm::perspective(90.f, 2.f, 2.f, 200.0f);
        isOrtho = false;
    }

    if (key == GLFW_KEY_W) {
        playerTank.setMovingState(false, FORWARD);
    }

    if (key == GLFW_KEY_S) {
        playerTank.setMovingState(false, BACKWARD);
    }

    if (key == GLFW_KEY_A) {
        playerTank.setMovingState(false, LEFT);
    }

    if (key == GLFW_KEY_D) {
        playerTank.setMovingState(false, RIGHT);
    }

    if (key == GLFW_KEY_Q) {
		playerTank.setCannonAimingState(false, UP);
	}

    if (key == GLFW_KEY_E) {
		playerTank.setCannonAimingState(false, DOWN);
	}
}

void Tanks3D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (deltaX)
    {
        float turretRotationSpeed = -MOUSE_SENSITIVITY_OX * deltaX;
        float cannonRotationSpeed = -MOUSE_SENSITIVITY_OX * deltaX;

        float turretRotationAngle = playerTank.getTurret()->getRotationAngle();
        float newTurretRotationAngle = turretRotationAngle + turretRotationSpeed;

        playerTank.getTurret()->setRotationAngle(newTurretRotationAngle);
    }
    
    
    // TODO REMOVE WHAT IS AFTER THIS

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(-2 * sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-2 * sensivityOY * deltaX);
        }

    }
}


void Tanks3D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tanks3D::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tanks3D::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tanks3D::OnWindowResize(int width, int height)
{
}
