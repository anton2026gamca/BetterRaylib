// IMPORTANT: GetSpritePixelCollision() does NOT work with rotation and scale for now

#include <raylib.h>
#include "Sprite.h"
#include "Helpers.h"
#include <iostream>

using namespace std;

// Define screen width and height
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Sprite car;
Sprite someObject;

int main()
{
    // Create Window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My first RAYLIB program!");
    // Set Max FPS
    SetTargetFPS(60);

    // Set the exit key to none
    SetExitKey(KEY_NULL); // default is ESC

    // Load Car Sprite and Create Collision Mask Texture
    car = LoadSprite("resources/car.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 5);
    car.CreateCollisionMaskTexture();

    // Load SomeObject Sprite and Create Collision Mask Texture
    someObject = LoadSprite("resources/rectangle.png", Vector2{0.5, 0.5}, Vector2{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, 5);
    someObject.CreateCollisionMaskTexture();

    // Toggle rectangle for 'debugDraw'
    Rectangle tglRect = Rectangle{10, 60, 400, 30};

    // Slider for Car scale
    Rectangle sldrRect = Rectangle{10, 100, 400, 75};
    Slider carScaleSldr = Slider(sldrRect, 5, 20, 5, GRAY, LIGHTGRAY, BLUE, RED, "Car Scale: ", 30);
    sldrRect = Rectangle{10, 185, 400, 75};
    Slider carRotationSldr = Slider(sldrRect, 0, 360, 0, GRAY, LIGHTGRAY, BLUE, RED, "Car Rotation: ", 30);

    // Slider for Some Object scale
    sldrRect = Rectangle{10, 270, 400, 75};
    Slider someObjectScaleSldr = Slider(sldrRect, 5, 20, 5, GRAY, LIGHTGRAY, BLUE, RED, "Rec. Scale: ", 30);

    // Draw rules
    bool debugDraw = true;

    // Main Loop
    while (!WindowShouldClose())
    {
        // Rotate Car
        if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
        {
            carRotationSldr.value -= 250 * GetFrameTime();
        }
        else if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
        {
            carRotationSldr.value += 250 * GetFrameTime();
        }

        // Set Some Object's position to mouse position
        someObject.position = GetMousePosition();

        BeginDrawing();
        ClearBackground(Color{75, 75, 75, 255});
        {
            // Draw Sprites Debug Rectangles if enabled
            if (debugDraw)
            {
                car.DrawDebugRects(BLACK, GRAY);
                someObject.DrawDebugRects(BLACK, GRAY);
            }

            // Draw Sprites
            car.Draw();
            someObject.Draw();

            // Draw sprites collision masks if enabled
            if (debugDraw)
            {
                car.DrawCollisionMask();
                someObject.DrawCollisionMask();
            }
            
            // Draw top panel
            if (GetSpritePixelCollision(&car, &someObject, debugDraw))
            {
                DrawRectangle(0, 0, SCREEN_WIDTH, 50, RED);
                DrawText("COLLISION!", SCREEN_WIDTH / 2 - MeasureText("COLLISION!", 40 / 2), 10, 40, RAYWHITE);
            }
            else
            {
                DrawRectangle(0, 0, SCREEN_WIDTH, 50, BLACK);
            }

            // Draw toggle
            debugDraw = Toggle(debugDraw, tglRect, "Debug Draw", 30, GRAY, BLUE, RED);

            // Draw Sliders
            carScaleSldr.Draw();
            car.scale = carScaleSldr.value;

            carRotationSldr.Draw();
            car.rotation = carRotationSldr.value;

            someObjectScaleSldr.Draw();
            someObject.scale = someObjectScaleSldr.value;
        }
        EndDrawing();
    }

    // Delete Sprites
    car.Delete();
    someObject.Delete();

    CloseWindow();
    return 0;
}