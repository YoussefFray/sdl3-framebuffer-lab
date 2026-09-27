
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>
#include <cstdint>

const int WIDTH = 320;
const int HEIGHT = 240;

std::vector<uint32_t> pixels(WIDTH * HEIGHT);

void putPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b)
{
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
        return;
    }
    uint32_t color = (0xFFu << 24) | (r << 16) | (g << 8) | b;
    pixels[y * WIDTH + x] = color;
}

void drawFrame(double time)
{
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            uint8_t r = (uint8_t)(x + time * 40.0);
            uint8_t g = (uint8_t)(y + time * 20.0);
            uint8_t b = (uint8_t)((x + y) / 2 + time * 60.0);
            putPixel(x, y, r, g, b);
        }
    }

    int cx = WIDTH / 2 + (int)(SDL_cos(time) * 80.0);
    int cy = HEIGHT / 2 + (int)(SDL_sin(time) * 80.0);
    for (int dy = -10; dy <= 10; dy++) {
        for (int dx = -10; dx <= 10; dx++) {
            if (dx * dx + dy * dy <= 10 * 10) {
                putPixel(cx + dx, cy + dy, 255, 255, 255);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Pixel Manipulation & Frame Buffers", WIDTH * 2, HEIGHT * 2, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    SDL_SetRenderLogicalPresentation(renderer, WIDTH, HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                              SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        double time = SDL_GetTicks() / 1000.0;

        drawFrame(time);

        SDL_UpdateTexture(texture, NULL, pixels.data(), WIDTH * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
