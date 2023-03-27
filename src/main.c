#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "function.h"
#include "constant.h"




int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error initializing SDL: %s", SDL_GetError());
        return 1;
    }

    // Create the window and renderer
    SDL_Window* window = SDL_CreateWindow("Taquin", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, 0);
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating window: %s", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating renderer: %s", SDL_GetError());
        return 1;
    }
     // Set up the board and textures
    board_size = 0;
    SDL_Texture* texture1 = NULL;
    SDL_Texture* texture2 = NULL;
    SDL_Texture* texture3 = NULL;
    SDL_Texture* texture4 = NULL;
    SDL_Texture* texture5 = NULL;
    SDL_Texture* current_texture = NULL;

    // Load the images and create the textures
    SDL_Surface* surface = SDL_LoadBMP("Screen/Interface/0.bmp");
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading image1.bmp: %s", SDL_GetError());
        exit(1);
    }
    texture1 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("Screen/Interface/1.bmp");
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading image2.bmp: %s", SDL_GetError());
        exit(1);
    }
    texture2 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("Screen/Interface/2.bmp");
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading image3.bmp: %s", SDL_GetError());
        exit(1);
    }
    texture3 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = SDL_LoadBMP("Screen/Interface/3.bmp");
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading image4.bmp: %s", SDL_GetError());
        exit(1);
    }
    texture4 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    surface = SDL_LoadBMP("Screen/Interface/4.bmp");
    if (surface == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading image5.bmp: %s", SDL_GetError());
        exit(1);
    }
    texture5 = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Set the current texture to the first image
    int current_image = 0;
    current_texture = texture1;

    // Set up the event loop
    SDL_Event event;
    bool running = true;

    while (running) {
        // Poll for events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                // The user closed the window
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                  // Switch to the next image
                  current_image++;
                  if (current_image >= 4) {
                      break;
                  }
                  // Set the current texture based on the current image
                if (current_image == 0) {
                    current_texture = texture1;
                } else if (current_image == 1) {
                    current_texture = texture2;
                } else if (current_image == 2) {
                    current_texture = texture3;
                } else if (current_image == 3) {
                    current_texture = texture4;
                }
                } else if (current_texture == texture4) {
                    // Check for difficulty selection
                    if (event.key.keysym.sym == SDLK_e) {
                        // Set the board size to 3 (easy)
                        board_size = 3;
                        load_tile_images();
                        reset_board();
                        shuffle_board();
                        current_texture = NULL;
                        } else if (event.key.keysym.sym == SDLK_h) {
                        // Set the board size to 4 (hard)
                        board_size = 4;
                        load_tile_images();
                        reset_board();
                        shuffle_board();
                        current_texture = NULL;
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Check if the player clicked on a tile
                int x = event.button.x / (640 / board_size);
                int y = event.button.y / (640 / board_size);

                // Check if the move is valid
                if (y > 0 && board[y - 1][x] == 0) {
                    board[y - 1][x] = board[y][x];
                    board[y][x] = 0;
                    blank_y = y;
                    blank_x = x;
                } else if (y < board_size - 1 && board[y + 1][x] == 0) {
                    board[y + 1][x] = board[y][x];
                    board[y][x] = 0;
                    blank_y = y;
                    blank_x = x;
                } else if (x > 0 && board[y][x - 1] == 0) {
                    board[y][x - 1] = board[y][x];
                    board[y][x] = 0;
                    blank_y = y;
                    blank_x = x;
                } else if (x < board_size - 1 && board[y][x + 1] == 0) {
                    board[y][x + 1] = board[y][x];
                    board[y][x] = 0;
                    blank_y = y;
                    blank_x = x;
                }
            }
        }

        // Clear the window
        SDL_RenderClear(renderer);

        if (current_texture == NULL) {
            // Draw the board if the game is in progress
            draw_board();

            // Check if the player has won
            if (check_win()) {
                // Switch to the final image
                current_texture = texture5;
            }
        } else {
            // Draw the current image
            SDL_RenderCopy(renderer, current_texture, NULL, NULL);
        }

        // Show the changes
        SDL_RenderPresent(renderer);
    }

    // Free the textures
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    SDL_DestroyTexture(texture3);
    SDL_DestroyTexture(texture4);
    for (int i = 0; i < board_size * board_size - 1; i++) {
        SDL_DestroyTexture(tile_textures[i]);
    }

    // Clean up SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}