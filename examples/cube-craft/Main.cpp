#include <fmt/core.h>

#include "abcg.hpp"
#include "OpenGLWindow.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    auto window{std::make_unique<OpenGLWindow>()};
    window->setOpenGLSettings({.samples = 0});
    window->setWindowSettings(
        {.width = 1280, .height = 720, .title = "Cube Craft"});

    app.run(window);
  } catch (abcg::Exception &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}
