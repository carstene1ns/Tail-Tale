# Set CMake compat
cmake_minimum_required(VERSION 3.18...4.0)

# Define the metadata
project(Tail-Tale
	VERSION 1.0.3
	DESCRIPTION ""
	HOMEPAGE_URL ""
	LANGUAGES C)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to 'RelWithDebInfo' as none was specified.")
	set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
		"MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_C_STANDARD 99)

# Get the dependency libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

# Define the source files
add_executable(tailtale WIN32
	src/bootmain.c src/bootmain.h
	src/debug.c src/debug.h
	src/gamemain.c src/gamemain.h
	src/grp_screen.c src/grp_screen.h
	src/grp_sprite.c src/grp_sprite.h
	src/input.c src/input.h
	src/puz_res.h
	src/puz_base.c src/puz_base.h
	src/puz_disp.c src/puz_disp.h
	src/puz_trial.c src/puz_trial.h
	src/sound.c src/sound.h)

# Game data
if(UNIX)
	include(GNUInstallDirs)
	set(DEFAULT_PREFIX "${CMAKE_INSTALL_DATAROOTDIR}/tailtale")
else()
	set(DEFAULT_PREFIX "data")
endif()
set(DATA_PREFIX "${DEFAULT_PREFIX}/" CACHE PATH "Where game data is located")

# Define the compilation flags
target_compile_options(tailtale PRIVATE -Wall)
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
	SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2::SDL2)
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
