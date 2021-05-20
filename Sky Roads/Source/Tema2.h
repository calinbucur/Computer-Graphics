#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		// Camera and projection matrix stuff
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		float zNear = 0.01f;
		float zFar = 100;

		// Player position
		float ballX = 0;
		float ballY = 0.5;

		// Umm, self-explanatory
		bool firstPerson = false;

		// Speed stuff
		float maxSpeed = 60;
		float minSpeed = 20;
		float speed = 0;
		float last;

		// Jumping stuff
		bool nojump = false;
		int jump = 1;
		float h = 0.5;
		float l = 4;

		// Flag for collisions, duuuh
		int collision = 1;

		// Fuel stuff
		float maxFuel = 40;
		float fuelPenalty = 10;
		float fuel = maxFuel;

		// Power-ups flags and timers and stuff
		bool kill = false;
		bool super = false;
		bool orange_power = false;
		bool yellow_power = false;
		bool green_power = false;
		float powerTime;
		float time = 0;

		// Platforms stuff
		int maxPlat = 15;
		float initZ = -50;
		float initLength = 110;
		int minLength = 10;
		int maxLength = 50;
		int minGap = 5;
		int maxGap = 10;

		// COLORS
		glm::vec3 blue = glm::vec3(0.11f, 0.56f, 1);
		glm::vec3 red = glm::vec3(1, 0, 0);
		glm::vec3 orange = glm::vec3(1, 0.64, 0);
		glm::vec3 yellow = glm::vec3(1, 1, 0);
		glm::vec3 green = glm::vec3(0, 1, 0);
		glm::vec3 purple = glm::vec3(1, 0, 1);
		glm::vec3 ballColor = glm::vec3(1, 0.4f, 0.3f);
};
