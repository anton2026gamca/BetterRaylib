#include <raylib.h>
#include "Sprite.h"
#include "Shapes.h"
#include "Helpers.h"

// Define screen width and height
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Sprite car;

int main()
{
    // Create Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first RAYLIB program!");
    // Set Max FPS
    SetTargetFPS(60);

    // Set the exit key to none
    SetExitKey(KEY_NULL); // default is ESC

    // Load Car Sprite
    car = LoadSprite("resources/car.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 5);

    // Main Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        {
            // Move car
            car.position.y -= 200 * GetFrameTime();
            if (car.position.y < 0 - car.GetHeight())
                car.position.y = SCREEN_HEIGHT + car.GetHeight();

            // Draw Car Sprite
            car.Draw();
        }
        EndDrawing();
    }

    // Cleanup
    car.Delete();
    CloseWindow();
    return 0;
}