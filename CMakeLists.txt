# Set CMake compat
cmake_minimum_required(VERSION 3.18...4.0)

# Define the metadata
project(Tail-Tale
	VERSION 1.0.4
	DESCRIPTION ""
	HOMEPAGE_URL ""
	LANGUAGES CXX)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
		"MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 14)

# Get the dependency libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Bug/Leak finding
option(WITH_SANITIZERS "Build with enabled sanitizers" OFF)
if(WITH_SANITIZERS)
	add_compile_options(-fsanitize=undefined -fsanitize=address)
	add_link_options(-fsanitize=undefined -fsanitize=address)
endif()

add_library(cute_png STATIC
	src/cute_png.hpp src/cute_png.cpp)

# Define the source files
add_executable(tailtale WIN32
	src/main.cpp src/main.hpp
	src/debug.cpp src/debug.hpp
	src/game.cpp src/game.hpp
	src/grp_screen.cpp src/grp_screen.hpp
	src/grp_sprite.hpp
	src/input.cpp src/input.hpp
	src/puz_res.hpp
	src/puz_base.cpp src/puz_base.hpp
	src/puz_disp.cpp src/puz_disp.hpp
	src/puz_trial.cpp src/puz_trial.hpp
	src/sound.cpp src/sound.hpp)

# Game data
if(UNIX)
	include(GNUInstallDirs)
	set(DEFAULT_PREFIX "${CMAKE_INSTALL_DATAROOTDIR}/tailtale")
else()
	set(DEFAULT_PREFIX "data")
endif()
set(DATA_PREFIX "${DEFAULT_PREFIX}/" CACHE PATH "Where game data is located")

# Define the compilation flags
target_compile_options(tailtale PRIVATE -Wall -fno-exceptions -fno-rtti)
target_compile_definitions(tailtale PRIVATE DATA_PREFIX="${DATA_PREFIX}")
option(HIGH_QUALITY "Render in 480x360 instead of 320x240" ON)
if(HIGH_QUALITY)
	target_compile_definitions(tailtale PRIVATE HIGH_QUALITY)
endif()
option(DEBUG_LOG "Print debug message" OFF)
if(DEBUG_LOG)
	target_compile_definitions(tailtale PRIVATE DEBUG)
endif()

# Link the dependencies
target_link_libraries(tailtale PRIVATE
	cute_png SDL2_mixer::SDL2_mixer SDL2::SDL2)
if(UNIX)
	target_link_libraries(tailtale PRIVATE m)
endif()

# Installation
if(UNIX)
	install(TARGETS tailtale
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

	# Desktop entry
	install(FILES unix/tailtale.desktop
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
	install(FILES unix/tailtale.png
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pixmaps)
	install(FILES unix/tailtale.png
		DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/32x32/apps)

	# Game data / Themes
	file(GLOB GAMEDATA LIST_DIRECTORIES false data/*.png data/*.ogg data/*.wav)
	install(FILES ${GAMEDATA} DESTINATION ${DATA_PREFIX})
endif()
