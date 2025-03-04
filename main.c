#include <raylib.h>

int main() {
  InitWindow(320, 180, "Mochi");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
