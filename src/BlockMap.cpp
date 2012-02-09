/////////////////////////////////////////////////
/// \file BlockMap.cpp
/// \brief Implementation of the BlockMap class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "BlockMap.hpp"

#include "Figure.hpp"

/////////////////////////////////////////////////
BlockMap::BlockMap(Tetris& tetris, sf::Texture& blocksSpritesheet) :
    GameObject(tetris),
    m_blocksSpritesheet(blocksSpritesheet)
{
    // Initializing the map
    m_map.resize(NB_BLOCKS_HEIGHT);
    for(int y = 0; y < NB_BLOCKS_HEIGHT; y++)
    {
        m_map[y].resize(NB_BLOCKS_WIDTH);
        for(int x = 0; x < NB_BLOCKS_WIDTH; x++)
        {
            // Every blocks are empty
            m_map[y][x].type = BLOCK_NONE;
            m_map[y][x].sprite.SetTexture(m_blocksSpritesheet);
            m_map[y][x].sprite.SetPosition(MAP_COORD_X + x * BLOCK_SIZE, MAP_COORD_Y + y * BLOCK_SIZE);
            m_map[y][x].x = x;
            m_map[y][x].y = y;
        }
    }
}


/////////////////////////////////////////////////
bool BlockMap::Collision(Figure& fig)
{
    const std::vector<std::vector< Block > >& grid = fig.GetGrid();
    unsigned int c = fig.GetGridSize();

    // For each block of the figure ...
    for(unsigned int y = 0; y < c; y++)
    {
        for(unsigned int x = 0; x < c; x++)
        {
            if(grid[y][x].type != BLOCK_NONE)
            {
                // ... checks if the block is out of the left and right map limits.
                if(grid[y][x].x < 0 || grid[y][x].x >= NB_BLOCKS_WIDTH)
                    return true;

                // ... checks if the block is out of the bottom map limit.
                if(grid[y][x].y >= NB_BLOCKS_HEIGHT)
                    return true;

                // ... checks if the block's position is already taken by an existing block.
                if(grid[y][x].y >= 0 && m_map[grid[y][x].y][grid[y][x].x].type != BLOCK_NONE)
                    return true;
            }
        }
    }

    return false;
}


/////////////////////////////////////////////////
void BlockMap::AddFigure(Figure& fig)
{
    const std::vector<std::vector< Block > >& grid = fig.GetGrid();
    unsigned int c = fig.GetGridSize();

    // For each block of the figure's grid
    for(unsigned int y = 0; y < c; y++)
    {
        for(unsigned int x = 0; x < c; x++)
        {
            // If the block isn't empty and is in the game surface
            if(grid[y][x].type != BLOCK_NONE &&
               grid[y][x].x >= 0 && grid[y][x].x < NB_BLOCKS_WIDTH &&
               grid[y][x].y >= 0 && grid[y][x].y < NB_BLOCKS_HEIGHT)
            {
                // Copy the figure block to into the map
                m_map[grid[y][x].y][grid[y][x].x].type = grid[y][x].type;
                m_map[grid[y][x].y][grid[y][x].x].sprite.SetSubRect(grid[y][x].sprite.GetSubRect());
            }
        }
    }
}


/////////////////////////////////////////////////
unsigned int BlockMap::DestroyCompleteLines()
{
    unsigned int destroyedLines = 0;

    // For each lines from top to bottom
    for(unsigned int y = 0; y < NB_BLOCKS_HEIGHT; y++)
    {
        bool completed = true;

        // For each block of the line
        for(unsigned int x = 0; x < NB_BLOCKS_WIDTH; x++)
        {
            // If the block is empty, sets to line to "incomplete"
            if(m_map[y][x].type == BLOCK_NONE)
            {
                completed = false;
                break;
            }
        }

        // If the line is full
        if(completed)
        {
            destroyedLines++;

            // Moves downs all the lines above
            for(unsigned int y2 = y; y2 > 0; y2--)
            {
                for(unsigned int x = 0; x < NB_BLOCKS_WIDTH; x++)
                {
                    m_map[y2][x].type = m_map[y2-1][x].type;
                    m_map[y2][x].sprite.SetSubRect(m_map[y2-1][x].sprite.GetSubRect());
                }
            }

            // Clears the top line
            for(unsigned int x = 0; x < NB_BLOCKS_WIDTH; x++)
                m_map[0][x].type = BLOCK_NONE;
        }
    }

    // Returns the number of destroyed lines
    return destroyedLines;
}


/////////////////////////////////////////////////
void BlockMap::Draw()
{
    for(int i = 0; i < NB_BLOCKS_HEIGHT; i++)
    {
        for(int j = 0; j < NB_BLOCKS_WIDTH; j++)
        {
            if(m_map[i][j].type != BLOCK_NONE)
                m_window.Draw(m_map[i][j].sprite);
        }
    }
}
