// The size of the board (either 3 for easy or 4 for hard)
int board_size;

// The board tiles, with 0 representing the blank tile
int board[4][4];

// The x and y coordinates of the blank tile
int blank_x;
int blank_y;

// The SDL textures for the tiles
SDL_Texture* tile_textures[16];

// The SDL renderer
SDL_Renderer* renderer;