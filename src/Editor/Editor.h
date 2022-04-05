#pragma once

class Editor {
	
public:

	static void Start(GLFWwindow* window);
	static void Update(GLFWwindow* window);

private:

	static void SetTheme();
	static void RenderAllGizmos();

	static bool showGizmos;

};

