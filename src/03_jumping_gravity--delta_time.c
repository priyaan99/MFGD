#include "raylib.h"
#include "raymath.h"

#define INIT_VELOCITY ((Vector2) {0, -300})

static const int screen_width = 256;
static const int screen_height= 256;

static Vector2 player_position;
static Vector2 player_velocity  = INIT_VELOCITY; 
static Vector2 player_gravity   = (Vector2) { 0.0, -200.0};
static const Vector2 UP_GRAVITY = (Vector2) { 0.0, 550.0};
static const Vector2 DOWN_GRAVITY   = (Vector2) { 0.0, 800.0};

static const int player_radius  = 20;
static bool is_player_jumping = true;

int main() {
    InitWindow(screen_width, screen_height, "Player Movement");
    SetTargetFPS(60);

    player_position = (Vector2) { screen_width*0.5f, 0+player_radius};

    // means 200 pixel per second (must multiply with delta time)
    const float SPEED = 200.0;

    while (!WindowShouldClose()) {
        // for real game like gravity
        if (player_velocity.y > 0.0) player_gravity = DOWN_GRAVITY;
        else player_gravity = UP_GRAVITY;

        player_position = Vector2Add(player_position, Vector2Scale(player_velocity, GetFrameTime()));
        player_velocity = Vector2Add(player_velocity, Vector2Scale(player_gravity, GetFrameTime()));

        if (player_position.y >= screen_height - player_radius - 5) is_player_jumping = false;
        else is_player_jumping = true;

        if (IsKeyPressed(KEY_SPACE) && !is_player_jumping)  {
            // reset velocity
            player_velocity = INIT_VELOCITY;
        }

        // stoping enemy from moving out of screen
        player_position = Vector2Clamp(
            player_position, 
            (Vector2){0+player_radius,0+player_radius},
            (Vector2){screen_width-player_radius, screen_height-player_radius}
        );

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(player_position, player_radius, BLUE);
        
        EndDrawing();
    }

    CloseWindow();

}
