cmake_minimum_required(VERSION 3.0)
project(game)

## Configure CMake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###################################
# Initialise directory structure
###################################

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)
set (PROJECT_DEP_DIR ${PROJECT_ROOT_DIR}/deps)

###################################
# Set sources & add an executable
###################################
set (game_SRCS 
  ${PROJECT_SOURCE_DIR}/main.cpp
  ${PROJECT_SOURCE_DIR}/test_screen.cpp
  ${PROJECT_SOURCE_DIR}/engine/vec.cpp
  ${PROJECT_SOURCE_DIR}/engine/matrix.cpp
  ${PROJECT_SOURCE_DIR}/engine/util/io.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/paint_controller.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/renderer.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/paint_buffer.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/vertex.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/batch.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/shader.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer/tex_cache.cpp
  ${PROJECT_SOURCE_DIR}/engine/input/input_manager.cpp
  ${PROJECT_SOURCE_DIR}/engine/engine.cpp
  ${PROJECT_SOURCE_DIR}/engine/resource_manager.cpp
  ${PROJECT_SOURCE_DIR}/engine/camera.cpp
  ${PROJECT_SOURCE_DIR}/engine/animation.cpp
  ${PROJECT_SOURCE_DIR}/engine/anim_frame.cpp
  ${PROJECT_SOURCE_DIR}/engine/tileset.cpp
  ${PROJECT_SOURCE_DIR}/engine/font.cpp
  ${PROJECT_SOURCE_DIR}/engine/glyph.cpp
  ${PROJECT_SOURCE_DIR}/engine/keyframe.cpp
  ${PROJECT_SOURCE_DIR}/engine/ecs.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/player_controlled.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/physics.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/wall_collision.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/animation_update.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/camera_update.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/tilemap_renderer.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/ai_enemy_basic.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/bullet_collision.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/check_death.cpp
  ${PROJECT_SOURCE_DIR}/engine/system/hud_renderer.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/player_controlled.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/game_entity.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/wall.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/animation.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/tilemap.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/ai_enemy_basic.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/bullet.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/sprite.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/player_killable.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/hud_entity.cpp
  ${PROJECT_SOURCE_DIR}/engine/comp/circle_collider.cpp  
  )


add_executable(game ${game_SRCS})
target_include_directories(game PUBLIC ${PROJECT_SOURCE_DIR})

#############################################
# Dependencies
#############################################

# OpenGL ###########################################
# For GNU Linux, should only need to link to this... windows might be a bit
# different.
if (LINUX AND NOT APPLE)
  target_link_libraries(game GL)
elseif (WIN32)
  target_link_libraries(game opengl32)
endif ()
####################################################

# GLFW #############################################
# Make sure GLFW doesn't build examples / tests / docs
add_subdirectory(${PROJECT_DEP_DIR}/glfw)
set (GLFW_BUILD_EXAMPLES OFF)
set (GLFW_BUILD_TESTS OFF)
set (GLFW_BUILD_DOCS OFF)
set (GLFW_VULKAN_STATIC OFF) # Make sure GLFW doesn't build vulkan
target_link_libraries(game glfw)
target_include_directories(game PUBLIC ${PROJECT_DEP_DIR}/glfw/include)
####################################################

# GLAD #############################################
# Compile glad as a static library and then link it:
set(GLAD_ROOT_DIR ${PROJECT_DEP_DIR}/glad)
set(GLAD_SRCS
  ${GLAD_ROOT_DIR}/src/glad.c
	)
add_library(glad STATIC ${GLAD_SRCS})
target_include_directories(glad PUBLIC ${GLAD_ROOT_DIR}/include)
target_link_libraries(game glad)
target_include_directories(game PUBLIC ${GLAD_ROOT_DIR}/include)
####################################################

# SparsePP #############################################
# Header only library for sparse contiguous hash maps
target_include_directories(game PUBLIC ${PROJECT_DEP_DIR}/sparsepp)
####################################################

# stb_image #############################################
# Header only library for loading images
target_include_directories(game PUBLIC ${PROJECT_DEP_DIR}/stb_image)
####################################################

# json #############################################
# Header only library for parsing json
target_include_directories(game PUBLIC ${PROJECT_DEP_DIR}/json)
####################################################

#############################################
# COMPILER FLAGS
#############################################
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET_TARGET_PROPERTIES(game
    PROPERTIES COMPILE_FLAGS "-include engine/typedefs.hpp -Wall -Wpedantic -g -std=c++11 -fdiagnostics-color")
	SET_TARGET_PROPERTIES(game
  PROPERTIES LINK_FLAGS "-include engine/typedefs.hpp")
endif()

