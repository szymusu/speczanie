cmake_minimum_required(VERSION 3.15)
project(speczanie)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(${PROJECT_NAME} main.c
        diagnostics/components/FpsCounter.c
        diagnostics/components/FpsCounter.h
        plot/plot_math.c
        plot/plot_math.h
        plot/components/Grid.c
        plot/components/Grid.h
        plot/components/DataPlot.c
        plot/components/DataPlot.h
        data/parse_binary.c
        data/parse_binary.h
        plot/move.c
        plot/move.h
        data/point_data.c
        data/point_data.h
        diagnostics/more_data.c
        diagnostics/more_data.h
        text/text.c
        text/text.h
        diagnostics/components/Clock.c
        diagnostics/components/Clock.h
        data/data_source.h
        data/data_source.c
        plot/components/PointHoverTooltip.c
        plot/components/PointHoverTooltip.h
        text/TextBox.c
        text/TextBox.h
        text/Button.c
        text/Button.h
        math/vector2.c
        math/vector2.h
        plot/components/Arrow.c
        plot/components/Arrow.h
        state/state.c
        state/state.h
        files/components/FileList.c
        files/components/FileList.h
        files/open_files.c
        files/open_files.h
        plot/components/Controls.c
        plot/components/Controls.h
        args/args.c
        args/args.h
        plot/components/Line.c
        plot/components/Line.h
        plot/components/Polynomial.c
        plot/components/Polynomial.h
        math/regression.c
        math/regression.h
        diagnostics/components/BenchmarkProgress.c
        diagnostics/components/BenchmarkProgress.h
        util/swapback_array.c
        util/swapback_array.h
        util/string.c
        util/string.h
        math/line.c
        math/line.h
        data/parse_csv.c
        data/parse_csv.h
        plot/components/Axes.c
        plot/components/Axes.h
        files/components/CloseButton.c
        files/components/CloseButton.h
        files/image_export.c
        files/image_export.h
        files/components/ColumnImport.c
        files/components/ColumnImport.h
        plot/components/MultiPlot.c
        plot/components/MultiPlot.h
        plot/components/LineSetZero.c
        plot/components/LineSetZero.h
        data/operations/data_operation.c
        data/operations/data_operation.h
        data/operations/op_cut_left.c
        data/operations/op_cut_left.h
        data/operations/op_cut_right.c
        data/operations/op_cut_right.h
        data/operations/op_flip_y.c
        data/operations/op_flip_y.h
        data/operations/op_flip_x.c
        data/operations/op_flip_x.h
        data/operations/op_offset.c
        data/operations/op_offset.h
        data/operations/op_replace.c
        data/operations/op_replace.h
)

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} m)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()