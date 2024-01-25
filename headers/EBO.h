#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>

class EBO
{
public:
	unsigned int ID;

	EBO(unsigned int* indices);

	void Bind();

	void Unbind();

	void Delete();
};

#endif