#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include <stdio.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
bool is_running = false;

void setup() {}

void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
    }
  }
}

void render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void update() {}

bool initialize_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL.\n");
    return false;
  }

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       600, 600, SDL_WINDOW_BORDERLESS);

  if (!window) {
    fprintf(stderr, "Error creating SDL window");
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    fprintf(stderr, "Error creating SDL renderer.\n");
    return false;
  }

  return true;
};

int main(int argc, char *argv[]) {
  // TODO: Create SDL Window
  is_running = initialize_window();

  setup();

  while (is_running) {
    process_input();
    update();
    render();
  }
  return 0;
}
