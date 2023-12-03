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


Tanks3D::Tanks3D()
{
}


Tanks3D::~Tanks3D()
{
}


void Tanks3D::Init()
{
    renderCameraTarget = false;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    {
        Mesh* mesh = new Mesh("track");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "trackv2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("turret");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "turretv2.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
    
    {
		Mesh* mesh = new Mesh("body");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "bodyv2.obj");
		meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("cannon");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "cannonv2.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    	// Create a shader program for drawing face polygon with the color of the normal
    {
		Shader *shader = new Shader("Camouflage");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TankVertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TankFragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

    {
        Shader* shader = new Shader("TankVertexNormal");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "CamouflageVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "CamouflageFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
		Shader* shader = new Shader("TurretShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TurretVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "TurretFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
	}

    {
        Shader* shader = new Shader("CannonFragmentShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "CannonVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "CannonFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    //// TODO(student): After you implement the changing of the projection
    //// parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

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

    // Set color to white before rendering each component
    glm::vec3 whiteColor = glm::vec3(1.0f, 1.0f, 1.0f);

    // Render track
    {
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderMesh(meshes["track"], shaders["TankVertexNormal"], modelMatrix);
	}

	// Render turret    
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderMesh(meshes["turret"], shaders["TurretShader"], modelMatrix);
	}

    {
        glm::mat4 modelMatrix = glm::mat4(1);
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.22f, -0.05, 0.05));
		RenderMesh(meshes["body"], shaders["Camouflage"], modelMatrix);
    }

    {
		glm::mat4 modelMatrix = glm::mat4(1);
		RenderMesh(meshes["cannon"], shaders["CannonFragmentShader"], modelMatrix);
	}
}


void Tanks3D::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tanks3D::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */




void Tanks3D::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->TranslateForward(deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->TranslateForward(-deltaTime * cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
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
}


void Tanks3D::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
            // use the sensitivity variables for setting up the rotation speed
            camera->RotateFirstPerson_OX(-2 * sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-2 * sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
            // use the sensitivity variables for setting up the rotation speed
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
