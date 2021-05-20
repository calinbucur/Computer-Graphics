// Bucur Calin-Andrei
// 332CB

#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

// Defining the extern variables in Object2D.h
float Object2D::bowLength = 35;
float Object2D::bowWidthOff = 0.8;
float Object2D::shaftLength = 40;
float Object2D::headLength = 4;
float Object2D::baloonLength = 15;
float Object2D::baloonWidthOff = 1.5;
float Object2D::shurikenSize = 2;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{	
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	
	// Create the bow
	Mesh* bow = Object2D::Bow("bow");
	AddMeshToList(bow);

	// Create the arrow
	Mesh* shaft = Object2D::Arrow_shaft("shaft");
	AddMeshToList(shaft);
	Mesh* head = Object2D::Arrow_head("head");
	AddMeshToList(head);

	// Create the red baloon
	Mesh* baloon = Object2D::Baloon("baloon", glm::vec3(1,0,0));
	AddMeshToList(baloon);

	// Create the yellow baloon
	Mesh* baloon1 = Object2D::Baloon("baloon1", glm::vec3(1, 1, 0));
	AddMeshToList(baloon1);

	// Create the baloon string
	Mesh* baloon_str = Object2D::Baloon_string("baloon_str");
	AddMeshToList(baloon_str);

	// Create the shuriken
	Mesh* shuriken = Object2D::Shuriken("shuriken");
	AddMeshToList(shuriken);

	// Create the menu at the bottom
	Mesh* menu = Object2D::Menu("menu", glm::vec3(0.5, 0.5, 0.5));
	AddMeshToList(menu);

	// Create the power bar
	Mesh* power = Object2D::Menu("power", glm::vec3(0, 1, 0));
	AddMeshToList(power);

	// Create the heart for the lives
	Mesh* life = Object2D::Heart("life");
	AddMeshToList(life);

	// Create the digits for the score
	Mesh* zero = Object2D::Zero("zero");
	AddMeshToList(zero);
	Mesh* one = Object2D::One("one");
	AddMeshToList(one);
	Mesh* two = Object2D::Two("two");
	AddMeshToList(two);
	Mesh* three = Object2D::Three("three");
	AddMeshToList(three);
	Mesh* four = Object2D::Four("four");
	AddMeshToList(four);
	Mesh* five = Object2D::Five("five"); //SFANTUL
	AddMeshToList(five);
	Mesh* six = Object2D::Six("six");
	AddMeshToList(six);
	Mesh* seven = Object2D::Seven("seven");
	AddMeshToList(seven);
	Mesh* eight = Object2D::Eight("eight");
	AddMeshToList(eight);
	Mesh* nine = Object2D::Nine("nine");
	AddMeshToList(nine);

	// Initialize the numbers info
	numbers.push_back("zero");
	numbers.push_back("one");
	numbers.push_back("two");
	numbers.push_back("three");
	numbers.push_back("four");
	numbers.push_back("five");
	numbers.push_back("six");
	numbers.push_back("seven");
	numbers.push_back("eight");
	numbers.push_back("nine");

	// Initialize the arrows info
	for (int i = 0; i < maxArrows; i++) {
		Arrow_info x;
		x.speed = lowArrowSpeed;
		x.fly = arrowOutX;
		x.flx = arrowOutY;
		arrows.push_back(x);
	}

	// Initialize the baloons info
	for (int i = 0; i < maxBaloons; i++) {
		Baloon_info x;
		x.y = baloonOut;
		baloons.push_back(x);
	}

	// Initialize the shurikens info
	for (int i = 0; i < maxShurikens; i++) {
		Shuriken_info x;
		x.x = shurikenOut;
		shurikens.push_back(x);
	}
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.23, 0.65, 0.74, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// GAME OVER !!!
	if (hp == 0) {
		// Print the score and exit
		cout << "Score: " << score << "\n";
		exit(1);
	}
	// Display the remaining lives as hearts at the bottom of the screen 
	else if (hp == 3) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x / 2, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x / 2 + 25, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x / 2 - 25, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}
	else if (hp == 2) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x / 2, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x / 2 - 25, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}
	else {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x / 2 - 25, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
	}

	// Display the score at the bottom right
	// Depending on the number of digits
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x - 30, menuWidth / 2);
	modelMatrix *= Transform2D::Scale(15, 15);
	RenderMesh2D(meshes[numbers[score % 10]], shaders["VertexColor"], modelMatrix);
	if (score >= 10) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 30 - 15 - 10, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(15, 15);
		RenderMesh2D(meshes[numbers[score / 10 % 10]], shaders["VertexColor"], modelMatrix);
	}
	if (score >= 100) {
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(resolution.x - 30 - 15 - 10 - 15 - 10, menuWidth / 2);
		modelMatrix *= Transform2D::Scale(15, 15);
		RenderMesh2D(meshes[numbers[score / 100 % 10]], shaders["VertexColor"], modelMatrix);
	}

	// Increasing the difficulty at certain score thresholds
	if (score >= 10) {
		shurikenSpawn = 75;
		baloonsSpawn = 75;
		lowBaloonSpeed = 75;
		lowShurikenSpeed = 90;
	}
	if (score >= 30) {
		shurikenSpawn = 50;
		baloonsSpawn = 100;
		lowBaloonSpeed = 100;
		lowShurikenSpeed = 100;
	}
	if (score >= 50) {
		shurikenSpawn = 50;
		baloonsSpawn = 100;
		lowBaloonSpeed = 150;
		lowShurikenSpeed = 150;
	}
	if (score >= 70) {
		shurikenSpawn = 30;
		baloonsSpawn = 100;
		lowBaloonSpeed = 200;
		lowShurikenSpeed = 200;
	}
	// CANCER
	if (score >= 100) {
		shurikenSpawn = 20;
		baloonsSpawn = 100;
		lowBaloonSpeed = 300;
		lowShurikenSpeed = 700;
	}

	// Dispaly the power bar and the menu
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, menuWidth / 4);
	// The power bar width is directly proportional with the speed of the arrow to be fired
	modelMatrix *= Transform2D::Scale(speed * 0.1 - lowArrowSpeed * 0.1, menuWidth / 2);
	RenderMesh2D(meshes["power"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Scale(resolution.x, menuWidth);
	RenderMesh2D(meshes["menu"], shaders["VertexColor"], modelMatrix);

	// Get the mouse coords
	float xpos, ypos;
	glm::ivec2 coords = window->GetCursorPosition();
	xpos = coords.x;
	ypos = resolution.y - coords.y;

	// Calculate the incline of the bow
	if (ypos > bowY && xpos > bowX) {
		bowAngle = atan((ypos - bowY) / (xpos - bowX));
	}
	else if (ypos < bowY && xpos > bowX) {
		bowAngle = -atan((bowY - ypos) / (xpos - bowX));
	}

	// Display the bow
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(bowX, bowY); // Heigth can be modified by pressing W or S
	modelMatrix *= Transform2D::Rotate(bowAngle); // Can be modified by moving the mouse
	modelMatrix *= Transform2D::Rotate(-3.14 / 2); // Necessary because of the way the bow is designed (horizontal)
	modelMatrix *= Transform2D::Scale(bowScaleX, bowScaleY);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

	// Go through the arrows
	for (int i = 0; i < arrows.size(); i++) {
		// Decompose the speed on the X and Y axis
		arrows[i].fly += sin(atan(arrows[i].slope)) * arrows[i].speed * deltaTimeSeconds;
		arrows[i].flx += cos(atan(arrows[i].slope)) * arrows[i].speed * deltaTimeSeconds;
		// Check if the arrow is in flight and in the scene
		if (!(arrows[i].startX + arrows[i].flx > arrowOutX || arrows[i].startY + arrows[i].fly > arrowOutY || arrows[i].startY + arrows[i].fly < -arrowOutY)) {
			// Display the arrow in flight
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(arrows[i].startX + arrows[i].flx, arrows[i].startY + arrows[i].fly);
			modelMatrix *= Transform2D::Rotate(atan(arrows[i].slope));
			modelMatrix *= Transform2D::Translate(arrowOff, 0); // Allign the arrow with the bow for correct rotation
			modelMatrix *= Transform2D::Scale(arrowScaleX, arrowScaleY);
			RenderMesh2D(meshes["shaft"], shaders["VertexColor"], modelMatrix);
			RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
		}
	}
	
	// Cooldown timer for the firing
	time += deltaTimeSeconds;
	if (time > arrowRespawn) {
		launch = 1;
	}

	// Check if an arrow can be launched
	if(launch == 1) {
		// Display the arrow on the bow at the same angle
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(bowX, bowY);
		modelMatrix *= Transform2D::Rotate(bowAngle);
		modelMatrix *= Transform2D::Translate(arrowOff, 0); // Allign the arrow with the bow for correct rotation
		modelMatrix *= Transform2D::Scale(arrowScaleX, arrowScaleY);
		RenderMesh2D(meshes["shaft"], shaders["VertexColor"], modelMatrix);
		RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
	}

	// The baloons and shurikens spawn randomly
	int spawn = rand() % baloonsSpawn;
	// Randomly decide whether a baloon should spawn
	if (spawn == 1) {
		// Get an available baloon and fill it's info so that it can be spawned
		for (int i = 0; i < baloons.size(); i++) {
			if (baloons[i].y >= baloonOut) {
				baloons[i].y = -50; // Starting point
				baloons[i].size = 1; // Normal size
				baloons[i].collide = 0; // Not collided yet
				// Random position on the X axis
				baloons[i].x = rand() % 1050 + bowX + Object2D::bowLength * Object2D::bowWidthOff * bowScaleX + Object2D::baloonLength * Object2D::baloonWidthOff * baloonScaleX + 10;
				// Random color (higher chance for red)
				baloons[i].color = rand() % 4;
				// Random speed
				baloons[i].speed = rand() % 200 + lowBaloonSpeed;
				break;
			}
		}
	}
	// Go through the baloons
	for (int i = 0; i < baloons.size(); i++) {
		// Check if the baloon is in the scene
		if (baloons[i].y < baloonOut) {
			// Display th baloon
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(baloons[i].x, baloons[i].y);
			modelMatrix *= Transform2D::Rotate(-3.14 / 2); // Necessary because of the way the baloons are created (horizontal)
			// Size depends on whether it has collided with the arrow or not
			modelMatrix *= Transform2D::Scale(baloonScaleX * baloons[i].size, baloonScaleY * baloons[i].size);
			// Decide the color
			if (baloons[i].color == 1) {
				RenderMesh2D(meshes["baloon1"], shaders["VertexColor"], modelMatrix);
				RenderMesh2D(meshes["baloon_str"], shaders["VertexColor"], modelMatrix);
			}
			else {
				RenderMesh2D(meshes["baloon"], shaders["VertexColor"], modelMatrix);
				RenderMesh2D(meshes["baloon_str"], shaders["VertexColor"], modelMatrix);
			}
			// Move it upwards (in the next frame)
			baloons[i].y += baloons[i].speed * deltaTimeSeconds;
			// If it has collided shrink it
			if (baloons[i].collide == 1) {
				if (baloons[i].size > 0)
					baloons[i].size -= 5 * deltaTimeSeconds;
				// Until it disappears
				else if (baloons[i].size < 0) {
					baloons[i].size = 0;
					// Modify the score depending on the color
					if (baloons[i].color == 1) {
						if (score > 0)
							score--;
					}
					else score += 2;
				}
			}
			// Go through the arrows and see if the baloon collides with one
			else for (int j = 0; j < arrows.size(); j++) {
				// Check only for the arrows currently in the scene
				if (!(arrows[j].startX + arrows[j].flx > arrowOutX || arrows[j].startY + arrows[j].fly > arrowOutY || arrows[j].startY + arrows[j].fly < -arrowOutY)) {
					// Get the position of the tip of the arrow
					float tipx = cos(atan(arrows[j].slope)) * (arrowOff + Object2D::headLength * arrowScaleX) + arrows[j].startX + arrows[j].flx;
					float tipy = sin(atan(arrows[j].slope)) * (arrowOff + Object2D::headLength * arrowScaleY) + arrows[j].startY + arrows[j].fly;
					// Collision condition (lots of 7th grade geometry)
					if (sqrt((baloons[i].x - tipx) * (baloons[i].x - tipx) + (baloons[i].y - tipy) * (baloons[i].y - tipy)) < (Object2D::baloonLength + Object2D::baloonLength * Object2D::baloonWidthOff) / 2 * arrowScaleX) {
						baloons[i].collide = 1;
					}
				}
			}
		}
	}

	spawn = rand() % shurikenSpawn;
	// Randomly decide whether a shuriken should spawn
	if (spawn == 1) {
		// Get an available shuriken and fill its info so that it can be displayed in the scene
		for (int i = 0; i < shurikens.size(); i++) {
			if (shurikens[i].x <= shurikenOut) {
				shurikens[i].x = 1300; // Starting point
				// Random height
				shurikens[i].y = rand() % 610 + menuWidth + Object2D::shurikenSize * shurikenScaleX;
				shurikens[i].size = 1; // Normal size
				shurikens[i].collide = 0; // Not collided yet
				shurikens[i].speed = rand() % 200 + lowShurikenSpeed; // Random speed
				break;
			}
		}
	}
	// Go through the shurikens
	for (int i = 0; i < shurikens.size(); i++) {
		// Check if the shuriken is in the scene
		if (shurikens[i].x > shurikenOut) {
			// Prepare the model matrix
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(shurikens[i].x, shurikens[i].y);
			modelMatrix *= Transform2D::Rotate(sh_rotate); // The spinning
			// Size depends on whether it has collided with the bow or an arrow
			modelMatrix *= Transform2D::Scale(shurikenScaleX*shurikens[i].size, shurikenScaleY*shurikens[i].size);
			// Some more 7th grade geometry
			float euclid = sqrt((shurikens[i].x - bowX) * (shurikens[i].x - bowX) + (shurikens[i].y - bowY) * (shurikens[i].y - bowY));
			float unghi = atan((shurikens[i].y - bowY) / (shurikens[i].x - bowX));
			// Check for collision with the bow
			if (euclid < Object2D::bowLength * Object2D::bowWidthOff * bowScaleX + Object2D::shurikenSize * shurikenScaleX) {
				if (!(((abs(bowAngle) + abs(unghi) > 3.14 / 2) && (bowAngle * unghi < 0)) || (((bowAngle > 0 && shurikens[i].y < bowY) || (bowAngle < 0 && shurikens[i].y > bowY)) && (shurikens[i].x < bowX)))) {
					// Shrink the shuriken
					if (shurikens[i].size > 0)
						shurikens[i].size -= 100 * deltaTimeSeconds;
					// Until it disappears
					else if (shurikens[i].size < 0) {
						shurikens[i].size = 0;
						// Just lost a life :(
						hp--;
					}
				}
			}
			// If it has collided with an arrow shrink it
			if (shurikens[i].collide == 1) {
				if (shurikens[i].size > 0)
					shurikens[i].size -= 5 * deltaTimeSeconds;
				// Until it's gone
				else if (shurikens[i].size < 0) {
					shurikens[i].size = 0;
				}
			}
			// Go through the arrows and check if the shuriken collides with one
			else for (int j = 0; j < arrows.size(); j++) {
				// Only check the arrows in the scene
				if (!(arrows[j].startX + arrows[j].flx > arrowOutX || arrows[j].startY + arrows[j].fly > arrowOutY || arrows[j].startY + arrows[j].fly < -arrowOutY)) {
					// Get the position of the tip of the arrow
					float tipx = cos(atan(arrows[j].slope)) * (arrowOff + Object2D::headLength * arrowScaleX) + arrows[j].startX + arrows[j].flx;
					float tipy = sin(atan(arrows[j].slope)) * (arrowOff + Object2D::headLength * arrowScaleY) + arrows[j].startY + arrows[j].fly;
					// Collision condition
					if (sqrt((shurikens[i].x - tipx) * (shurikens[i].x - tipx) + (shurikens[i].y - tipy) * (shurikens[i].y - tipy)) < shurikenScaleX * Object2D::shurikenSize) {
						shurikens[i].collide = 1;
						// Increase the score
						score++;
					}
				}
			}
			// Display the shuriken
			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
			// Move it towards the bow
			shurikens[i].x -= shurikens[i].speed * deltaTimeSeconds;
		}
	}
	// Keep spinnin' it
	sh_rotate += 10 * deltaTimeSeconds;
	if (sh_rotate > 6.28) {
		sh_rotate = 0;
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// Move the bow up and down
	if (window->KeyHold(GLFW_KEY_W)) {
		if (bowY < maxBowY) {
			bowY += bowSpeed * deltaTime;
		}
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		if (bowY > minBowY) {
			bowY -= bowSpeed * deltaTime;
		}
	}
	// If an arrow is ready to be launched
	// Increase it's speed up to a certain ceiling
	// As long as left click is held
	if (launch == 1) {
		if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
			if (speed < maxArrowSpeed)
				speed += 30;
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{

}

void Tema1::OnKeyRelease(int key, int mods)
{

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{	
	// If an arrow is ready to be launched
	if (launch == 1) {
		if (button == GLFW_MOUSE_BUTTON_2) {
			// Get mouse coords
			float xpos = mouseX;
			float ypos = resolution.y - mouseY;
			// The bow can't fire to the left
			if (xpos > bowX) {
				slope = (ypos - bowY) / (xpos - bowX); // The slope of the trajectory
				// Get an available arrow and fill it's info so that it can be fired
				for (int i = 0; i < arrows.size(); i++) {
					if (bowX + arrows[i].flx > arrowOutX || bowY + arrows[i].fly > arrowOutY || bowY + arrows[i].fly < -arrowOutY) {
						// Starts from the bow (the begining of the trajectory)
						arrows[i].fly = 0;
						arrows[i].flx = 0;
						arrows[i].speed = speed; // Its speed is the speed accumulated by holding the mouse
						arrows[i].slope = slope; // The trajectory
						// The starting point
						arrows[i].startX = bowX;
						arrows[i].startY = bowY;
						break;
					}
				}
				speed = lowArrowSpeed; // Reset the speed to the floor value
				launch = 0; // An arrow can no longer be fired for the time being
				time = 0; // Reset the cooldown timer
			}
		}
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
