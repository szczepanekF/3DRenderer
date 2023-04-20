#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
int main(void) {
    GLFWwindow* mainWindow;
    if (!glfwInit()) return -1;

    mainWindow = glfwCreateWindow(640,480,"Hello World",NULL,NULL);
    if (!mainWindow) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    while (!glfwWindowShouldClose(mainWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

