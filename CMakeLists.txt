cmake_minimum_required(VERSION 3.0)

project(GAME)

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)

set (GAME_SRCS ${PROJECT_SOURCE_DIR}/main.cpp)

add_executable(GAME ${GAME_SRCS})

include_directories(${PROJECT_ROOT_DIR}/include)

if (MSVC)
  target_link_libraries(GAME ${PROJECT_ROOT_DIR}/lib/glfw3.lib opengl32 gdi32 user32 kernel32 shell32)
	set (CMAKE_CXX_FLAGS "/MD /EHsc")
endif (MSVC)

if(${CMAKE_COMPILER_IS_GNUCC})
	link_directories(/usr/local/lib)
  link_directories(${PROJECT_ROOT_DIR}/lib)
	target_link_libraries(GAME glfw3 GL 
	# glfw3 library dependencies
	glfw3 rt Xrandr Xinerama Xi Xcursor m dl Xrender drm Xdamage X11-xcb 
		xcb-glx xcb-dri2 xcb-dri3 xcb-present xcb-sync xshmfence Xxf86vm 
		Xfixes Xext X11 pthread xcb Xau Xdmcp
	)
  set (CMAKE_CXX_FLAGS "-std=c++11 -g")
endif()


