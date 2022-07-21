cmake_minimum_required(VERSION 3.22)
project(FaceEngine VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_TESTS "Build Face Engine tests" OFF)

find_package(ZLIB 1.2.12 EXACT REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(OpenAL REQUIRED)

set(FACE_ENGINE_HEADER_FILES
    include/glad/glad.h
    include/KHR/khrplatform.h

    include/FaceEngine/AudioDevice.h
    include/FaceEngine/ContentLoader.h
    include/FaceEngine/Display.h
    include/FaceEngine/Exception.h
    include/FaceEngine/Game.h
    include/FaceEngine/GameDraw.h
    include/FaceEngine/GameUpdate.h
    include/FaceEngine/GraphicsDevice.h
    include/FaceEngine/OGL.h
    include/FaceEngine/Resolution.h
    include/FaceEngine/Resource.h
    include/FaceEngine/ResourceManager.h
    include/FaceEngine/TypingSession.h
    include/FaceEngine/Window.h

    include/FaceEngine/Graphics/Colour.h
    include/FaceEngine/Graphics/Shader.h
    include/FaceEngine/Graphics/SpriteBatcher.h
    include/FaceEngine/Graphics/Texture2D.h
    include/FaceEngine/Graphics/TextureFont.h

    include/FaceEngine/Math/Calculator.h
    include/FaceEngine/Math/Matrix.h
    include/FaceEngine/Math/Matrix3f.h
    include/FaceEngine/Math/Matrix4f.h
    include/FaceEngine/Math/Vector.h
    include/FaceEngine/Math/Vector2.h
    include/FaceEngine/Math/Vector3.h
    include/FaceEngine/Math/Vector4.h
    include/FaceEngine/Math/Rectangle.h
    include/FaceEngine/Math/Circle.h
)

set(FACE_ENGINE_SRC_FILES
    src/AudioDevice.cpp
    src/ContentLoader.cpp
    src/Game.cpp
    src/GameUpdate.cpp
    src/GLAD.cpp
    src/GraphicsDevice.cpp
    src/Resolution.cpp
    src/Resource.cpp
    src/ResourceManager.cpp
    src/TypingSession.cpp
    src/Window.cpp

    src/Graphics/Colour.cpp
    src/Graphics/Shader.cpp
    src/Graphics/SpriteBatcher.cpp
    src/Graphics/Texture2D.cpp
    src/Graphics/TextureFont.cpp

    src/Math/Calculator.cpp
    src/Math/Matrix.cpp
    src/Math/Matrix3f.cpp
    src/Math/Matrix4f.cpp
    src/Math/Vector.cpp
    src/Math/Rectangle.cpp
    src/Math/Circle.cpp
)

add_library(FaceEngine STATIC ${FACE_ENGINE_SRC_FILES})
target_compile_options(FaceEngine PRIVATE -O3)
target_include_directories(FaceEngine PRIVATE include "${OPENAL_INCLUDE_DIR}" "${GLFW_INCLUDE_DIRS}" "${ZLIB_INCLUDE_DIRS}")
target_link_libraries(FaceEngine PRIVATE "${OPENAL_LIBRARY}" "${ZLIB_LIBRARIES}" glfw)

if (BUILD_TESTS)
    add_executable(FaceEngineMathTests ${FACE_ENGINE_SRC_FILES} tests/MathTests.cpp)
    target_compile_options(FaceEngineMathTests PRIVATE -O3)
    target_include_directories(FaceEngineMathTests PRIVATE include "${OPENAL_INCLUDE_DIR}" "${GLFW_INCLUDE_DIRS}" "${ZLIB_INCLUDE_DIRS}")
    target_link_libraries(FaceEngineMathTests PRIVATE "${OPENAL_LIBRARY}" "${ZLIB_LIBRARIES}" glfw)
endif()