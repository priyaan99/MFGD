#include "raylib.h"
#include "raymath.h"

static int screen_width = 256;
static int screen_height= 256;

static Vector2 enemy_position;
static Vector2 player_position;
static const int enemy_radius   = 10;
static const int player_radius  = 10;

int main() {
    InitWindow(screen_width, screen_height, "Player Movement");
    SetTargetFPS(60);

    enemy_position = (Vector2) { screen_width*1.0f/2, screen_height*1.0f/2 };
    player_position= (Vector2) { 0+player_radius, 0+player_radius};

    // means 200 pixel per second (must multiply with delta time)
    const float ENEMY_SPEED = 200.0;
    const float PLAYER_SPEED= 100.0;

    while (!WindowShouldClose()) {
        // update
        if (IsKeyDown(KEY_W)) enemy_position.y -= ENEMY_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_S)) enemy_position.y += ENEMY_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_A)) enemy_position.x -= ENEMY_SPEED * GetFrameTime();
        if (IsKeyDown(KEY_D)) enemy_position.x += ENEMY_SPEED * GetFrameTime();

        // stoping enemy from moving out of screen
        enemy_position = Vector2Clamp(
            enemy_position, 
            (Vector2){0+enemy_radius,0+enemy_radius},
            (Vector2){screen_width-enemy_radius, screen_height-enemy_radius}
        );

        // Get direction to enemy form player
        Vector2 direction_to_enemy = Vector2Subtract(enemy_position, player_position); 

        // Normalize or convert Vector2 to unit length
        direction_to_enemy = Vector2Normalize(direction_to_enemy);
        
        // Scale unit vec to speed of player following enemy
        direction_to_enemy = Vector2Scale(direction_to_enemy, PLAYER_SPEED * GetFrameTime());

        // add direction scaled to player
        player_position = Vector2Add(player_position, direction_to_enemy);

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(enemy_position, enemy_radius, RED);
        DrawCircleV(player_position, player_radius, BLUE);
        
        EndDrawing();
    }

    CloseWindow();

}
