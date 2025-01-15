#include <raylib.h>
#define BETTER_RAYLIB_IMPLEMENTATION
#include "better_raylib.h"

// Define screen width and height
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Sprite sprite1;
Sprite sprite2;

int main()
{
    // Create Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sprite Collision");
    // Set Max FPS
    SetTargetFPS(60);

    // Set the exit key to none
    SetExitKey(KEY_NULL); // default is ESC

    // Load sprites
    sprite1 = LoadSprite("resources/sprite1.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 2);
    sprite2 = LoadSprite("resources/sprite2.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 2);

    Vector2 dir = {1, 1};

    // Main Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        {
            const float delta_time = GetFrameTime();

            // Move sprites
            sprite1.position.x += 200 * delta_time * dir.x;
            sprite1.position.y += 200 * delta_time * dir.y;
            if (sprite1.position.x - sprite1.GetWidth() / 2 < 0) // Check if bounced left
                dir.x = 1;
            else if (sprite1.position.x + sprite1.GetWidth() / 2 > SCREEN_WIDTH) // Check if bounced right
                dir.x = -1;
            if (sprite1.position.y - sprite1.GetHeight() / 2 < 0) // Check if bounced top
                dir.y = 1;
            else if (sprite1.position.y + sprite1.GetHeight() / 2 > SCREEN_HEIGHT) // Check if bounced bottom
                dir.y = -1;

            sprite2.position = GetMousePosition();
            sprite2.rotation += 100 * delta_time;

            // Draw top panel
            if (GetSpriteCollision(&sprite1, &sprite2)) // Draw RED if the sprites collided
            {
                DrawRectangle(0, 0, SCREEN_WIDTH, 30, RED);
                DrawText("COLLISION!", SCREEN_WIDTH / 2, 3, 30, 0.5, RAYWHITE);
            }
            else // Draw BLACK if not
            {
                DrawRectangle(0, 0, SCREEN_WIDTH, 30, BLACK);
            }

            // Draw Sprites
            sprite1.Draw();
            sprite2.Draw();
        }
        EndDrawing();
    }

    // Cleanup
    sprite1.Delete();
    CloseWindow();
    return 0;
}