#include <GLFW/glfw3.h>

int main(void) {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Window", NULL, NULL);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
