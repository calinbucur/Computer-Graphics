#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Structure holding a platform's info
typedef struct {
	float z; // Location
	float length;
	float gap; // Distance between this platform and the next
	glm::vec3 color;
}Platform;

vector<Platform> mid;

vector<Platform> lft;

vector<Platform> rgt;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

	// Load the necessary objects
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Initialize a vector for each column
	// Holding each platform's info
	for (int i = 0; i < maxPlat; i++) {
		Platform x;
		x.gap = 0;
		x.length = 0;
		x.z = 10;
		mid.push_back(x);
	}
	// Set the info for the first platform
	// The one the player will spawn on
	mid[0].z = initZ;
	mid[0].length = initLength;
	mid[0].gap = 5;
	mid[0].color = blue;

	for (int i = 0; i < maxPlat; i++) {
		Platform x;
		x.gap = 0;
		x.length = 0;
		x.z = 10;
		lft.push_back(x);
	}
	lft[0].z = initZ;
	lft[0].length = initLength;
	lft[0].gap = 5;
	lft[0].color = blue;

	for (int i = 0; i < maxPlat; i++) {
		Platform x;
		x.gap = 0;
		x.length = 0;
		x.z = 10;
		rgt.push_back(x);
	}
	rgt[0].z = initZ;
	rgt[0].length = initLength;
	rgt[0].gap = 5;
	rgt[0].color = blue;

	// Generate the projection matrix
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, zNear, zFar);

	// Add the necessary shaders
	{
		// Used for platforms and the player
		Shader* shader = new Shader("MyShader");
		shader->AddShader("Source/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		// Used for the user interface
		Shader* shader = new Shader("HUDShader");
		shader->AddShader("Source/Shaders/HUDVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Shaders/HUDFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		// Used for the special effects of power-ups
		Shader* shader = new Shader("SpecialShader");
		shader->AddShader("Source/Shaders/SpecialVertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Shaders/SpecialFragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	// If the player has fallen
	// Or touched a red platform
	// Or has run out of fuel
	if (ballY < -10 || kill || fuel <= 0) {
		// GAME OVER!!! :(
		exit(1);
	}

	// Set the camera mode
	if (firstPerson) {
		camera->Set(glm::vec3(ballX, ballY + 1, 1), glm::vec3(ballX, ballY + 1, -1), glm::vec3(0, 1, 0));
	}

	// Check if a new platform needs to be spawned
	int midok = 0;
	int rgtok = 0;
	int lftok = 0;
	for (int i = 0; i < maxPlat; i++) {
		// If a platform is currently at the spawn point, it's ok 
		if ((mid[i].z + mid[i].length / 2 >= -zFar) && (mid[i].z - mid[i].length / 2 - mid[i].gap < -zFar)) {
			midok = 1;
		}
		if ((lft[i].z + lft[i].length / 2 >= -zFar) && (lft[i].z - lft[i].length / 2 - lft[i].gap < -zFar)) {
			lftok = 1;
		}
		if ((rgt[i].z + rgt[i].length / 2 >= -zFar) && (rgt[i].z - rgt[i].length / 2 - rgt[i].gap < -zFar)) {
			rgtok = 1;
		}
	}

	// A new platform needs to be spawned on the middle row
	if (midok == 0) {
		for (int i = 0; i < maxPlat; i++) {
			if (mid[i].z - mid[i].length / 2 > zNear + 3.5f) {
				// Randomly generate platform length, gap and color
				mid[i].length = rand() % (maxLength - minLength) + minLength;
				mid[i].z = -zFar - mid[i].length / 2;
				mid[i].gap = rand() % (maxGap - minGap) + minGap;
				int color_rand = rand() % 20;
				if (color_rand == 0) {
					mid[i].color = red;
				}
				else if (color_rand == 1) {
					mid[i].color = orange;
				}
				else if (color_rand == 2 || color_rand == 3) {
					mid[i].color = green;
				}
				else if (color_rand == 4) {
					mid[i].color = yellow;
				}
				else {
					mid[i].color = blue;
				}
				break;
			}
		}
	}
	// Same for left
	if (lftok == 0) {
		for (int i = 0; i < maxPlat; i++) {
			if (lft[i].z - lft[i].length / 2 > zNear + 3.5f) {
				// Randomly generate platform length, gap and color
				lft[i].length = rand() % (maxLength - minLength) + minLength;
				lft[i].z = -zFar - lft[i].length / 2;
				lft[i].gap = rand() % (maxGap - minGap) + minGap;
				int color_rand = rand() % 20;
				if (color_rand == 0) {
					lft[i].color = red;
				}
				else if (color_rand == 1) {
					lft[i].color = orange;
				}
				else if (color_rand == 2 || color_rand == 3) {
					lft[i].color = green;
				}
				else if (color_rand == 4) {
					lft[i].color = yellow;
				}
				else {
					lft[i].color = blue;
				}
				break;
			}
		}
	}
	// Same for right
	if (rgtok == 0) {
		for (int i = 0; i < maxPlat; i++) {
			if (rgt[i].z - rgt[i].length / 2 > zNear + 3.5f) {
				// Randomly generate platform length, gap and color
				rgt[i].length = rand() % (maxLength - minLength) + minLength;
				rgt[i].z = -zFar - rgt[i].length / 2;
				rgt[i].gap = rand() % (maxGap - minGap) + minGap;
				int color_rand = rand() % 20;
				if (color_rand == 0) {
					rgt[i].color = red;
				}
				else if (color_rand == 1) {
					rgt[i].color = orange;
				}
				else if (color_rand == 2 || color_rand == 3) {
					rgt[i].color = green;
				}
				else if (color_rand == 4) {
					rgt[i].color = yellow;
				}
				else {
					rgt[i].color = blue;
				}
				break;
			}
		}
	}

	// Render the platforms in the scene
	for (int i = 0; i < maxPlat; i++) {
		// For every column
		// Check if the platform is still in the scene
		// Render only if it is
		if (mid[i].z - mid[i].length / 2 < zNear + 3.5f) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, mid[i].z));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 0.08f, mid[i].length));
			RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, mid[i].color);
		}
		if (lft[i].z - lft[i].length / 2 < zNear + 3.5f) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, 0, lft[i].z));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 0.08f, lft[i].length));
			RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, lft[i].color);
		}
		if (rgt[i].z - rgt[i].length / 2 < zNear + 3.5f) {
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0, rgt[i].z));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5, 0.08f, rgt[i].length));
			RenderSimpleMesh(meshes["box"], shaders["MyShader"], modelMatrix, rgt[i].color);
		}
	}

	{	
		// If the game has started, slowly deplete the fuel
		if (speed > 0) {
			fuel -= deltaTimeSeconds;
		}
		// Render a green bar using the HUD shader
		// Scale it proportionally to the fuel left
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7, 0.8, -1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(fuel / 100, 0.12, 1));
		RenderSimpleMesh(meshes["box"], shaders["HUDShader"], modelMatrix, glm::vec3(0, 1, 0));
	}

	{
		// Render a red bar behind the green one
		// Represents the max fuel
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.7, 0.8, -1));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.4, 0.12, 1));
		RenderSimpleMesh(meshes["box"], shaders["HUDShader"], modelMatrix, glm::vec3(1, 0, 0));
	}

	// Each row of platforms moves towards the player with a certain speed
	for (int i = 0; i < maxPlat; i++) {
		if (mid[i].z - mid[i].length < zNear + 3.5f) {
			mid[i].z += speed * deltaTimeSeconds;
		}
		if (lft[i].z - lft[i].length < zNear + 3.5f) {
			lft[i].z += speed * deltaTimeSeconds;
		}
		if (rgt[i].z - rgt[i].length < zNear + 3.5f) {
			rgt[i].z += speed * deltaTimeSeconds;
		}
	}

	// If the player was on a platform
	if (collision == 1) {
		// Go thorugh all the platforms and perform some checks
		for (int i = 0; i < maxPlat; i++) {
			// If the ball is at platform level
			if (ballY - 0.5f <= 0.4f) {
				// If it's on the middle row
				if (ballX <= 0.75f && ballX >= -0.75f) {
					// If it's in a gap set the collision flag to 0
					// This means the ball will fall
					if ((mid[i].z - mid[i].length / 2 > 0) && (mid[i].z - mid[i].length / 2 - mid[i].gap < 0)) {
						collision = 0;
						break;
					}
					// If the ball is still on a platform act accordingly
					// This condition is true only for the platform that the player is touching
					else if (mid[i].z + mid[i].length / 2 > 0 && mid[i].z - mid[i].length / 2 < 0){
						// If it's red activate the kill flag and game over
						if (mid[i].color == red) {
							kill = true;
						}
						// If it's orange
						if (mid[i].color == orange) {
							last = speed; //Remember the speed
							time = Engine::GetElapsedTime();
							jump = 0; // jump
							super = true; // enable this flag that will trigger a high speed launch for a short time
							orange_power = true; //enable this flag for shader effects
							powerTime = Engine::GetElapsedTime(); //used for shader effects duration
						}
						// If it's green reset the fuel back to full
						if (mid[i].color == green) {
							fuel = maxFuel;
							green_power = true;
							powerTime = Engine::GetElapsedTime();
						}
						// If it's yellow lose some fuel
						if (mid[i].color == yellow) {
							yellow_power = true;
							fuel -= fuelPenalty;
							powerTime = Engine::GetElapsedTime();
						}
						// Always make the platform the player is touching purple
						mid[i].color = purple;
					}
				}
				// Same for the right column
				else if (ballX <= 3.75 && ballX >= 2.25) {
					if ((rgt[i].z - rgt[i].length / 2 > 0) && (rgt[i].z - rgt[i].length / 2 - rgt[i].gap < 0)) {
						collision = 0;
						break;
					}
					else if (rgt[i].z + rgt[i].length / 2 > 0 && rgt[i].z - rgt[i].length / 2 < 0) {
						if (rgt[i].color == red) {
							kill = true;
						}
						if (rgt[i].color == orange) {
							orange_power = true;
							last = speed;
							time = Engine::GetElapsedTime();
							jump = 0;
							super = true;
							powerTime = Engine::GetElapsedTime();
						}
						if (rgt[i].color == green) {
							green_power = true;
							fuel = maxFuel;
							powerTime = Engine::GetElapsedTime();
						}
						if (rgt[i].color == yellow) {
							yellow_power = true;
							fuel -= fuelPenalty;
							powerTime = Engine::GetElapsedTime();
						}
						rgt[i].color = purple;
					}
				}
				// Same for the left column
				else if (ballX <= -2.25 && ballX >= -3.75) {
					if ((lft[i].z - lft[i].length / 2 > 0) && (lft[i].z - lft[i].length / 2 - lft[i].gap < 0)) {
						collision = 0;
						break;
					}
					else if (lft[i].z + lft[i].length / 2 > 0 && lft[i].z - lft[i].length / 2 < 0) {
						if (lft[i].color == red) {
							kill = true;
						}
						if (lft[i].color == orange) {
							last = speed;
							time = Engine::GetElapsedTime();
							jump = 0;
							super = true;
							orange_power = true;
							powerTime = Engine::GetElapsedTime();
						}
						if (lft[i].color == green) {
							fuel = maxFuel;
							green_power = true;
							powerTime = Engine::GetElapsedTime();
						}
						if (lft[i].color == yellow) {
							fuel -= fuelPenalty;
							yellow_power = true;
							powerTime = Engine::GetElapsedTime();
						}
						lft[i].color = purple;
					}
				}
				// If it's between the plaforms fall
				else {
					collision = 0;
				}
			}
		}
	}
	// Launched by the orange platform
	if (super) {
		jump = 0; // Launched in the air
		if (Engine::GetElapsedTime() - time < 0.5) { // For a short time
			collision = 1;
			speed = 100; // At high speed
		}
		// When it expires
		else {
			speed = last; // Return to the previous speed
			super = false;
		}
	}

	// If the player is falling
	if (collision == 0) {
		nojump = true; // Disable jumping
		ballY -= 5 * deltaTimeSeconds; // Player is falling
		// Check for each plaform
		for (int i = 0; i < maxPlat; i++) {
			// Fancy collision that checks if while falling the player touches the edge of a platform
			// If so, it stops the player. It just starts falling vertically
			// Check this for each column
			if (ballX <= 0.75f && ballX >= -0.75f) {
				if ((mid[i].z + mid[i].length / 2 > -0.5f && mid[i].z - mid[i].length / 2 < -0.5f && ballY > -0.5)) {
					speed = 0;
				}
			}
			if (ballX <= 3.75f && ballX >= 2.25f) {
				if ((rgt[i].z + rgt[i].length / 2 > -0.5f && rgt[i].z - rgt[i].length / 2 < -0.5f && ballY > -0.5)) {
					speed = 0;
				}
			}
			if (ballX <= -2.25f && ballX >= -3.75f) {
				if ((lft[i].z + lft[i].length / 2 > -0.5f && lft[i].z - lft[i].length / 2 < -0.5f && ballY > -0.5)) {
					speed = 0;
				}
			}
			// And for falling between them
			if (ballX <= -1.75f && ballX >= -2.25 && ballY > -0.5) {
				ballX = -1.75f;
			}
			if (ballX <= -0.75f && ballX >= -1.25 && ballY > -0.5) {
				ballX = -1.25f;
			}
			if (ballX <= 1.25f && ballX >= 0.75 && ballY > -0.5) {
				ballX = 1.25f;
			}
			if (ballX <= 2.25f && ballX >= 1.75 && ballY > -0.5) {
				ballX = 1.75f;
			}
		}
	}
	
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		// Get the ball position
		modelMatrix = glm::translate(modelMatrix, glm::vec3(ballX, ballY, 0));
		// Only render if the camera is in third person mode
		if (!firstPerson) {
			// If a power-up was recently claimed render the player with some fancy animations using the special shader for a short time
			if (orange_power) {
				if (Engine::GetElapsedTime() - powerTime < 0.5)
					RenderSimpleMesh(meshes["sphere"], shaders["SpecialShader"], modelMatrix, orange);
				else
					orange_power = false;
			}
			else if (yellow_power) {
				if (Engine::GetElapsedTime() - powerTime < 0.5)
					RenderSimpleMesh(meshes["sphere"], shaders["SpecialShader"], modelMatrix, yellow);
				else
					yellow_power = false;
			}
			else if (green_power) {
				if (Engine::GetElapsedTime() - powerTime < 0.5)
					RenderSimpleMesh(meshes["sphere"], shaders["SpecialShader"], modelMatrix,green);
				else
					green_power = false;
			}
			// Else just render it normally
			else RenderSimpleMesh(meshes["sphere"], shaders["MyShader"], modelMatrix, ballColor);
		}
	}
	
	// If jumping is enabled
	if (!nojump) {
		// And active
		if (jump == 0) {
			// Jump up to a certain height
			if (h < 2) {
				ballY += 5 * deltaTimeSeconds;
				h = ballY;
			}
			// Then fall back down
			else if (l > 0.5) {
				ballY -= 5 * deltaTimeSeconds;
				l = ballY;
			}
			else {
				jump = 1;
				h = 0.5;
				l = 4;
			};
		}
	}
}

void Tema2::FrameEnd()
{

}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4 & modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();

	// Bind the current time
	GLint loc_time = glGetUniformLocation(shader->program, "time");
	glUniform1f(loc_time, Engine::GetElapsedTime());

	// Bind the color
	GLint loc_color = glGetUniformLocation(shader->program, "color");
	glUniform3fv(loc_color, 1, glm::value_ptr(color));

	// Bind model matrix
	GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
	glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind view matrix
	int loc_view_matrix = glGetUniformLocation(shader->program, "View");
	glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

	// Bind projection matrix
	int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
	glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Draw the object
	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float acc = 70; // Acceleration

	// Move the player left
	if (window->KeyHold(GLFW_KEY_A)) {
		ballX -= 7 * deltaTime;
	}

	// MOve the player right
	if (window->KeyHold(GLFW_KEY_D)) {
		ballX += 7 * deltaTime;
	}
	
	// Increase the speed up to a certain level
	if (window->KeyHold(GLFW_KEY_W)) {
		if (Engine::GetElapsedTime() > 2) {
			if (speed < maxSpeed) {
				speed += acc * deltaTime;
			}
		}
	}

	// Decrease the speed up to a certain level
	if (window->KeyHold(GLFW_KEY_S)) {
		if (speed > minSpeed) {
			speed -= acc * deltaTime;
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// Activate the jump
	if (key == GLFW_KEY_SPACE) {
		if (jump == 1)
			jump = 0;
	}

	// Switch the camera mode
	if (key == GLFW_KEY_C) {
		if (!firstPerson) {
			firstPerson = true;
		}
		else {
			firstPerson = false;
			camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		}
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
