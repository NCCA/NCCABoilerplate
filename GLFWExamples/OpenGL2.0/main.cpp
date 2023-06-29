#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>
using namespace std::chrono_literals;

static int s_activeButton;
// key callback
void keyCallback(GLFWwindow *_window, int _key, int _scancode, int _action, int _mods);
// mouse button press callback
void mouseButtonCallback(GLFWwindow *_window, int _button, int _action, int _mods);
// mouse move callback
void cursorPosCallback(GLFWwindow *_window, double _xpos, double _ypos);
// mouse wheel callback
void scrollCallback(GLFWwindow *_window, double _xoffset, double _yoffset);

void drawTriangle();

int main()
{
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
  {
    std::cout << "Failed to init GLFW\n";
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1024, 720, "GLFW and NGL", NULL, NULL);
  if (!window)
  {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return EXIT_FAILURE;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  // set the key callback
  glfwSetKeyCallback(window, keyCallback);
  // set mouse callback
  glfwSetMouseButtonCallback(window, mouseButtonCallback);
  // mouse cursor move callback
  glfwSetCursorPosCallback(window, cursorPosCallback);
  // scroll wheel callback
  glfwSetScrollCallback(window, scrollCallback);
  // Note we need to get this for retinal display else we will get smaller
  // window due to pixel size see http://www.glfw.org/docs/latest/window.html#window_fbsize
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  /* Loop until the user closes the window */
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  // set the projection matrix to prespective from glm
  float aspect = static_cast<float>(width) / height;
  auto persp = glm::perspective(45.0f, aspect, 0.5f, 100.0f);
  glLoadIdentity();
  glMultMatrixf(&persp[0][0]);
  // now create a static camera matrix for viewing the object
  glMatrixMode(GL_MODELVIEW);
  auto look = glm::lookAt(glm::vec3(2, 2, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  glLoadIdentity();
  glMultMatrixf(&look[0][0]);
  glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawTriangle();
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
    std::this_thread::sleep_for(10ms);
  }
  glfwTerminate();
}

void keyCallback(GLFWwindow *_window, int _key, int _scancode, int _action, int _mods)
{
  if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
  {
    exit(EXIT_SUCCESS);
  }
  if (_key == GLFW_KEY_W && _action == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  if (_key == GLFW_KEY_S && _action == GLFW_PRESS)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void mouseButtonCallback(GLFWwindow *_window, int _button, int _action, int _mods)
{
  double x, y;
  glfwGetCursorPos(_window, &x, &y);
  if (_action == GLFW_PRESS)
  {
    s_activeButton = _button;
  }

  else if (_action == GLFW_RELEASE)
  {
    s_activeButton = _button;
  }
}

void cursorPosCallback(GLFWwindow *_window, double _xpos, double _ypos)
{
  double x, y;
  glfwGetCursorPos(_window, &x, &y);
  // mouse move event
}

void scrollCallback(GLFWwindow *_window, double _xoffset, double _yoffset)
{
  // mouse wheel event
}

void drawTriangle()
{
  static float rot = 0.0f;
  glPushMatrix();
  glRotatef(rot, 0, 1, 0);
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex3d(0, 1, 0);
  glColor3f(0, 1, 0);
  glVertex3d(1, -1, 0);
  glColor3f(0, 0, 1);
  glVertex3d(-1, -1, 0);
  glEnd();
  glPopMatrix();
  rot++;
}
