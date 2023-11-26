#include <SFML/Graphics/RenderWindow.hpp>
#include <glad/gl.h>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <TGUI/TGUI.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Backend/SFML-OpenGL3.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* #define STB_IMAGE_IMPLEMENTATION */
#include "stb_image.h"

#include <cstdint>
#include <iostream>

#include "Camera/Camera.h"
#include "Shader/Shader.h"
#include "Input/Input.h"
#include "App/App.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Model/Box.h"


const uint32_t kScreenWidth  = 800;
const uint32_t kScreenHeight = 600;

int main () {

  sf::ContextSettings settings;
  settings.depthBits = 24; // Need this for DEPTH_TEST
  settings.stencilBits = 0;
  settings.antialiasingLevel = 4;

  sf::Window window(sf::VideoMode(kScreenWidth,kScreenHeight), "Simulation", sf::Style::Default, settings);
  window.setActive(true);
  window.setVerticalSyncEnabled(false);

  tgui::Gui gui{window};

  /* Camera camera(glm::vec3(0.0f, 0.0f, -3.0f)); */
  /* App app{window, camera}; */

  int version = gladLoaderLoadGL();
  if (!version) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  /* stbi_set_flip_vertically_on_load(true); */

  /* Shader ball_shader{"resources/shaders/ball.vert", "resources/shaders/ball.frag"}; */
  /* Shader line_shader{"resources/shaders/line.vert", "resources/shaders/line.frag"}; */
  /**/
  /* sf::Clock clock; */
  /* sf::Clock clock2; */
  /**/
  /* Model ball_model("resources/models/ball/ball.obj"); */
  /* Box box{}; */
  /**/
  /* glad_glEnable(GL_DEPTH_TEST); */

  while (window.isOpen()) {

    sf::Event event;
    window.pollEvent(event);

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.scancode == sf::Keyboard::Scan::Escape) {
          window.close();
        }
      }
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

   /*  loat dt = clock.restart().asSeconds(); */
   /*   std::string fps = "FPS: " + std::to_string(1.0/dt); */ 
   /*   app.SetDeltaTime(clock.restart().asSeconds()); */ 
   /*  app.SetDeltaTime(dt); */
   /**/
   /*   app.GetWindow().setTitle(fps); */
   /**/
   /*  ProcessEvents(app); */
   /*  ProcessKeyboard(app); */
   /*  ProcessMouse(app); */
   /**/
    glad_glClearColor(0.2, 0.5, 0.8, 1.0);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   /**/
   /*  glm::mat4 model = glm::mat4(1.0f); */
   /*  glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(kScreenWidth)/kScreenHeight, 0.05f, 100.0f); */
   /*  glm::mat4 view = camera.GetViewMatrix(); */
   /*  glm::mat4 pvm = projection * view * model; */
   /**/
   /* ball_shader.Use(); */
   /**/
   /*  model = glm::mat4(1.0f); */
   /*  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); */
   /*  model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01)); */
   /**/
   /**/
   /*  pvm = projection * view * model; */
   /*  ball_shader.SetMat4("pvm", pvm); */
   /*  ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f)); */
   /*   float time = clock2.getElapsedTime().asSeconds(); */ 
   /*   ball_shader.SetVec3f("light_pos", glm::vec3(cos(time), 2.0f, sin(time))); */
   /*  all_shader.SetVec3f("light_pos", glm::vec3(0.0f, 2.0f, 1.0f)); */
   /**/
   /*  glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); */
   /*  ball_model.Draw(ball_shader); */
   /**/
   /*  // Draw line */
   /*  line_shader.Use(); */
   /*  model = glm::mat4(1.0f); */
   /*  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); */
   /*  model = glm::scale(model, glm::vec3(2.5, 1.5, 1.5)); */
   /*  pvm = projection * view * model; */
   /*  line_shader.SetVec3f("line_color", glm::vec3(1.0, 1.0, 1.0)); */
   /*  line_shader.SetMat4("pvm", pvm); */
   /*  box.Draw(); */

    /* gui.draw(); */

    window.display();
  }

  gladLoaderUnloadGL();
  return 0;
}
