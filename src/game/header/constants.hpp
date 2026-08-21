#ifndef CONSTANTS
#define CONSTANTS

const int CAMERA_PPF = 5; // pixels per frame.

const int PLAYER_PPF = 2;

const int UPS = 60;

const int DISPLAY_WIDTH = 640;
const int DISPLAY_HEIGHT = 640;

// Number of tiles horizontally across the game arena
const int ARENA_TILES_HORIZONTAL = 20;

// Number of tiles vertically across the game arena
const int ARENA_TILES_VERTICAL = 20;

// Sidelength of game tiles in pixels
const int TILES_SIDELENGTH = 70;

const int ARENA_WIDTH = ARENA_TILES_HORIZONTAL * TILES_SIDELENGTH;
const int ARENA_HEIGHT = ARENA_TILES_VERTICAL * TILES_SIDELENGTH;

const int WALL_DETAIL_LEVEL = 3;

const int ALLIANCE_SIZE = 3;

// Sidelength in pixels
const int PLAYER_BOUNDING_BOX_SIDELENGTH = 40;

const int COLLISION_DETECT_TAXICAB_RANGE = 2*TILES_SIDELENGTH;
#endif



