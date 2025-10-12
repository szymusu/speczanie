cmake_minimum_required(VERSION 3.15)
project(speczanie)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(${PROJECT_NAME} main.c
        diagnostics/components/FpsCounter.c
        diagnostics/components/FpsCounter.h
        plot/components/Plot.c
        plot/components/Plot.h
        plot/components/ScatterPlot.c
        plot/components/ScatterPlot.h
        plot/plot_math.c
        plot/plot_math.h
        plot/components/SplinePlot.c
        plot/components/SplinePlot.h
        plot/components/Grid.c
        plot/components/Grid.h
        plot/components/DataPlot.c
        plot/components/DataPlot.h
        data/parse_binary.c
        data/parse_binary.h
        plot/move.c
        plot/move.h
        data/point_data.c
        data/point_data.h)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} m)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()