#include <pax_glsl.h>
#include <pax_error.h>

#include <fstream>
#include <string>
#include <vector>

GLSLProgram::GLSLProgram()
{
	this->program_ID = 0;
	this->vertex_shader_ID = 0;
	this->fragment_shader_ID = 0;
	this->num_attributes = 0;
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShader(const char* file_path, GLuint id)
{
	// investigate the renaming of the vertexFile member
	std::fstream vertexFile(std::string(file_path).c_str());
	if (vertexFile.fail()) {
		perror(file_path);
		FatalError("GLSL Compilation: Error whilst reading vertex shader file " + std::string(file_path));
	}

	std::string file_contents = "";
	std::string line;

	while (std::getline(vertexFile, line)) {
		file_contents += line + "\n";
	}

	vertexFile.close();

	// this should be changed to reflect more sound practise
	const char* contents_ptr = file_contents.c_str();
	GLint contents_length = file_contents.length();
	glShaderSource(id, 1, &contents_ptr, &contents_length);

	glCompileShader(id);

	// Error traps
	GLint compile_success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &compile_success);
	if (compile_success == GL_FALSE) {
		// Error during compilation process
		GLint max_length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &max_length);

		// max_length includes the NULL character
		std::vector<GLchar> errorLog(max_length);
		glGetShaderInfoLog(id, max_length, &max_length, &errorLog[0]);

		// Provide the information to the user in a friendly way
		// Exit with failure
		glDeleteShader(id);
		std::printf("%s\n", &errorLog[0]);
		FatalError("GLSL Compilation: Shader failed to compile : " + std::string(file_path));

		return;
	}
}

void GLSLProgram::CompileShaders(const char* &vertex_shader_file_path, const char* &fragment_shader_file_path)
{
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	this->program_ID = glCreateProgram();

	this->vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	if (this->vertex_shader_ID == 0) {
		FatalError("GLSL Compilation: Failed to read vertex shader file.");
	}

	this->fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	if (this->fragment_shader_ID == 0) {
		FatalError("GLSL Compilation: Failed to read fragment shader file.");
	}

	CompileShader(vertex_shader_file_path, vertex_shader_ID);
	CompileShader(fragment_shader_file_path, fragment_shader_ID);
}

void GLSLProgram::LinkShaders()
{
	//Attach our shaders to our program
	glAttachShader(this->program_ID, vertex_shader_ID);
	glAttachShader(this->program_ID, fragment_shader_ID);

	//Link our program
	glLinkProgram(this->program_ID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(this->program_ID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(this->program_ID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(this->program_ID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(this->program_ID);
		//Don't leak shaders either.
		glDeleteShader(vertex_shader_ID);
		glDeleteShader(fragment_shader_ID);

		std::printf("%s\n", &(errorLog[0]));
		FatalError("GLSL Compilation: Shaders failed to link");

		//In this simple program, we'll just leave
		return;
	}

	//Always detach shaders after a successful link.
	glDetachShader(this->program_ID, vertex_shader_ID);
	glDetachShader(this->program_ID, fragment_shader_ID);
	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);
}

void GLSLProgram::AddAttribute(const char* &attribute_name)
{
	glBindAttribLocation(program_ID, num_attributes++, attribute_name);
}

GLuint GLSLProgram::GetUniformLocation(char* &uniform_name)
{
	GLuint location = glGetUniformLocation(program_ID, uniform_name);
	if (location == GL_INVALID_INDEX) {
		// if uniform requested does not exist
		// TODO: get rid of the fatal error in the near future
		FatalError("Uniform: Uniform name not found in shader.");
	}
	return location;
}

void GLSLProgram::Use()
{
	glUseProgram(program_ID);

	// Enable each attribute
	for (int i = 0; i < num_attributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::Disuse()
{
	glUseProgram(0);

	// Disable
	for (int i = 0; i < num_attributes; i++) {
		glDisableVertexAttribArray(i);
	}
}
