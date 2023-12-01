#include "App.h"
/* #include <glad/gl.h> */
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Model/Box.h"
#include <GLFW/glfw3.h>


namespace sim3D {

auto App::GetInstance() -> App* {
  if (app == nullptr) {
    app = new App();
  }
  return app;
}

void App::run() {
  glad_glEnable(GL_DEPTH_TEST);
  Shader ball_shader{"resources/shaders/ball.vert", "resources/shaders/ball.frag"};
  Shader line_shader{"resources/shaders/line.vert", "resources/shaders/line.frag"};

  Model ball_model("resources/models/sphere/sphere3.obj");
  Box box{};
  m_last_time = 0.0;
  while (!glfwWindowShouldClose(m_window.GetWindow())) {
 
    glfwPollEvents(); 

    /* last_time = current_time; */
    /* current_time = (float)glfwGetTime(); */
    /* dt = current_time - last_time; */
    /* frames = 1.0f/dt; */
    /* std::cout << "FPS: " << frames << '\n'; */

    /* fps << frames; */
    /* button->setText(std::to_string(1.0f/dt)); */
    /* fps.str(""); */

    /* sprintf(fps, "%6.2f", 1.0f/dt); */
    /* button->setText(fps); */
    /* app.SetDeltaTime(dt); */

    /* ProcessEvents(app); */
    /* ProcessKeyboard(app);  */
    /* ProcessMouse(app);  */

    glad_glClearColor(0.2, 0.5, 0.8, 1.0);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetZoom()), static_cast<float>(kWidth)/kHeight, 0.05f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 pvm = projection * view * model;

    ball_shader.Use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
    

    pvm = projection * view * model;
    ball_shader.SetMat4("pvm", pvm);
    ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f));
    ball_shader.SetVec3f("light_pos", glm::vec3(0.0f, 2.0f, 1.0f));
      
    glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ball_model.Draw(ball_shader);
      
    // Draw line */
    line_shader.Use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));
    pvm = projection * view * model;
    line_shader.SetVec3f("line_color", glm::vec3(1.0, 1.0, 1.0));
    line_shader.SetMat4("pvm", pvm);
    box.Draw();
      
      
    glfwSwapBuffers(m_window.GetWindow());
  }
}

/* auto App::Shutdown() -> void { */
/*   m_window.ShouldClose(true); */
/* } */

}
