// Bucur Calin-Andrei
// 332CB

#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>


namespace Object2D
{
	// Bow size
	extern float bowLength;
	extern float bowWidthOff;
	// Arrow size
	extern float shaftLength;
	extern float headLength;
	// Baloon size
	extern float baloonLength;
	extern float baloonWidthOff;
	// Shuriken size
	extern float shurikenSize;

	Mesh* Bow(std::string name);
	Mesh* Arrow_shaft(std::string name);
	Mesh* Arrow_head(std::string name);
	Mesh* Baloon(std::string name, glm::vec3 color);
	Mesh* Baloon_string(std::string name);
	Mesh* Shuriken(std::string name);
	Mesh* Menu(std::string name, glm::vec3 color);
	Mesh* Heart(std::string name);
	Mesh* One(std::string name);
	Mesh* Two(std::string name);
	Mesh* Three(std::string name);
	Mesh* Four(std::string name);
	Mesh* Five(std::string name); //SFANTUL
	Mesh* Six(std::string name);
	Mesh* Seven(std::string name);
	Mesh* Eight(std::string name);
	Mesh* Nine(std::string name);
	Mesh* Zero(std::string name);
}

