#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL.h>
#include <stdbool.h>
#include <stdint.h>

#define FPS 60
// how many millisecs we need per second to achieve 30 FPS
#define FRAME_TARGET_TIME (1000/FPS)

extern int window_width;
extern int window_height;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

bool initialize_window(void);
void draw_grid(int multiple);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void clear_color_buffer(uint32_t color);
void render_color_buffer();
void destroy_window();
void draw_pixel(int x, int y, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);

#endif //DISPLAY_H
