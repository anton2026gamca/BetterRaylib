#include <raylib.h>
#include "Sprite.h"
#include "Shapes.h"
#include "Helpers.h"

// Define screen width and height
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main()
{
    // Create Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "UI in Raylib");
    // Set Max FPS
    SetTargetFPS(60);

    // Set the exit key to none
    SetExitKey(KEY_NULL); // default is ESC

    float uiy = 10;
    Rectangle rects[3];

    // Button
    rects[0] = {10, uiy, 400, 30};
    uiy += rects[0].height + 10;
    
    // Toggle
    rects[1] = {10, uiy, 400, 30};
    bool toggle = false;
    uiy += rects[1].height + 10;

    // Slider
    rects[2] = {10, uiy, 400, 60};
    uiy += rects[2].height + 10;
    Slider slider = Slider(rects[2], 0, SCREEN_WIDTH - rects[0].width - 20, 0, DARKGRAY, RAYWHITE, BLUE, RED, true, "Slider", 30);

    // Main Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        {
            if (Button(rects[0], "Button", 30, DARKGRAY, BLUE, RED))
            {
                /* Button is pressed */
                DrawText("Ouch!", SCREEN_WIDTH / 2, 500, 60, 0.5, RAYWHITE);
            }
            toggle = Toggle(toggle, rects[1], "Toggle", 30, DARKGRAY, BLUE, RED);
            if (toggle)
            {
                /* toggle is true */
                slider.Draw();
            }

            rects[0].x = 10 + slider.value;
            rects[1].x = 10 + slider.value;
        }
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}