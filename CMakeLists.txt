cmake_minimum_required(VERSION 3.21)
project(DeMandelbrot)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/CImg-3.0.0"
        )

add_executable(DeMandelbrot
        app/App.cpp
        source/Mandelbrot/Mandelbrot.cpp include/Mandelbrot/Mandelbrot.hpp
        source/ImageIO/PixelMatrix.cpp include/ImageIO/PixelMatrix.hpp
        source/ImageIO/InputParser.cpp include/ImageIO/InputParser.hpp
        include/ImageIO/ImageIOTypes.hpp
        include/ImageIO.hpp
        source/ImageIO/Utility.cpp include/ImageIO/Utility.hpp
        source/Swarm/Swarm.cpp include/Swarm/Swarm.hpp
        source/Swarm/Agent.cpp include/Swarm/Agent.hpp
        include/Swarm/SwarmTypes.hpp
        source/Swarm/GeneratorHelper.cpp include/Swarm/GeneratorHelper.hpp
        include/GlobalParameters.hpp)

target_include_directories(DeMandelbrot PUBLIC ${INCLUDE_DIRS})
