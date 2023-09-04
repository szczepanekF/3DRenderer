#include <GLFW/glfw3.h>
#include <GL/gl.h>



int main(void) {

    GLFWwindow *mainWindow;
    if (!glfwInit()) return -1;

    mainWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!mainWindow) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(mainWindow);

    while (!glfwWindowShouldClose(mainWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINE);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(1.0f, -1.0f);
        glEnd();
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

