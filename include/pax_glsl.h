#ifndef PAX_GLSL_H
#define PAX_GLSL_H

#include <GL/glew.h>

class GLSLProgram {
private:
	GLuint program_ID;
	GLuint vertex_shader_ID;
	GLuint fragment_shader_ID;

	int num_attributes;

	void CompileShader(const char* file_path, GLuint id);

public:
	// Rename in due course
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const char* &vertex_shader_file_path, const char* &fragment_shader_file_path);
	void LinkShaders();
	void AddAttribute(const char* &attribute_name);

	void Use();
	void Disuse();
};

#endif