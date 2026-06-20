#include "raylib.h"

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

typedef struct Panel
{
  float x, y;             // top-left origin of the panel, in screen pixels
  float width;            // "my_width" in the article
  float height;           // "my_height" — you'll compute this
  float ypad;             // vertical padding
  float character_height; // stand-in for body_font->character_height
} Panel;

typedef struct Panel_Layout
{
  float width;
  float row_height;
  float at_x;
  float at_y;
  float top_y;
} Panel_Layout;

void panel_layout_init(
    Panel_Layout *pl, Panel *panel, float left_x, float top_y, float width)
{
  pl->row_height = panel->ypad + 1.2 * panel->character_height;
  pl->at_x       = left_x;
  pl->at_y       = top_y;
  pl->top_y      = top_y;
}

void panel_layout_row(Panel_Layout *pl) { pl->at_y += pl->row_height; }

void panel_layout_window_title(Panel_Layout *pl, char *title)
{
  float title_height = draw_title(pl->at_x, pl->at_y, title);
  pl->at_y += title_height;
}

void panel_layout_complete(Panel_Layout *pl, Panel *panel)
{
  panel->height = pl->top_y - pl->at_y;
}

void panel_layout_push_button(Panel_Layout *pl, char *text)
{
  bool result = draw_big_text_button(
      pl->at_x, pl->at_y, pl->width, pl->row_height, "text");
}

static void render_panel(Panel *panel)
{
  Panel_Layout layout;
  panel_layout_init(&layout, panel, panel->x, panel->y, panel->width);
  panel_layout_window_title(&layout, "Title");

  panel_layout_row(&layout);
  panel_layout_push_button(&layout, "Auto Snap");

  panel_layout_row(&layout);
  panel_layout_push_button(&layout, "Reset Orientation");

  panel_layout_complete(&layout, panel);
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
