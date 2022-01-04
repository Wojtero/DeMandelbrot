cmake_minimum_required(VERSION 3.21)
project(DeMandelbrot)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/CImg-3.0.0"
        )

add_executable(DeMandelbrot
        app/App.cpp
        source/Mandelbrot.cpp include/Mandelbrot.hpp
        source/ImageIO/PixelMatrix.cpp include/ImageIO/PixelMatrix.hpp
        source/ImageIO/InputParser.cpp include/ImageIO/InputParser.hpp
        include/ImageIO/ImageIOTypes.hpp
        include/ImageIO.hpp
        source/ImageIO/Utility.cpp include/ImageIO/Utility.hpp
        source/Swarm.cpp include/Swarm.hpp
        source/Agent.cpp include/Agent.hpp
        include/SwarmTypes.hpp
        include/GeneratorHelper.hpp source/GeneratorHelper.cpp)

target_include_directories(DeMandelbrot PUBLIC ${INCLUDE_DIRS})
