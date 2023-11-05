#include <glad/gl.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <cstdint>
#include <iostream>

#include "Camera/Camera.h"
#include "Shader/Shader.h"
#include "Input/Input.h"
#include "App/App.h"
#include "Model/Model.h"
#include "Model/Mesh.h"


const uint32_t kScreenWidth  = 800;
const uint32_t kScreenHeight = 600;

glm::vec3 start{-0.5f, 0.5f, 0.5f};
glm::vec3 end{0.5f, 0.5f, 0.5f};
/* float vertices[] = { */
/*     -0.5f, -0.5f, 0.0f, */
/*      0.5f, -0.5f, 0.0f, */
/*      0.0f,  0.5f, 0.0f */
/* }; */
int main () {

  sf::ContextSettings settings;
  settings.depthBits = 24; // Need this for DEPTH_TEST
  settings.stencilBits = 0;
  settings.antialiasingLevel = 4;

  sf::Window window(sf::VideoMode(kScreenWidth,kScreenHeight), "My window", sf::Style::Default, settings);
  window.setActive(true);
  window.setVerticalSyncEnabled(false);
  Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));
  App app{window, camera};

  int version = gladLoaderLoadGL();
  if (!version) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  stbi_set_flip_vertically_on_load(true);

  // Drawing a line
  /* float vertices[] = { */
  /*   start.x, start.y, start.z, */
  /*   end.x, end.y, end.z, */
  /* }; */
  float vertices[] = {
    // Back Top
    -0.5, 0.5, 0.5, // Back Top Right
     0.5, 0.5, 0.5, // Back top left
    // Back left
     0.5, 0.5, 0.5, // Back top left
     0.5, -0.5, 0.5,// Back bottom left
    // Back bottom
     0.5, -0.5, 0.5,// Back bottom left
    -0.5, -0.5, 0.5,// Back bottom right
    // Back right
    -0.5, -0.5, 0.5,// Back bottom right
    -0.5, 0.5, 0.5, // Back Top right again
    // Front top
    -0.5, 0.5, -0.5,// front top right
    0.5, 0.5, -0.5, // front top left
    // Front left
    0.5, 0.5, -0.5,// front bottom left
    0.5, -0.5, -0.5,// front bottom right
    // Front bottom
    0.5, -0.5, -0.5,// front top right again
    -0.5, -0.5, -0.5,// front top right again
    // Front right
    -0.5, -0.5, -0.5,// front bottom left
    -0.5, 0.5, -0.5, // front bottom right
    // Left top
    0.5, 0.5, 0.5, // Back
    0.5, 0.5, -0.5, // front
    // Left bottom
    0.5, -0.5, 0.5, // back
    0.5, -0.5, -0.5,// front
    // Right top
    -0.5, 0.5, 0.5,
    -0.5, 0.5, -0.5,
    // Right bottom
    -0.5, -0.5, 0.5,
    -0.5, -0.5, -0.5
  };
  uint32_t VBO, VAO;
  glad_glGenVertexArrays(1, &VAO);
  glad_glGenBuffers(1, &VBO);
  glad_glBindVertexArray(VAO);
  glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
  /* glad_glVertexAttribPointer() */
  glad_glEnableVertexAttribArray(0);
  glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
  /* glad_glBindVertexArray(0); */
  // Drawing a line

  Shader ball_shader{"resources/shaders/ball.vert", "resources/shaders/ball.frag"};
  Shader box_shader{"resources/shaders/box.vert", "resources/shaders/box.frag"};
  Shader line_shader{"resources/shaders/line.vert", "resources/shaders/line.frag"};

  sf::Clock clock;
  sf::Clock clock2;

  Model ball_model("resources/models/ball/ball.obj");
  /* Model box_model("resources/models/cube/box.obj"); */
  
  glad_glEnable(GL_DEPTH_TEST);

  while (app.IsOpen()) {

    float dt = clock.restart().asSeconds();
    /* std::string fps = "FPS: " + std::to_string(1.0/dt); */
    /* app.SetDeltaTime(clock.restart().asSeconds()); */
    app.SetDeltaTime(dt);
    
    /* app.GetWindow().setTitle(fps); */

    ProcessEvents(app);
    ProcessKeyboard(app);
    ProcessMouse(app);

    glad_glClearColor(0.2, 0.5, 0.8, 1.0);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw Box
    /* box_shader.Use(); */

    glm::mat4 model = glm::mat4(1.0f);
    /* model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); */
    /* model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1)); */
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(kScreenWidth)/kScreenHeight, 0.05f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 pvm = projection * view * model;

    /* box_shader.SetMat4("pvm", pvm); */
    /* box_shader.SetVec3f("i_color", glm::vec3(0.1, 0.1, 0.1)); */

    /* glad_glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
    /* box_model.Draw(box_shader); */

    // Draw Ball
    ball_shader.Use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));
    

    pvm = projection * view * model;
    ball_shader.SetMat4("pvm", pvm);
    ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f));
    float time = clock2.getElapsedTime().asSeconds();
    ball_shader.SetVec3f("light_pos", glm::vec3(cos(time), 2.0f, sin(time)));

    glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ball_model.Draw(ball_shader);

    // Draw line
    line_shader.Use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(2.5, 1.5, 1.5));
    pvm = projection * view * model;
    line_shader.SetVec3f("line_color", glm::vec3(1.0, 1.0, 1.0));
    line_shader.SetMat4("pvm", pvm);
    glad_glBindVertexArray(VAO);
    glad_glDrawArrays(GL_LINES, 0, 24);

    window.display();
  }

  gladLoaderUnloadGL();
  return 0;
}
