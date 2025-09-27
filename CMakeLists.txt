cmake_minimum_required(VERSION 3.15)
project(speczanie)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(${PROJECT_NAME} main.c
        diagnostics/components/fps.c
        diagnostics/components/fps.h
        plot/components/plot.c
        plot/components/plot.h
        plot/components/ScatterPlot.c
        plot/components/ScatterPlot.h
        plot/plot_math.c
        plot/plot_math.h
        plot/components/SplinePlot.c
        plot/components/SplinePlot.h)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()