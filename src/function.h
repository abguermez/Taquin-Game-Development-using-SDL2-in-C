#include "constant.h"

// Loads the tile images and creates the corresponding textures
void load_tile_images() {
    for (int i = 0; i < board_size * board_size - 1; i++) {
        // Load the image
        char filename[32];
        sprintf(filename, "Screen/Numbers/N%d.bmp", i + 1);
        SDL_Surface* surface = SDL_LoadBMP(filename);
        if (surface == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading %s: %s", filename, SDL_GetError());
            exit(1);
        }

        // Create the texture
        tile_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);

        // Free the surface
        SDL_FreeSurface(surface);
    }

    // Set the last texture to NULL
    tile_textures[board_size * board_size - 1] = NULL;
}

// Resets the board to the solved state
void reset_board() {
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            board[y][x] = y * board_size + x + 1;
        }
    }
    board[board_size - 1][board_size - 1] = 0;
    blank_x = board_size - 1;
    blank_y = board_size - 1;
}

// Shuffles the board using a random number generator
// Shuffles the board
void shuffle_board() {
    // Seed the random number generator

    // Shuffle the board 1000 times
    for (int i = 0; i < 1000; i++) {
        // Choose a random move
        int move = rand() % 4;
        if (move == 0 && blank_y > 0) {
            // Swap the blank tile with the tile above it
            board[blank_y][blank_x] = board[blank_y - 1][blank_x];
            board[blank_y - 1][blank_x] = 0;
            blank_y--;
        } else if (move == 1 && blank_y < board_size - 1) {
            // Swap the blank tile with the tile below it
            board[blank_y][blank_x] = board[blank_y + 1][blank_x];
            board[blank_y + 1][blank_x] = 0;
            blank_y++;
        } else if (move == 2 && blank_x > 0) {
            // Swap the blank tile with the tile to the left of it
            board[blank_y][blank_x] = board[blank_y][blank_x - 1];
            board[blank_y][blank_x - 1] = 0;
            blank_x--;
        } else if (move == 3 && blank_x < board_size - 1) {
            // Swap the blank tile with the tile to the right of it
            board[blank_y][blank_x] = board[blank_y][blank_x + 1];
            board[blank_y][blank_x + 1] = 0;
            blank_x++;
        }
    }
}

// Draws the board
void draw_board() {
    // Calculate the size of the tiles
    int tile_size = 640 / board_size;

    // Loop through the tiles
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            // Get the value of the current tile
            int value = board[y][x];

            // Calculate the position of the tile
            int x_pos = x * tile_size;
            int y_pos = y * tile_size;

            // Set the draw color to white
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            // Draw the tile
            SDL_Rect rect = { x_pos, y_pos, tile_size, tile_size };
            if (value == 0) {
                SDL_RenderFillRect(renderer, &rect);
            } else {
                SDL_RenderCopy(renderer, tile_textures[value - 1], NULL, &rect);
            }

            // Draw the border of the tile
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}

// Check if the player has won the game
bool check_win() {
    int current_value = 1;
    for (int y = 0; y < board_size; y++) {
        for (int x = 0; x < board_size; x++) {
            if (board[y][x] != current_value && (y != board_size - 1 || x != board_size - 1)) {
                return false;
            }
            current_value++;
        }
    }
    return true;
}