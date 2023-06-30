#include <cstdlib>
#include <iostream>
#ifndef __APPLE__
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif
#include "GLFunctions.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

// key callback
void keyCallback(GLFWwindow *_window, int _key, int _scancode, int _action, int _mods);

int main()
{
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
  {
    std::cout << "Failed to init GLFW\n";
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1024, 720, "GLFW Triangle", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  // set the key callback
  glfwSetKeyCallback(window, keyCallback);

#ifndef __APPLE__
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cerr << "Error: " << glewGetErrorString(err) << '\n';
    exit(EXIT_FAILURE);
  }
  std::cerr << "Status: Using GLEW" << glewGetString(GLEW_VERSION) << '\n';
#endif

  // create the triangle
  auto vaoID = createTriangle(0.8f);
  const std::string vertex = R"(
#version 400 core

layout (location = 0) in vec3  inPosition;
layout (location = 1) in vec3 inColour;
layout (location = 2) in vec3 inNormal;
uniform mat4 MVP;
uniform mat4 model;
out vec3 vertColour;
out vec3 normal;
out vec3 fragPos;
void main()
{
  gl_Position = MVP*vec4(inPosition, 1.0);
  vertColour = inColour;
  normal = normalize(inNormal);
  fragPos = vec3(model * vec4(inPosition, 1.0));
}
)";

  // some source for our fragment shader
  const std::string fragment = R"(
#version 400 core
in vec3 vertColour;
in vec3 normal;
in vec3 fragPos;
out vec4 fragColour;
uniform vec3 lightPos;  

void main()
{
	vec3 s = normalize(lightPos - fragPos);
	vec3 v = normalize(-fragPos);
	vec3 h = normalize( v + s );
	float sDotN = max( dot(s,normal), 0.0 );
	vec3 diffuse = vertColour * sDotN;
  fragColour = vec4(diffuse,1.0);
}
)";

  auto shaderID = loadShaderFromStrings(vertex, fragment);
  // we will store uniform locations here as it is expensive to look up each time
  // First MVP
  auto MVP = glGetUniformLocation(shaderID, "MVP");
  auto model = glGetUniformLocation(shaderID, "model");
  auto lightPos = glGetUniformLocation(shaderID, "lightPos");

  // now set the things that are not going to change much
  glUniform3f(lightPos, 0.0f, 2.0f, 0.0f);

  // now clear the screen and swap whilst NGL inits (which may take time)
  glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

  // resize the ngl to set the screen size and camera stuff
  // Note we need to get this for retinal display else we will get smaller
  // window due to pixel size see http://www.glfw.org/docs/latest/window.html#window_fbsize
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  /* Loop until the user closes the window */
  float rotation = 0.0f;
  // sdl event processing data structure
  glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.5f, 1.5f),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 project = glm::perspective(45.0f, static_cast<float>(1024) / 720, 0.01f, 200.0f);

  while (!glfwWindowShouldClose(window))
  {
    // now clear the screen and swap whilst NGL inits (which may take time)
    glClear(GL_COLOR_BUFFER_BIT);

    rotation += 1.0f;
    // create a rotation matrix around the y axis note the conversion to radians
    auto rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    // now set the MVP matrix of the triangle
    auto transform = project * view * rotY;
    // note the use of glm::value_ptr to convert to gl pointer.
    glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(transform));
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(view * rotY));
    glBindVertexArray(vaoID);         // select first bind the array
    glDrawArrays(GL_TRIANGLES, 0, 3); // draw object

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
  glDeleteProgram(shaderID);
  glDeleteVertexArrays(1, &vaoID);

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
