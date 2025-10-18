cmake_minimum_required(VERSION 3.15)
project(CameraShake LANGUAGES CXX)

# ------------------------------------------------------------------------------
# C++ standard setup
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------------------
# Collect all sources and headers
# ------------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/srcs/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/includes/*.hpp" "${CMAKE_SOURCE_DIR}/includes/*.h")

# ------------------------------------------------------------------------------
# Find or set up SFML
# ------------------------------------------------------------------------------
# If SFML is installed system-wide (Linux/macOS, vcpkg on Windows), this works:
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

# ------------------------------------------------------------------------------
# Create executable
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Copy the images directory to the runtime folder after building
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/images"
)

# Add include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/includes)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        sfml-network
)

# ------------------------------------------------------------------------------
# Platform-specific settings
# ------------------------------------------------------------------------------

# Set Windows-specific compiler flags and output name
if(WIN32)
    # Output .exe to bin folder
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        OUTPUT_NAME "${PROJECT_NAME}"
    )

    # Suppress some Visual Studio warnings
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /W3 /EHsc)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
    endif()

    # Copy SFML DLLs automatically after build (if found)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-audio>
            $<TARGET_FILE:sfml-network>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
else()
    # Linux/macOS output setup
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wextra)
endif()

# ------------------------------------------------------------------------------
# Optional: set default build type (Release or Debug)
# ------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
endif()
