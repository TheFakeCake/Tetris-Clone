/////////////////////////////////////////////////
/// \file Figure.cpp
/// \brief Implementation of the Figure class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "Figure.hpp"

#include "BlockMap.hpp"

/////////////////////////////////////////////////
Figure::Figure(Tetris& tetris, BlockType type, sf::Texture& blocksSpritesheet) :
    GameObject(tetris),
    m_blocksSpritesheet(blocksSpritesheet),
    m_type(type),
    m_outOfGame(true),
    m_previewNextFig(false)
{
    // Creating the figure
    switch(m_type)
    {
    case BLOCK_RED:
        InitGrid(4);
        m_grid[0][2].type = m_type;
        m_grid[1][2].type = m_type;
        m_grid[2][2].type = m_type;
        m_grid[3][2].type = m_type;
        break;

    case BLOCK_YELLOW:
        InitGrid(2);
        m_grid[0][0].type = m_type;
        m_grid[0][1].type = m_type;
        m_grid[1][0].type = m_type;
        m_grid[1][1].type = m_type;
        break;

    case BLOCK_BLUE:
        InitGrid(3);
        m_grid[0][1].type = m_type;
        m_grid[1][1].type = m_type;
        m_grid[2][1].type = m_type;
        m_grid[2][2].type = m_type;
        break;

    case BLOCK_PURPLE:
        InitGrid(3);
        m_grid[0][1].type = m_type;
        m_grid[1][1].type = m_type;
        m_grid[2][1].type = m_type;
        m_grid[2][0].type = m_type;
        break;

    case BLOCK_GREEN:
        InitGrid(3);
        m_grid[0][1].type = m_type;
        m_grid[1][0].type = m_type;
        m_grid[1][1].type = m_type;
        m_grid[1][2].type = m_type;
        break;

    case BLOCK_ORANGE:
        InitGrid(3);
        m_grid[0][0].type = m_type;
        m_grid[0][1].type = m_type;
        m_grid[1][1].type = m_type;
        m_grid[1][2].type = m_type;
        break;

    case BLOCK_BLACK:
        InitGrid(3);
        m_grid[0][2].type = m_type;
        m_grid[0][1].type = m_type;
        m_grid[1][1].type = m_type;
        m_grid[1][0].type = m_type;
        break;

    default:
        break;
    }
}


/////////////////////////////////////////////////
void Figure::Rotate()
{
    m_outOfGame = false;
    std::vector<std::vector<Block> > gridCopy = m_grid;

    // Rotating each blocks of the grid
    for(unsigned int y = 0; y < m_gridSize; y++)
    {
        for(unsigned int x = 0; x < m_gridSize; x++)
        {
            m_grid[y][x].type = gridCopy[m_gridSize-x-1][y].type;
            m_grid[y][x].sprite.SetSubRect(gridCopy[m_gridSize-x-1][y].sprite.GetSubRect());

            // checking for out of game block
            if(m_grid[y][x].type != BLOCK_NONE && m_grid[y][x].y < 0)
                m_outOfGame = true;
        }
    }
}


/////////////////////////////////////////////////
void Figure::Move(Direction direction)
{
    int xMove = 0;
    int yMove = 0;
    m_outOfGame = false;

    // Setting position modifiers
    switch(direction)
    {
    case DIRECT_DOWN:
        yMove = 1;
        break;
    case DIRECT_UP:
        yMove = -1;
        break;
    case DIRECT_LEFT:
        xMove = -1;
        break;
    case DIRECT_RIGHT:
        xMove = 1;
        break;
    default:
        break;
    }

    // For each block of the grid ...
    for(unsigned int y = 0; y < m_gridSize; y++)
    {
        for(unsigned int x = 0; x < m_gridSize; x++)
        {
            // ... moving the block
            m_grid[y][x].x += xMove;
            m_grid[y][x].y += yMove;

            m_grid[y][x].sprite.SetPosition(MAP_COORD_X + m_grid[y][x].x * BLOCK_SIZE,
                                            MAP_COORD_Y + m_grid[y][x].y * BLOCK_SIZE);

            // ... checking for out of game block
            if(m_grid[y][x].y < 0)
                m_outOfGame = true;
        }
    }
}


/////////////////////////////////////////////////
void Figure::Draw()
{
    for(unsigned y = 0; y < m_gridSize; y++)
    {
        for(unsigned x = 0; x < m_gridSize; x++)
        {
            if(m_grid[y][x].type != BLOCK_NONE)
            {
                if(m_previewNextFig || m_grid[y][x].y >= 0)
                    m_window.Draw(m_grid[y][x].sprite);
            }
        }
    }
}


/////////////////////////////////////////////////
const std::vector<std::vector< Block > >& Figure::GetGrid()
{
    return m_grid;
}


/////////////////////////////////////////////////
unsigned int Figure::GetGridSize()
{
    return m_gridSize;
}


/////////////////////////////////////////////////
BlockType Figure::GetType()
{
    return m_type;
}


/////////////////////////////////////////////////
bool Figure::IsOutOfGame()
{
    return m_outOfGame;
}


/////////////////////////////////////////////////
void Figure::SetNextFigPos()
{
    m_previewNextFig = true;
    float xOrigin = (float)PREVIEW_COORD_X - (float)m_gridSize / 2 * BLOCK_SIZE;
    float yOrigin = (float)PREVIEW_COORD_Y - (float)m_gridSize / 2 * BLOCK_SIZE;

    for(unsigned int y = 0; y < m_gridSize; y++)
    {
        for(unsigned int x = 0; x < m_gridSize; x++)
            m_grid[y][x].sprite.SetPosition(xOrigin + x * BLOCK_SIZE, yOrigin + y * BLOCK_SIZE);
    }
}


/////////////////////////////////////////////////
void Figure::InitGrid(unsigned int gridSize)
{
    m_grid.resize(gridSize, std::vector< Block >(gridSize));

    // Initializing each block of the grid
    for(unsigned int y = 0; y < gridSize; y++)
    {
        for(unsigned int x = 0; x < gridSize; x++)
        {
            m_grid[y][x].type = BLOCK_NONE;

            m_grid[y][x].x = x + NB_BLOCKS_WIDTH / 2 - gridSize / 2;
            m_grid[y][x].y = 0 - gridSize + y;

            m_grid[y][x].sprite.SetTexture(m_blocksSpritesheet);
            m_grid[y][x].sprite.SetPosition(MAP_COORD_X + m_grid[y][x].x * BLOCK_SIZE,
                                            MAP_COORD_Y + m_grid[y][x].y * BLOCK_SIZE);
            m_grid[y][x].sprite.SetSubRect(sf::IntRect(m_type * BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE));
        }
    }

    m_gridSize = gridSize;
}
