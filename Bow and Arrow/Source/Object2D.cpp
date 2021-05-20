// Bucur Calin-Andrei
// 332CB

#include "Object2D.h"

#include <Core/Engine.h>

// This file contains all the object building functions

// Builds the bow
Mesh* Object2D::Bow(std::string name)
{	
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(6);
	// Big radius of the ellipse
	float a = bowLength;
	// Small radius of the ellipse
	float b = a * bowWidthOff;
	glm::vec3 color = glm::vec3(0.5, 0.2, 0);

	std::vector<VertexFormat> vertices;

	// Creating vertices on the bow using the ellipse ecuation
	for (float t = 0; t <= 3.14; t += 0.01) {
		vertices.push_back(VertexFormat(glm::vec3(a*cos(t), b*sin(t), 0), color));
	}

	// These 2 vertices will be used for the black bowstring
	vertices.push_back(VertexFormat(glm::vec3(-a,0,0), glm::vec3(0, 0, 0)));
	vertices.push_back(VertexFormat(glm::vec3(a, 0, 0), glm::vec3(0, 0, 0)));

	Mesh* bow = new Mesh(name);
	std::vector<unsigned short> indices;

	// Creating the indices
	indices.push_back(0);
	for (int i = 1; i < 315; i++) {
		indices.push_back(i);
		indices.push_back(i);
	}
	indices.push_back(315);
	indices.push_back(315);
	indices.push_back(316);

	// Uses the lines primitive
	bow->SetDrawMode(GL_LINES);

	bow->InitFromData(vertices, indices);
	return bow;
}

// The arrow shaft and head are different objects
// They are built in such a way that they will look as a single object if I apply the same transformations

// Builds the shaft of the arrow
Mesh* Object2D::Arrow_shaft(std::string name) {
	float length = shaftLength;

	glm::vec3 color = glm::vec3(0.5, 0.2, 0);

	Mesh* arrow = new Mesh(name);

	std::vector<VertexFormat> vertices1 = {
		VertexFormat(glm::vec3(-length, 0, 0), color),
		VertexFormat(glm::vec3(0, 0, 0), color),
	};

	std::vector<unsigned short> indices1 = {
		0, 1
	};

	// Using line primitive
	arrow->SetDrawMode(GL_LINES);
	arrow->InitFromData(vertices1, indices1);
	return arrow;
}

// Builds the arrow head
Mesh* Object2D::Arrow_head(std::string name) {
	float tip = headLength;

	glm::vec3 color = glm::vec3(0.5, 0.2, 0);
	glm::vec3 tip_color = glm::vec3(1, 0, 0);

	std::vector<VertexFormat> vertices = {

		VertexFormat(glm::vec3(0, 3, 0), tip_color),
		VertexFormat(glm::vec3(0, -3, 0), tip_color),
		VertexFormat(glm::vec3(tip, 0, 0), tip_color),
	};
	std::vector<unsigned short> indices = {
		0, 1, 2
	};

	Mesh* arrow = new Mesh(name);
	//Uses triangle primitive
	arrow->InitFromData(vertices, indices);

	return arrow;
}

// The baloon and string are different objects
// They are built in such a way that they will look as a single object if I apply the same transformations

Mesh* Object2D::Baloon(std::string name, glm::vec3 color) {
	float a = baloonLength;
	float b = a/baloonWidthOff;

	glEnable(GL_LINE_SMOOTH);

	std::vector<VertexFormat> vertices;

	// Creates a vertex at the center of the ellipse
	// The central vertex is white for that "shining" look
	vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1,1,1)));
	// Creates pairs of vertices along the baloon
	for (float t = 0; t <= 6.28; t += 0.01) {
		vertices.push_back(VertexFormat(glm::vec3(a * cos(t), b * sin(t), 0), color));
	}

	std::vector<unsigned short> indices;

	indices.push_back(1);
	indices.push_back(0);
	for (int i = 1; i <= 628; i++) {
		indices.push_back(i);
		indices.push_back(0);
		indices.push_back(i);
	}
	indices.push_back(1);

	Mesh* baloon = new Mesh(name);
	// Using the triangle primitive
	baloon->InitFromData(vertices, indices);
	return baloon;
}

// Builds the baloon string
Mesh* Object2D::Baloon_string(std::string name) {
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(3);
	// Kinda hard-coded
	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(15, 0, 0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(18, 3, 0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(21, 0, 0), glm::vec3(0,0,0)),
		VertexFormat(glm::vec3(24, 3, 0), glm::vec3(0,0,0)),
	};

	std::vector<unsigned short> indices = {
		0, 1, 2, 3
	};
	
	Mesh* baloon_string = new Mesh(name);
	//Uses line strip primitive
	baloon_string->SetDrawMode(GL_LINE_STRIP);
	baloon_string->InitFromData(vertices, indices);

	return baloon_string;
}

// Builds the shuriken
Mesh* Object2D::Shuriken(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);

	// The hypothenuse of the four triangles
	float x = shurikenSize;

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(x/2, -x/2, 0), color),
		VertexFormat(glm::vec3(x, 0, 0), color),
		VertexFormat(glm::vec3(x/2, x/2, 0), color),
		VertexFormat(glm::vec3(0, x, 0), color),
		VertexFormat(glm::vec3(-x/2, x/2, 0), color),
		VertexFormat(glm::vec3(-x, 0, 0), color),
		VertexFormat(glm::vec3(-x/2, -x/2, 0), color),
		VertexFormat(glm::vec3(0, -x, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8
	};

	Mesh* shuriken = new Mesh(name);
	// Uses the triangles primitive
	shuriken->InitFromData(vertices, indices);

	return shuriken;
}


// Builds a little rectangle to be scaled and used for the menu and power bar
Mesh* Object2D::Menu(std::string name, glm::vec3 color) {
	glEnable(GL_LINE_SMOOTH);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1, 0, 0), color),
		VertexFormat(glm::vec3(1, 1, 0), color),
		VertexFormat(glm::vec3(0, 1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 2,
		2, 3, 0,
	};

	Mesh* menu = new Mesh(name);
	// Uses triangles primitive
	menu->InitFromData(vertices, indices);

	return menu;
}

// Builds a lovely heart representing a life
Mesh* Object2D::Heart(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(1, 0, 0);
	
	// Kinda hardcoded too :))
	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-2, 0, 0), color),
		VertexFormat(glm::vec3(2, 0, 0), color),
		VertexFormat(glm::vec3(0, -2, 0), color),
		VertexFormat(glm::vec3(-1, 2, 0), color),
		VertexFormat(glm::vec3(1, 2, 0), color),
		VertexFormat(glm::vec3(-2, 1, 0), color),
		VertexFormat(glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(2, 1, 0), color),
	};

	std::vector<unsigned short> indices = {
		1, 0, 2,
		6, 3, 5,
		7, 4, 6,
		1, 5, 0,
		7, 5, 1
	};

	Mesh* heart = new Mesh(name);
	// Uses triangles primitive
	heart->InitFromData(vertices, indices);

	return heart;
}

// The following meshes are digits used for the score
// Lots of writing, lots of copy-paste, lots of hard-coding
// Built like a seven segment display using the line strip primitive

Mesh* Object2D::Zero(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 3, 5, 4, 2, 0
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::One(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		1, 3, 5,
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Two(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 3, 2, 4, 5,
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Three(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 3, 2, 3, 5, 4
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Four(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 2, 3, 1, 5
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Five(std::string name) { //SFANTUL
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		1, 0, 2, 3, 5, 4
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Six(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		1, 0, 2, 4, 5, 3, 2
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Seven(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 3, 5
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Eight(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		0, 1, 3, 5, 4, 2, 3, 2, 0
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}

Mesh* Object2D::Nine(std::string name) {
	glEnable(GL_LINE_SMOOTH);

	glm::vec3 color = glm::vec3(0, 0, 0);

	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-0.5, 1, 0), color),
		VertexFormat(glm::vec3(0.5, 1, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),
		VertexFormat(glm::vec3(-0.5, -1, 0), color),
		VertexFormat(glm::vec3(0.5, -1, 0), color),
	};

	std::vector<unsigned short> indices = {
		3, 2, 0, 1, 5, 4
	};

	Mesh* num = new Mesh(name);
	num->SetDrawMode(GL_LINE_STRIP);

	num->InitFromData(vertices, indices);

	return num;
}