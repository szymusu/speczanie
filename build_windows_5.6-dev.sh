i686-w64-mingw32-gcc main.c \
    args/*.c \
    data/*.c data/operations/*.c \
    diagnostics/*.c diagnostics/components/*.c \
    files/*.c files/components/*.c \
    math/*.c \
    plot/*.c plot/components/*.c \
    text/*.c \
    util/*.c \
    -O3 \
    -o ./build/speczanie.exe \
    /home/_m/code/raylib/cmake-build-release/raylib/libraylib.a \
    -I/home/_m/code/raylib/cmake-build-release/raylib/include \
    -static -static-libgcc \
    -D_WIN32_WINNT=0x0501 \
    -lopengl32 -lmsvcrt -lwinmm -lgdi32 --std=c11 \

objdump -x ./build/speczanie.exe | grep 'DLL Name'
