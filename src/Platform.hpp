#ifndef _PLATFORM_HPP_
#define _PLATFORM_HPP_

struct GLFWwindow;

#include <functional>

class Platform {
private:
	int m_width;
	int m_height;
	char m_shouldClose;

	GLFWwindow* nodesEditorWindow;

	std::function<void()> m_onStart;
	std::function<void(int width, int height)> m_onUpdate;
	std::function<void()> m_onDestroy;

public:
	Platform(int width, int height, const char* title);
	void init();

	void onDestroy(std::function<void()> callback);
	void onStart(std::function<void()> callback);
	void onUpdate(std::function<void(int width, int height)> callback);

	int getWidth();
	int getHeingt();

	void render();
	char shouldClose();
};

#endif
