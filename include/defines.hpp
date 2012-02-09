#ifndef DEFINES_HPP_INCLUDED
#define DEFINES_HPP_INCLUDED

/////////////////////////////////////////////////
/// \file defines.hpp
/// \brief Declaration of constants
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

/////////////////////////////////////////////////
/// \enum GameStateID
/// \brief Constants for the different Game states.
/////////////////////////////////////////////////
enum GameStateID {
    STATE_NULL,         ///< No state
    STATE_TITLE,        ///< Title screen
    STATE_MENU,         ///< Menu screen
    STATE_PLAY,         ///< Tetris game screen
    STATE_NEW_SCORE,    ///< New score screen
    STATE_HIGH_SCORES,  ///< High scores screen
    STATE_HELP,         ///< Help screen
    STATE_EXIT          ///< Exit the application
};

/////////////////////////////////////////////////
/// \enum
/// \brief Some constants
/////////////////////////////////////////////////
enum {
    BLOCK_SIZE          = 24,   ///< Size of the Tetris blocks (width and height)
    NB_BLOCKS_WIDTH     = 10,   ///< Number of blocks in width of the map
    NB_BLOCKS_HEIGHT    = 22,   ///< Number of blocks in height of the map
    MAP_COORD_X         = 30,   ///< Top left X coordinate of the map
    MAP_COORD_Y         = 36,   ///< Top left Y coordinate of the map
    PREVIEW_COORD_X     = 450,  ///< Center X coordinate of the preview box
    PREVIEW_COORD_Y     = 84    ///< Center Y coordinate of the preview box
};

/////////////////////////////////////////////////
/// \enum BlockType
/// \brief List of the different block types.
/////////////////////////////////////////////////
enum BlockType {
    BLOCK_RED,      ///< Red block (I figure)
    BLOCK_YELLOW,   ///< Yellow block (square figure)
    BLOCK_BLUE,     ///< Blue block (J figure)
    BLOCK_PURPLE,   ///< Purple block (L figure)
    BLOCK_GREEN,    ///< Green block (T figure)
    BLOCK_ORANGE,   ///< Orange block (Z figure)
    BLOCK_BLACK,    ///< Black block (S figure)
    BLOCK_NONE,     ///< No Block
    FIRST_BLOCK_TYPE = BLOCK_RED,   ///< First block type (Red block)
    LAST_BLOCK_TYPE = BLOCK_BLACK   ///< Last block type (Black block)
};


/////////////////////////////////////////////////
/// \enum Direction
/// \brief Constants for the different directions.
/////////////////////////////////////////////////
enum Direction {
    DIRECT_NULL,    ///< No direction
    DIRECT_LEFT,    ///< Left
    DIRECT_RIGHT,   ///< Right
    DIRECT_UP,      ///< Up
    DIRECT_DOWN     ///< Down
};

#endif // DEFINES_HPP_INCLUDED
