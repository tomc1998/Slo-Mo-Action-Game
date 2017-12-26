cmake_minimum_required(VERSION 3.0)
project(game)

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
  ${PROJECT_SOURCE_DIR}/engine/vec.cpp
  ${PROJECT_SOURCE_DIR}/engine/renderer.cpp
  ${PROJECT_SOURCE_DIR}/engine/engine.cpp
  ${PROJECT_SOURCE_DIR}/engine/ecs.cpp
  )

add_executable(game ${game_SRCS})
target_include_directories(game PUBLIC ${PROJECT_SOURCE_DIR})

#############################################
# Dependencies
#############################################

# OpenGL ###########################################
# For GNU Linux, should only need to link to this... windows might be a bit
# different.
target_link_libraries(game GL)
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

#############################################
# COMPILER FLAGS
#############################################
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	SET_TARGET_PROPERTIES(game
    PROPERTIES COMPILE_FLAGS "/FI engine/typedefs.hpp /W4 /Wall")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	SET_TARGET_PROPERTIES(game
		PROPERTIES COMPILE_FLAGS "-include engine/typedefs.hpp -Wall -Wpedantic -g -std=c++11")
endif()

