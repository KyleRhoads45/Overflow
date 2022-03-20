#include <unordered_map>
#include "Input.h"

static std::unordered_map<int, bool> keyMap;
static std::unordered_map<int, bool> mouseMap;

static double lastMouseXPos = 0; 
static double lastMouseYPos = 0;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void MouseCallback(GLFWwindow* window, int button, int action, int mods);

void InputInit(GLFWwindow* window) {
    if (glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwGetCursorPos(window, &lastMouseXPos, &lastMouseYPos);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseCallback);
}

bool OnKeyHold(const int key) {
    if (keyMap.find(key) == keyMap.end()) return false;
    return keyMap[key];
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyMap[key] = true;
    }
    if (action == GLFW_RELEASE) {
        keyMap[key] = false;
    }
}

static void MouseCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        mouseMap[button] = true;
    }
    if (action == GLFW_RELEASE) {
        mouseMap[button] = false;
    }
}
