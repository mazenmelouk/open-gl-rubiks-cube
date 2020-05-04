cmake_minimum_required (VERSION 2.6)
project (Cube)

file(GLOB SRC "src/*.cpp")

add_executable(Cube ${SRC})

include_directories(include)
include_directories(src)
include_directories(/usr/local/include)

# find_package(glfw3 3.3 REQUIRED)

target_link_libraries(Cube
# -lstdc++ \
  # "-framework Cocoa"
  # "-framework CoreVideo"
  # "-framework IOKit"
  # "-framework OpenGL"
  # "-framework Glut"
  glfw
)

target_compile_options(Cube PUBLIC -s USE_GLFW=3)
set (CMAKE_CXX_FLAGS "-s USE_GLFW=3 --preload-file vshader.glsl --preload-file fshader.glsl -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2")

configure_file(shaders/vshader.glsl vshader.glsl COPYONLY)
configure_file(shaders/fshader.glsl fshader.glsl COPYONLY)
configure_file(index.html index.html COPYONLY)
