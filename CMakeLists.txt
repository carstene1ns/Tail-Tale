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

set(CMAKE_C_STANDARD 90)

# Get the dependency libraries
find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_image REQUIRED)

# Define the source files
add_executable(tailtale WIN32
	src/bootmain.c src/bootmain.h
	src/debug.c src/debug.h
	src/gamemain.c src/gamemain.h
	#src/gp2x_grp_screen.c
	src/grp_screen.c src/grp_screen.h
	src/grp_sprite.c src/grp_sprite.h
	src/grp_table.h
	src/grp_table_int.h
	src/grp_texture.c src/grp_texture.h
	src/input.c src/input.h
	#src/psp_debug.c
	#src/psp_grp_screen.c
	src/puz_base.c src/puz_base.h
	src/puz_disp.c src/puz_disp.h
	src/puz_trial.c src/puz_trial.h
	src/sound.c src/sound.h)

# Define the compilation flags
target_compile_options(tailtale PRIVATE -Wall)
target_compile_definitions(tailtale PRIVATE NOTPSP __GP2X_SCREEN__)
option(DEBUG_LOG "Print debug message" OFF)
if(DEBUG_LOG)
	target_compile_definitions(tailtale PRIVATE DEBUG)
endif()

# Link the dependencies
target_include_directories(tailtale PRIVATE
	${SDL_IMAGE_INCLUDE_DIRS} ${SDL_MIXER_INCLUDE_DIRS} ${SDL_INCLUDE_DIRS})
target_link_libraries(tailtale PRIVATE
	${SDL_IMAGE_LIBRARIES} ${SDL_MIXER_LIBRARIES} ${SDL_LIBRARIES})
if(UNIX)
	target_link_libraries(tailtale PRIVATE m)
endif()
