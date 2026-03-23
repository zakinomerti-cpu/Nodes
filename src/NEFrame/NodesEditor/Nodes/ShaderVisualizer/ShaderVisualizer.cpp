#include "glad/glad.h"
#include "ShaderVisualizer.hpp"
#include "imgui/imgui_impl_opengl3_loader.h"
#include <iostream>

ShaderVisualizer::ShaderVisualizer() : Node(CLASS_NAME) {
	initVar = 0;
	addNodeDrawPath([this]() {
		render();
	});

	vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	fragmentShaderSource = "#version 330 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
}

unsigned int ShaderVisualizer::compileShader(unsigned int type, const char* shaderSource) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderSource, 0);
	glCompileShader(shader);

	int success;
	char log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << log << std::endl;
		return -1;
	}

	return shader;
}

void ShaderVisualizer::createShader() {
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	char log[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << log << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderVisualizer::init() {
	float vertices[]{
		-0.5, -0.5, 0.0,
		 0.5, -0.5, 0.0,
		 0.0,  0.5, 0.0,

	};

	GLuint indices[]{
		0, 1, 2
	};

	this->createShader();

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0x88E4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 0x88E4);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void ShaderVisualizer::initFBO(int width, int height) {
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &texcolbuff);
	glBindTexture(GL_TEXTURE_2D, texcolbuff);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texcolbuff, 0);

	// depth/stencil
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "FBO error\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void ShaderVisualizer::render() {
	if (initVar == 0) {
		init();
		initFBO(800, 600);
		initVar = 1;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, 800, 600);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ImGui::Image(
		(ImTextureID)(intptr_t)texcolbuff,
		ImVec2(400, 300),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);

	ImGui::Text("This is some useful text.");
}
