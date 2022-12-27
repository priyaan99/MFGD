#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

#define VEC(x, y) ((Vector2) {x, y})

static const int screen_width = 256;
static const int screen_height= 256;

static Vector2 enemy_position;
static Vector2 enemy_direction;
static Vector2 player_position;
static Vector2 player_direction;
static const int enemy_radius   = 15;
static const int player_radius  = 15;

static float dot_product;
static char str_dot_product[100];

static void init() {
    enemy_position = VEC(screen_width*1.0f/2, screen_height*1.0f/2);
    player_position= VEC(0+player_radius, 0+player_radius);

    enemy_direction = VEC(0.0, -1);
    player_direction= VEC(0.0, 1);

    dot_product = 0.0;
}

static void update() {
    // means 200 pixel per second (must multiply with delta time)
    const float SPEED = 200.0;
    if (IsKeyDown(KEY_W)) player_position.y -= SPEED * GetFrameTime();
    if (IsKeyDown(KEY_S)) player_position.y += SPEED * GetFrameTime();
    if (IsKeyDown(KEY_A)) player_position.x -= SPEED * GetFrameTime();
    if (IsKeyDown(KEY_D)) player_position.x += SPEED * GetFrameTime();

    // set player direction to mouse cursor
    player_direction = Vector2Normalize(Vector2Subtract(GetMousePosition(), player_position));

    // calculate the dot product for player to enemy
    // Dot product tells the relation of angle between two direction;
    //
    //  1   => Both vecs pointing to Same direction
    // -1   => Both vecs pointing to opposite direction
    // in-between => side and behind
    dot_product = Vector2DotProduct(player_direction, enemy_direction);

    // stoping enemy from moving out of screen
    player_position = Vector2Clamp(
        player_position, 
        (Vector2){0+player_radius,0+player_radius},
        (Vector2){screen_width-player_radius, screen_height-player_radius}
    );
}

static void draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    sprintf(&str_dot_product, "%.3f", dot_product);

    DrawText(str_dot_product, 100, 20, 22, RED);

    DrawCircleV(enemy_position, enemy_radius, RED);
    DrawLineEx(enemy_position, Vector2Add(enemy_position, Vector2Scale(enemy_direction, 30)), 5, RED);
    DrawCircleV(player_position, player_radius, BLUE);
    DrawLineEx(player_position, Vector2Add(player_position, Vector2Scale(player_direction, 30)), 5, BLUE);
    
    EndDrawing();
}

int main() {
    InitWindow(screen_width, screen_height, "Player Movement");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

}
