#include <raylib.h>

int main() {
    InitWindow(300, 300, "Raylib");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        DrawRectangle(20, 20, 80, 40, BLACK);
        DrawText("Text", 20, 20, 25, WHITE);

        EndDrawing();
    }
}