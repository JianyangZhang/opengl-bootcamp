#ifndef  MESH_H
#define  MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
public:
	Vertex(const glm::vec3& pos) {
		this->pos = pos;
	};
protected:
private:
	glm::vec3 pos;
};

class Mesh {
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	void draw();
	virtual ~Mesh();
private:
	Mesh(const Mesh& other) {};
	void operator = (const Mesh& other) {};

	GLuint m_vertexArrayObject;
};

#endif // ! MESH_H