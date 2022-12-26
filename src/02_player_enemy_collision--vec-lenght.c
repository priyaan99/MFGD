#include "raylib.h"
#include "raymath.h"

static const int screen_width = 256;
static const int screen_height= 256;

static Vector2 enemy_position;
static Vector2 player_position;
static const int enemy_radius   = 40;
static const int player_radius  = 20;

static bool collided;

int main() {
    InitWindow(screen_width, screen_height, "Player Movement");
    SetTargetFPS(60);

    enemy_position = (Vector2) { screen_width*1.0f/2, screen_height*1.0f/2 };
    player_position= (Vector2) { 0+player_radius, 0+player_radius};

    collided = false;

    // means 200 pixel per second (must multiply with delta time)
    const float SPEED = 200.0;

    while (!WindowShouldClose()) {
        // update
        if (IsKeyDown(KEY_W)) player_position.y -= SPEED * GetFrameTime();
        if (IsKeyDown(KEY_S)) player_position.y += SPEED * GetFrameTime();
        if (IsKeyDown(KEY_A)) player_position.x -= SPEED * GetFrameTime();
        if (IsKeyDown(KEY_D)) player_position.x += SPEED * GetFrameTime();

        // stoping enemy from moving out of screen
        player_position = Vector2Clamp(
            player_position, 
            (Vector2){0+player_radius,0+player_radius},
            (Vector2){screen_width-player_radius, screen_height-player_radius}
        );


        int radius_sum = player_radius + enemy_radius;
        if (Vector2DistanceSqr(player_position, enemy_position) <= (radius_sum * radius_sum)) {
            collided = true;
        } else {
            collided = false;
        }

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(enemy_position, enemy_radius, RED);
        DrawCircleV(player_position, player_radius, collided ? BLUE : GREEN);
        
        EndDrawing();
    }

    CloseWindow();

}
