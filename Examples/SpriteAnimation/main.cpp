#include <raylib.h>
#include <iostream>
#include "Sprite.h"

using namespace std;

// Define screen width and height
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Sprite car;
#define SINGLE_CAR_WIDTH 16
#define ANIMATION_FPS 6

Sprite allFrames;

int main() 
{
    // Create Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sprite Animation");
    // Set Max FPS
    SetTargetFPS(90);

    // Set the exit key to none
    SetExitKey(KEY_NULL); // default is ESC

    // Load Car Sprite
    car = LoadSprite("resources/cars.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, 150 + (SCREEN_HEIGHT - 150) / 2}, 10);
    car.SetAnimation(SINGLE_CAR_WIDTH, car.texture.height);

    allFrames = LoadSprite("resources/cars.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, 100}, 5);

    // Main Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{50, 50, 50, 255});
        {
            // Update the animation
            car.AnimationUpdate(ANIMATION_FPS);

            // Draw sprites
            car.Draw();
            allFrames.Draw();

            // Draw FPS of the animation
            char text[50];
            sprintf(text, "FPS: %d", ANIMATION_FPS);
            DrawText(text, 10, 10, 30, RAYWHITE);
        }
        EndDrawing();
    }

    // Cleanup
    car.Delete();
    CloseWindow();

    return 0;
}