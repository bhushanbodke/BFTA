#pragma once
#include<GLFW/glfw3.h>

class Usegui
{
public:
	void init(GLFWwindow* window);
	void Frame();
	void render();
	void destroy();
};

