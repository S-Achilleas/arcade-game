cmake_minimum_required(VERSION 3.29)
project(my_project)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Set the output directories for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Add the executable target
add_executable(my_project
        source/main.cpp            # Main source file
        include/sgg/graphics.h     # Headers in include/sgg
        include/sgg/scancodes.h
        include/box.h              # Headers in include/
        include/gameobject.h
        include/gamestate.h
        source/gamestate.cpp
        include/player.h
        include/level.h
        include/my_stdio.h
        source/player.cpp
        source/gameobject.cpp
        source/level.cpp
        # Additional headers (if in the root directory)

)

# Add include directories
target_include_directories(my_project PRIVATE
        ${CMAKE_SOURCE_DIR}/include                # Project-specific headers
        /opt/homebrew/Cellar/freetype/2.13.3/include/freetype2
        /opt/homebrew/Cellar/sdl2/2.30.9/include
        /opt/homebrew/Cellar/sdl2_mixer/2.8.0/include
        /opt/homebrew/Cellar/glew/2.2.0_1/include
        /opt/homebrew/Cellar/glm/1.0.1/include     # GLM is header-only
)

# Add library directories
target_link_directories(my_project PRIVATE
        ${CMAKE_SOURCE_DIR}/lib                    # Project-specific libraries
        /opt/homebrew/Cellar/freetype/2.13.3/lib
        /opt/homebrew/Cellar/sdl2/2.30.9/lib
        /opt/homebrew/Cellar/sdl2_mixer/2.8.0/lib
        /opt/homebrew/Cellar/glew/2.2.0_1/lib
)

# Link libraries
target_link_libraries(my_project PRIVATE
        freetype                                   # FreeType library
        SDL2                                       # SDL2 library
        SDL2_mixer                                 # SDL2_mixer library
        GLEW                                       # GLEW library
        "-framework OpenGL"                        # OpenGL framework for macOS
)

# Link the appropriate project library (Debug vs Release)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(my_project PRIVATE sggd)   # Debug version of project library
else()
    target_link_libraries(my_project PRIVATE sgg)    # Release version of project library
endif()

# Set the working directory for debugging
set_target_properties(my_project PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

