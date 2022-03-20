#pragma once
class Shader {

public:

	Shader(const char* vertexPath, const char* fragmentPath);
	int id;

private:

	void CheckCompileErrors(unsigned int shader, const char* type);

};

