#include "lab_m1/tema2/tanks_3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

Tanks3D::Tanks3D() {}


Tanks3D::~Tanks3D() {}


void Tanks3D::Init() {
    Mesh* mesh = nullptr;
    Shader* shader = nullptr;
    isLookingAround = false;
    gameManager = GameManager(meshes);
    playerTank = gameManager.getPlayerTank();
    renderer = Renderer();
    shell = NULL;

    camera = new Implemented::CameraAPI();
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    mesh = new Mesh("field");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
    meshes[mesh->GetMeshID()] = mesh;

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

    mesh = new Mesh("shell");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank components"), "shell.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("horizontal_barracks");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "buildings"), "horizontal_barracks.obj");
    meshes[mesh->GetMeshID()] = mesh;

    mesh = new Mesh("vertical_barracks");
    mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "buildings"), "vertical_barracks.obj");
    meshes[mesh->GetMeshID()] = mesh;

    shader = new Shader("field");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FieldVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FieldFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

    shader = new Shader("barracks");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "BarracksVertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "BarracksFragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;

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

    glm::vec3 tankPosition = gameManager.getPlayerTank()->getPosition();
    glm::vec3 cameraPosition = tankPosition + glm::vec3(0, HEIGHT_ABOVE_TANK, DISTANCE_TO_TANK);
    camera->Set(cameraPosition, tankPosition, glm::vec3(0, 1, 0));

    CreateEnemyTanks();
    CreateBarracks();

    chassisMeshes = {
        {"track", meshes["track"]},
        {"body", meshes["body"]},
    };

    chassisShaders = {
        {"track", shaders["track"]},
        {"body", shaders["body"]},
    };
}

void m1::Tanks3D::CreateBarracks()
{
    for (int i = 0; i < 10; i++) {
        int barrackType = rand() % 2;
        std::string type = barrackType == 0 ? "horizontal_barracks" : "vertical_barracks";
        glm::vec3 barracksPosition = UtilFunctions::GenerateRandomPositionInMap();
        while (gameManager.CheckPositionIsEmpty(barracksPosition, 4.0f, 8.0f) == false) {
            barracksPosition = UtilFunctions::GenerateRandomPositionInMap();
        }

        Barracks* barracks = new Barracks(meshes[type], barracksPosition, type);
        gameManager.AddBarracks(barracks);
    }
}

void m1::Tanks3D::CreateEnemyTanks()
{
    for (int i = 0; i < 7; i++) {
        Chassis enemyChassis = Chassis(glm::vec3(0.7, 0.5, 0.1), glm::vec3(0.7, 0.5, 0.1));
        Cannon enemyCannon = Cannon(meshes["cannon"], glm::vec3(0.3, 0.5f, 0.6f));
        Turret enemyTurret = Turret(meshes["turret"], glm::vec3(0.2, 0.3, 0.7));
        Tank* enemyTank = new Tank(enemyChassis, enemyTurret, enemyCannon, true, glm::vec3(1.3, 0.6, 2.3));
        enemyTank->setPosition(UtilFunctions::GenerateRandomPositionInMap());
        gameManager.AddTank(enemyTank);
    }
}

void Tanks3D::FrameStart()
{
    glClearColor(0.0f, 0.596f, 0.804f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}



void Tanks3D::Update(float deltaTimeSeconds)
{
    window->DisablePointer();

    camera->adjustRotationAngle(playerTank->getChassis()->getRotationAngle());
    camera->setPreviousChassisAngle(playerTank->getChassis()->getRotationAngle());

    renderer.RenderBattlefield("field", meshes["field"], shaders["field"], camera, projectionMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    gameManager.Update(deltaTimeSeconds);

    if (playerTank->isMoving()) {
        playerTank->move(deltaTimeSeconds, gameManager.isGameFinished());

        float storedRotationAngle = camera->getRotationAngle();
        glm::vec3 tankPosition = playerTank->getPosition();
        // Calculate the offset from the tank's position based on the stored rotation angle/
        float x = DISTANCE_TO_TANK * sin(storedRotationAngle);
        float z = DISTANCE_TO_TANK * cos(storedRotationAngle);

        glm::vec3 cameraPosition = tankPosition + glm::vec3(x, HEIGHT_ABOVE_TANK, z);
        glm::vec3 cameraTarget = tankPosition;  // Camera looks at the tank.

        // Set the camera's position and target
        camera->Set(cameraPosition, cameraTarget, glm::vec3(0, 1, 0));
    }

    if (playerTank->isAiming()) {
        playerTank->aim(deltaTimeSeconds);
    }

    renderer.RenderChassis(chassisMeshes, chassisShaders, camera, projectionMatrix, playerTank);
    renderer.RenderTurret("turret", meshes["turret"], shaders["turret"], camera, projectionMatrix, playerTank);
    renderer.RenderCannon("cannon", meshes["cannon"], shaders["cannon"], camera, projectionMatrix, playerTank);

    RenderShells(deltaTimeSeconds);
    RenderEnemyTanks(deltaTimeSeconds);
    RenderBarracks();
}

void m1::Tanks3D::RenderShells(float deltaTimeSeconds) {
    vector<Shell*> playerBullets = gameManager.getPlayerBullets();

    for (int i = 0; i < playerBullets.size(); i++) {
        Shell* shell = playerBullets[i];
        shell->update(deltaTimeSeconds);
        renderer.RenderShell("shell", meshes["shell"], shaders["cannon"], projectionMatrix, shell, deltaTimeSeconds);

        if (shell->shouldDestroy()) {
            gameManager.RemoveBullet(shell, false);
        }
    }

    vector<Shell*> enemyBullets = gameManager.getEnemyBullets();

    for (int i = 0; i < enemyBullets.size(); i++) {
        Shell* shell = enemyBullets[i];
        shell->update(deltaTimeSeconds);
        renderer.RenderShell("shell", meshes["shell"], shaders["cannon"], projectionMatrix, shell, deltaTimeSeconds);

        if (shell->shouldDestroy()) {
            gameManager.RemoveBullet(shell, true);
        }
    }
}

void m1::Tanks3D::RenderBarracks() {
    vector<Barracks*> barracks = gameManager.getBarracksList();

    for (int i = 0; i < barracks.size(); i++) {
        if (barracks[i]->getName() == "horizontal_barracks") {
            renderer.RenderBarracks("horizontal_barracks", meshes["horizontal_barracks"], shaders["barracks"], camera, projectionMatrix, barracks[i]->getPosition());
        } else {
            renderer.RenderBarracks("vertical_barracks", meshes["vertical_barracks"], shaders["barracks"], camera, projectionMatrix, barracks[i]->getPosition());
        }
    }
}

void m1::Tanks3D::RenderEnemyTanks(float deltaTimeSeconds) {
    vector<Tank*> enemyTanks = gameManager.getEnemyTanks();

    for (int i = 0; i < enemyTanks.size(); i++) {
        if (enemyTanks[i]->isMoving()) {
            enemyTanks[i]->move(deltaTimeSeconds, gameManager.isGameFinished());
        }

        enemyTanks[i]->decreaseStateChangeInterval(deltaTimeSeconds);
        enemyTanks[i]->deacreaseCooldown(deltaTimeSeconds);

        if (enemyTanks[i]->isTimeToChangeState()) {
            enemyTanks[i]->generateEnemyMoves(deltaTimeSeconds);
        }

        if (enemyTanks[i]->isTimeToShoot() && !enemyTanks[i]->isDestroyed() && !gameManager.isGameFinished()) {
            Shell* shell = enemyTanks[i]->launchShell(meshes["shell"], false);
            if (shell != nullptr) {
                gameManager.AddBullet(shell, true);
            }
        }

        renderer.RenderChassis(chassisMeshes, chassisShaders, camera, projectionMatrix, enemyTanks[i]);
        renderer.RenderTurret("turret", meshes["turret"], shaders["turret"], camera, projectionMatrix, enemyTanks[i]);
        renderer.RenderCannon("cannon", meshes["cannon"], shaders["cannon"], camera, projectionMatrix, enemyTanks[i]);
    }
}

void Tanks3D::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) {
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void Tanks3D::OnKeyPress(int key, int mods) {
    switch (key) {
        case GLFW_KEY_W:
            playerTank->setMovingState(true, FORWARD);
            break;

        case GLFW_KEY_S:
            playerTank->setMovingState(true, BACKWARD);
            break;

        case GLFW_KEY_A:
            playerTank->setMovingState(true, LEFT);
            break;

        case GLFW_KEY_D:
            playerTank->setMovingState(true, RIGHT);
            break;

        case GLFW_KEY_Q:
            playerTank->setCannonAimingState(true, UP);
            break;

        case GLFW_KEY_E:
            playerTank->setCannonAimingState(true, DOWN);
            break;

        default:
            break;
    }
}


void Tanks3D::OnKeyRelease(int key, int mods) {
    switch (key) {
        case GLFW_KEY_O:
            orthoLeft = -8.0f;
            orthoRight = 8.0f;
            orthoUp = 4.5f;
            orthoDown = -4.5f;
            projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.0f, 200.0f);
            isOrtho = true;
            break;

        case GLFW_KEY_P:
            projectionMatrix = glm::perspective(90.f, 2.f, 2.f, 200.0f);
            isOrtho = false;
            break;

        case GLFW_KEY_W:
            playerTank->setMovingState(false, FORWARD);
            break;

        case GLFW_KEY_S:
            playerTank->setMovingState(false, BACKWARD);
            break;

        case GLFW_KEY_A:
            playerTank->setMovingState(false, LEFT);
            break;

        case GLFW_KEY_D:
            playerTank->setMovingState(false, RIGHT);
            break;

        case GLFW_KEY_Q:
            playerTank->setCannonAimingState(false, UP);
            break;

        case GLFW_KEY_E:
            playerTank->setCannonAimingState(false, DOWN);
            break;

        default:
            break;
    }
}

void Tanks3D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (deltaX && !isLookingAround) {
        float turretRotationSpeed = -MOUSE_SENSITIVITY_OX * deltaX;
        float cannonRotationSpeed = -MOUSE_SENSITIVITY_OX * deltaX;

        float turretRotationAngle = playerTank->getTurret()->getRotationAngle();
        float newTurretRotationAngle = turretRotationAngle + turretRotationSpeed;

        // Reset the angle if it exceeds 360 or -360 degrees
        newTurretRotationAngle = newTurretRotationAngle > 2 * PI ? newTurretRotationAngle - 2 * PI : newTurretRotationAngle;
        newTurretRotationAngle = newTurretRotationAngle < -2 * PI ? newTurretRotationAngle + 2 * PI : newTurretRotationAngle;

        playerTank->getTurret()->setRotationAngle(newTurretRotationAngle);
    }
    
    // Rotate the camera around the tank
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        isLookingAround = true;

        float sensitivityOX = 0.001f;
        float sensitivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            camera->RotateThirdPerson_OY(-2 * sensitivityOY * deltaX);
        } else if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			camera->RotateThirdPerson_OX(-2 * sensitivityOX * deltaY);
			camera->RotateThirdPerson_OY(-2 * sensitivityOY * deltaX);
        }
    }
    else {
        isLookingAround = false;
    }
}


void Tanks3D::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // This is left click, but the in the framework it called right ...
    if (button == GLFW_MOUSE_BUTTON_RIGHT && !gameManager.isGameFinished() && playerTank->isTimeToShoot()) {
        bool isBallistic = false;
        float turretRotationAngle = glm::degrees(playerTank->getTurret()->getRotationAngle());
        float cannonRotationAngle = glm::degrees(playerTank->getCannon()->getRotationAngle());
        
        if (cannonRotationAngle > 0 && turretRotationAngle > -90.0f && turretRotationAngle < 90.0f) {
            isBallistic = true;
        }

		Shell *shell = playerTank->launchShell(meshes["shell"], isBallistic);
        
        if (shell != nullptr) {
			gameManager.AddBullet(shell, false);
		}
	}
}
