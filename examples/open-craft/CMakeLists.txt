cmake_minimum_required(VERSION 3.11)
project(open-craft)
add_executable(${PROJECT_NAME} Main.cpp OpenGLWindow.cpp model/Model.cpp camera/Camera.cpp eventHandler/EventHandler.cpp map/SeaMap.cpp block/Block.cpp block/grassBlock/GrassBlock.cpp block/stoneBlock/StoneBlock.cpp block/woodBlock/WoodBlock.cpp block/glassBlock/GlassBlock.cpp sea/Sea.cpp render/TextureRender.cpp render/FluidRender.cpp ui/UI.cpp)
enable_abcg(${PROJECT_NAME})
