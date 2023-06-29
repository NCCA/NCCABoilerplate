#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
auto main() -> int
{
  std::cerr << "Creating OpenGL Context\n";
  GLFWwindow *window;

  /* Initialize the library */
  auto init = glfwInit();
  // use GL 4.1 as it's the max mac can use.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  window = glfwCreateWindow(1024, 720, "", nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
}
