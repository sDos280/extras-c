/*******************************************************************************************
*
*   raylib [core] example - First Person Orbit Camera Example
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "rlFPCamera.h"
#include "rlgl.h"

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1900;
    int screenHeight = 900;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib-extras [camera] example - First person camera");
    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------
    Image img = GenImageChecked(256, 256, 32, 32, DARKGRAY, WHITE);
    Texture tx = LoadTextureFromImage(img);
    UnloadImage(img);
    SetTextureFilter(tx, TEXTURE_FILTER_ANISOTROPIC_16X);
    SetTextureWrap(tx, TEXTURE_WRAP_CLAMP);

    // setup initial camera data
    rlFPCamera cam;
    rlFPCameraInit(&cam, 45, (Vector3) { 1, 0, 0 });
    cam.MoveSpeed.z = 10;
    cam.MoveSpeed.x = 5;

    cam.FarPlane = 5000;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (IsKeyPressed(KEY_F1))
            cam.AllowFlight = !cam.AllowFlight;

        rlFPCameraUpdate(&cam);
        BeginDrawing();
        ClearBackground(SKYBLUE);

        rlFPCameraBeginMode3D(&cam);

        // grid of cube trees on a plane to make a "world"
        DrawPlane((Vector3) { 0, 0, 0 }, (Vector2) { 50, 50 }, BEIGE); // simple world plane
        float spacing = 4;
        int count = 5;

        for (float x = -count * spacing; x <= count * spacing; x += spacing)
        {
            for (float z = -count * spacing; z <= count * spacing; z += spacing)
            {
                DrawCubeTexture(tx, (Vector3) { x, 1.5f, z }, 1, 1, 1, GREEN);
                DrawCubeTexture(tx, (Vector3) { x, 0.5f, z }, 0.25f, 1, 0.25f, BROWN);
            }
        }

        rlFPCameraEndMode3D();

        if (cam.AllowFlight)
            DrawText("(F1) Flight", 2, 20, 20, BLACK);
        else
            DrawText("(F1) Running", 2, 20, 20, BLACK);
        // instructions
        DrawFPS(0, 0);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
