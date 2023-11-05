#include <glad/gl.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdint>
#include <iostream>

#include "Camera/Camera.h"
#include "Shader/Shader.h"
#include "Input/Input.h"
#include "App/App.h"
#include "Model/Model.h"
#include "Model/Mesh.h"


float vertices[] = {
  // Positions        // Colors
  -0.5f, -0.5f, 2.0f, 1.0f, 0.0f, 0.0f,
   0.5f, -0.5f, 2.0f, 0.0f, 1.0f, 0.0f,
   0.0f,  0.5f, 2.0f, 0.0f, 0.0f, 1.0f
};

const uint32_t kScreenWidth  = 800;
const uint32_t kScreenHeight = 600;

int main () {

  
  sf::Window window(sf::VideoMode(kScreenWidth,kScreenHeight), "My window");
  window.setActive(true);
  window.setVerticalSyncEnabled(false);
  Camera camera(glm::vec3(0.0f, 0.0f, -3.0f));
  App app{window, camera};
  
  int version = gladLoaderLoadGL();
  if (!version) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }
  glad_glEnable(GL_DEPTH_TEST);

  uint32_t VBO;
  uint32_t VAO;

  glad_glGenVertexArrays(1, &VAO);
  glad_glGenBuffers(1, &VBO);
  glad_glBindVertexArray(VAO);
  glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
  glad_glEnableVertexAttribArray(0);

  glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
  glad_glEnableVertexAttribArray(1);

  glad_glBindBuffer(GL_ARRAY_BUFFER, 0);
  glad_glBindVertexArray(0);
 
  Shader triangle{"resources/shaders/vertex.vert", "resources/shaders/fragment.frag"};

  sf::Clock clock;

/* camera.SetZoom(80.0); */
  while (app.IsOpen()) {

    /* float dt = clock.restart().asSeconds(); */
    /* std::string fps = "FPS: " + std::to_string(1000.0/dt); */
    /* scene.SetDeltaTime(dt); */
    app.SetDeltaTime(clock.restart().asSeconds());
    
    /* scene.GetWindow().setTitle(fps); */
    ProcessEvents(app);
    ProcessKeyboard(app);
    ProcessMouse(app);

    glad_glClearColor(0.2, 0.5, 0.8, 1.0);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangle.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(kScreenWidth)/kScreenHeight, 0.05f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();

    glm::mat4 pvm = projection * view * model;
    triangle.SetMat4("pvm", pvm);

    glad_glBindVertexArray(VAO);
    glad_glDrawArrays(GL_TRIANGLES, 0, 3);

    window.display();
  }

  gladLoaderUnloadGL();
  return 0;
}



