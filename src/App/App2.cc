#include "App2.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Model/Box.h"

namespace sim3D {

void FirstApp::run() {
  Shader ball_shader{"resources/shaders/ball.vert", "resources/shaders/ball.frag"};
  Shader line_shader{"resources/shaders/line.vert", "resources/shaders/line.frag"};

  /* sf::Clock clock; */
  /* sf::Clock clock2; */

  Model ball_model("resources/models/ball/ball.obj");
  Box box{};
  m_last_time = 0.0;
  while (!m_window.ShouldClose()) {
    glfwPollEvents();
    glClearColor(0.2, 0.5, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_current_time = (float)glfwGetTime();

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetZoom()), static_cast<float>(800)/600.0f, 0.05f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 pvm = projection * view * model;

    ball_shader.Use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.01, 0.01, 0.01));


    pvm = projection * view * model;
    ball_shader.SetMat4("pvm", pvm);
    ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f));
    float time = GetDeltaTime();
    ball_shader.SetVec3f("light_pos", glm::vec3(cos(time), 2.0f, sin(time)));
    ball_shader.SetVec3f("light_pos", glm::vec3(0.0f, 2.0f, 1.0f));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ball_model.Draw(ball_shader);

    // Draw line
    line_shader.Use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(2.5, 1.5, 1.5));
    pvm = projection * view * model;
    line_shader.SetVec3f("line_color", glm::vec3(1.0, 1.0, 1.0));
    line_shader.SetMat4("pvm", pvm);
    box.Draw();

    
  }
}
}
