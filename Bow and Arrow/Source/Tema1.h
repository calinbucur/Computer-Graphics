// Bucur Calin-Andrei
// 332CB

#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include "Object2D.h"

// Structure holding all the info needed for the behaviour of an arrow in flight
typedef struct {
	float speed = 300;
	float slope; // The trajectory
	// Current position
	float fly = 0;
	float flx = 0;
	// The launching point
	float startX = 0;
	float startY = 0;
}Arrow_info;

// Structure holding all the info needed for the behaviour of a baloon in flight
typedef struct {
	// Kinda self-explanatory
	float x;
	float y;
	float speed;
	float size = 1;
	int color;
	int collide = 0;
}Baloon_info;

// Structure holding all the info needed for the behaviour of an shuriken in flight
typedef struct {
	// Kinda self-explanatory
	float x;
	float y;
	float speed;
	float size = 1;
	int collide = 0;
}Shuriken_info;

class Tema1 : public SimpleScene
{	
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		Mesh* Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	// Lots and lots of variables
	protected:
		glm::mat3 modelMatrix;
		glm::ivec2 resolution = window->GetResolution();
		float menuWidth = 50;

		// For the bow
		float bowAngle = 0; // Bow incline
		// Bow position
		float bowX = 50;
		float bowY = 400;
		// Bow size
		float bowScaleX = 3;
		float bowScaleY = 3;
		float bowSpeed = 100; // Bow movement speed
		// Bow movement limits
		float maxBowY = resolution.y - Object2D::bowLength * bowScaleY;
		float minBowY = menuWidth + Object2D::bowLength * bowScaleY;

		// For the arrows
		int maxArrows = 20; // Maximum number of arrows in the scene
		// Arrows size
		float arrowScaleX = 3;
		float arrowScaleY = 3;
		// Arrow head offset from the bowstring
		float arrowOff = Object2D::bowLength * bowScaleX * Object2D::bowWidthOff + 28;
		int launch = 0; // Whether an arrow can be launched
		float slope; // Used for the arrows trajectory
		float lowArrowSpeed = 300; // Minimum arrow speed
		float speed = lowArrowSpeed; // Arrow speed. Grows on mouse hold
		// Points from where an arrow is considered out of the scene and can be reused
		float arrowOutX = 2000;
		float arrowOutY = 2000;
		// Arrow position
		float arrowX = 0;
		float arrowY = 0;
		float maxArrowSpeed = 2000; // Maximum arrow speed
		// Cooldown for firing 
		float time = 0;
		float arrowRespawn = 0.6;

		// For the baloons
		int baloonsSpawn = 50; // Chance for a baloon to spawn
		float lowBaloonSpeed = 50; // Minimum baloon speed
		// Baloon size
		float baloonScaleX = 3;
		float baloonScaleY = 3;
		int maxBaloons = 70; // Maximum number of baloons in the scene
		float baloonOut = 900; // Height where a baloon is considered out of the scene and can be reused 

		// For the shurikens
		int shurikenSpawn = 100; // Chance for a shuriken to spawn
		// Shuriken size
		float shurikenScaleX = 15;
		float shurikenScaleY = 15;
		float lowShurikenSpeed = 70; // Minimum shuriken speed
		float sh_rotate = 0; // Used for shuriken spinning
		int maxShurikens = 100; // Maximum number of shurikens in the scene
		float shurikenOut = -50; // The point where a shuriken is considered out of scene and can be reused
		
		// For the multiple objects in the scene
		std::vector<Arrow_info> arrows; // Holds the info of the arrows
		std::vector<Baloon_info> baloons; // Holds the info of the baloons
		std::vector<Shuriken_info> shurikens; // Holds the info of the shurikens
		std::vector<std::string> numbers; // Holds the info of the numbers used for the score
		
		// For score
		int hp = 3;
		int score = 0;	
};
