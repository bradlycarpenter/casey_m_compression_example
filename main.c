#include "raylib.h"

typedef struct Panel
{
  float x, y;             // top-left origin of the panel, in screen pixels
  float width;            // "my_width" in the article
  float height;           // "my_height" — you'll compute this
  float ypad;             // vertical padding
  float character_height; // stand-in for body_font->character_height
} Panel;

static float draw_title(float x, float y, const char *title)
{
  int font = 20;
  DrawText(title, (int)x + 6, (int)y + 4, font, DARKGRAY);
  float h = font + 10;
  DrawLine((int)x, (int)(y + h), (int)x + 220, (int)(y + h), LIGHTGRAY);
  return h;
}

static bool
draw_big_text_button(float x, float y, float w, float h, const char *label)
{
  Rectangle r     = {x, y, w, h};
  Vector2   m     = GetMousePosition();
  bool      hover = CheckCollisionPointRec(m, r);
  bool      held  = hover && IsMouseButtonDown(MOUSE_BUTTON_LEFT);
  bool      click = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

  Color fill = held ? GRAY : (hover ? LIGHTGRAY : (Color){225, 225, 225, 255});
  DrawRectangleRec(r, fill);
  DrawRectangleLinesEx(r, 1, DARKGRAY);

  int font = 20;
  int tw   = MeasureText(label, font);
  DrawText(
      label, (int)(x + (w - tw) / 2), (int)(y + (h - font) / 2), font, BLACK);
  return click;
}

static void render_panel(Panel *panel)
{
  int   num_categories  = 4;
  int   category_height = panel->ypad + 1.2 * panel->character_height;
  float x0              = panel->x;
  float y0              = panel->y;
  float title_height    = draw_title(x0, y0, "Title");
  float height  = title_height + num_categories * category_height + panel->ypad;
  panel->height = height;
  y0 += title_height;

  {
    y0 += category_height;
    char *string = "Auto Snap";
    bool  pressed =
        draw_big_text_button(x0, y0, panel->width, category_height, string);
  }
}

int main(void)
{
  InitWindow(480, 360, "semantic compression demo");
  SetTargetFPS(60);

  Panel panel = {
      .x                = 40,
      .y                = 40,
      .width            = 220,
      .height           = 0,
      .ypad             = 6,
      .character_height = 18,
  };

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    render_panel(&panel);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
