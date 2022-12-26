#include "raylib.h"
#include "raymath.h"

#define VEC(x, y) ((Vector2) {x, y})

static const int screen_width = 256;
static const int screen_height= 256;

static Vector2 player_position;
static Vector2 player_velocity; // current velocity
static Vector2 player_goal_velocity; // velocity to achive
static const float SPEED = 250.0f;
static const int player_radius  = 20;

static void init() {
    player_position = (Vector2) { screen_width*0.5f, screen_height*0.5f};
    player_velocity = VEC(0.0, 0.0);
}

static void update() {
    if (IsKeyDown(KEY_W)) player_goal_velocity      = VEC(0.0, -SPEED);
    else if (IsKeyDown(KEY_S)) player_goal_velocity = VEC(0.0, SPEED);
    else if (IsKeyDown(KEY_A)) player_goal_velocity = VEC(-SPEED, 0.0);
    else if (IsKeyDown(KEY_D)) player_goal_velocity = VEC(SPEED, 0.0);
    else player_goal_velocity = VEC(0.0, 0.0);

    player_velocity = Vector2Lerp(player_velocity, player_goal_velocity, 5.0 * GetFrameTime());
    player_position = Vector2Add(player_position, Vector2Scale(player_velocity, GetFrameTime()));

    // stoping enemy from moving out of screen
    player_position = Vector2Clamp( player_position, 
        (Vector2){0+player_radius,0+player_radius},
        (Vector2){screen_width-player_radius, screen_height-player_radius}
    );
}

static void draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawCircleV(player_position, player_radius, BLUE);
    
    EndDrawing();
}

int main() {
    InitWindow(screen_width, screen_height, "Player Movement");
    SetTargetFPS(95);

    init();

    while (!WindowShouldClose()) {
        update();
        draw();
    }

    CloseWindow();

}
