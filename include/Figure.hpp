#ifndef FIGURE_HPP
#define FIGURE_HPP

/////////////////////////////////////////////////
/// \file Figure.hpp
/// \brief Definition of the Figure class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "GameObject.hpp"

class BlockMap;
struct Block;

/////////////////////////////////////////////////
/// \class Figure
/// \brief Figure made out of blocks.
///
/// A figure is made out of blocks and has a shape that depends on the block type.
/////////////////////////////////////////////////
class Figure : public GameObject
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the figure.
        ///
        /// \param tetris : The parent Tetris object.
        /// \param type : Block type of the figure. Also determines the shape of the figure.
        /// \param blocksSpritesheet : Reference to the blocks sprite sheet.
        /////////////////////////////////////////////////
        Figure(Tetris& tetris, BlockType type, sf::Texture& blocksSpritesheet);

        /////////////////////////////////////////////////
        /// \brief Figure rotation.
        ///
        /// Rotates the figure of 90 degrees (clockwise).
        /////////////////////////////////////////////////
        void Rotate();

        /////////////////////////////////////////////////
        /// \brief Moves the figure.
        ///
        /// Moves the figure of one block in the given direction.
        ///
        /// \param direction : Direction of movement.
        /////////////////////////////////////////////////
        void Move(Direction direction);

        /////////////////////////////////////////////////
        /// \brief Rendering.
        ///
        /// Draws the figure.
        /////////////////////////////////////////////////
        void Draw();

        /////////////////////////////////////////////////
        /// \brief Returns a constant reference to the figure's block grid.
        ///
        /// \return The reference to the block grid.
        /////////////////////////////////////////////////
        const std::vector<std::vector< Block > >& GetGrid();

        /////////////////////////////////////////////////
        /// \brief Returns the grid size.
        ///
        /// \return Grid size.
        /////////////////////////////////////////////////
        unsigned int GetGridSize();

        /////////////////////////////////////////////////
        /// \brief Returns the figure's block type.
        ///
        /// \return Block type.
        /////////////////////////////////////////////////
        BlockType GetType();

        /////////////////////////////////////////////////
        /// \brief Tells if the figure is out of the map or not.
        ///
        /// If on block is out of the map, the figure is considered "out of game".
        ///
        /// \return True if the figure is out of game.
        /////////////////////////////////////////////////
        bool IsOutOfGame();

        /////////////////////////////////////////////////
        /// \brief Sets the position for preview figure.
        ///
        /// The preview figure has a custom position, so the preview position
        /// can be set with this method.
        /////////////////////////////////////////////////
        void SetNextFigPos();

    protected:

        /////////////////////////////////////////////////
        /// \brief Grid initialization.
        ///
        /// Initializes the grid with a given size.
        ///
        /// \param gridSize : The grid size.
        /////////////////////////////////////////////////
        void InitGrid(unsigned int gridSize);

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture&    m_blocksSpritesheet;    ///< Blocks sprites sheet texture.
        BlockType       m_type;                 ///< Block type.
        std::vector<std::vector<Block> > m_grid;///< Grid of blocks.
        unsigned int    m_gridSize;             ///< Grid size.
        bool            m_outOfGame;            ///< Out of the game flag.
        bool            m_previewNextFig;       ///< Preview figure flag.
};

#endif // FIGURE_HPP
