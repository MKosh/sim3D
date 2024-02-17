#pragma once

class Renderer {
public:
  Renderer();
  Renderer(Renderer &&) = default;
  Renderer(const Renderer &) = default;
  Renderer &operator=(Renderer &&) = default;
  Renderer &operator=(const Renderer &) = default;
  ~Renderer();

  auto ClearScreen() -> void;

private:
  
};

