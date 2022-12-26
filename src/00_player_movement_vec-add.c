#include "raylib.h"
#include "raymath.h"

static int screen_width = 256;
static int screen_height= 256;

static Vector2 player_position;
static int player_radius;

int main() {
    InitWindow(screen_width, screen_height, "Player Movement");
    SetTargetFPS(60);

    player_position = (Vector2) { screen_width*1.0f/2, screen_height*1.0f/2 };
    player_radius = 10;

    // means 200 pixel per second (must multiply with delta time)
    const float SPEED = 200.0;

    while (!WindowShouldClose()) {
        // update
        if (IsKeyDown(KEY_W)) player_position.y -= SPEED * GetFrameTime();
        if (IsKeyDown(KEY_S)) player_position.y += SPEED * GetFrameTime();
        if (IsKeyDown(KEY_A)) player_position.x -= SPEED * GetFrameTime();
        if (IsKeyDown(KEY_D)) player_position.x += SPEED * GetFrameTime();

        // stoping player from moving out of screen
        player_position = Vector2Clamp(
            player_position, 
            (Vector2){0+player_radius,0+player_radius},
            (Vector2){screen_width-player_radius, screen_height-player_radius}
        );

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(player_position, player_radius, RED);
        
        EndDrawing();
    }

    CloseWindow();

}
