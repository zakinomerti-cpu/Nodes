#ifndef _SHADER_VIZUALIZER_H_
#define _SHADER_VIZUALIZER_H_

#include <string>
#include "NEFrame/NodesEditor/Nodes/Node/Node.hpp"
class ShaderVisualizer : public Node {
public:
	static inline std::string CLASS_NAME = "ShaderVisualizer";
	ShaderVisualizer();
private:
	int initVar;
	unsigned int shaderProgram;
	unsigned int vao, vbo, ibo;
	unsigned int fbo, rbo, texcolbuff;

	const char* vertexShaderSource;
	const char* fragmentShaderSource;

	unsigned int compileShader(unsigned int, const char*);
	void createShader();
	void init();
	void initFBO(int width, int height);
	void render();
};

#endif