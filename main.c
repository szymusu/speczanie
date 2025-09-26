#include <stdio.h>

#include "raylib.h"

int main() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Yay window werks!", 100, 100, 20, (Color){0x99, 0x11, 0x11, 0xff});

        EndDrawing();
    }
    CloseWindow();
}