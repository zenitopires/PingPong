#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "headers/init.h"
#include "headers/defs.h"
#include "headers/log.h"

void Init(char* string) {
    int window_flags, renderer_flags;

    window_flags = 0;
    renderer_flags = SDL_RENDERER_ACCELERATED;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        log_debug("Cannot initialize SDL: %s.", SDL_GetError());
        exit(1);
    }
    else {
        log_debug("SDL initialized.");
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        log_debug("Failed to initialize audio: %s", Mix_GetError());
        exit(1);
    }
    else {
        log_debug("SDL_mixer initialized successfully.");
    }

    if (TTF_Init() == -1) {
        log_debug("SDL_ttf could not be initialized: %s", TTF_GetError());
        exit(1);
    }
    else  {
        log_debug("SDL_ttf initialized successfully.");
    }

    app.window = SDL_CreateWindow(
        string,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        window_flags
    );

    if (app.window == NULL) {
        log_debug("Could not create window: %s", SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, renderer_flags);

    if (app.renderer == NULL) {
        log_debug("Could not create renderer: %s", SDL_GetError());
        exit(1);
    }
    log_debug("All systems fine. Starting game.");
}

void CleanUp(void) {
    log_debug("Cleaning up SDL window and renderer.");
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
