#ifndef BLOCKMAP_HPP
#define BLOCKMAP_HPP

/////////////////////////////////////////////////
/// \file BlockMap.hpp
/// \brief Declaration of the BlockMap class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GameObject.hpp"

class Figure;

/////////////////////////////////////////////////
/// \struct Block
/// \brief Stores the data of a block.
/////////////////////////////////////////////////
struct Block
{
    BlockType   type;   ///< Block type.
    sf::Sprite  sprite; ///< Block sprite.
    int         x;      ///< X position of the block in the BlockMap
    int         y;      ///< Y position of the block in the BlockMap
};

/////////////////////////////////////////////////
/// \class BlockMap
/// \brief Block map of the Tetris playing surface.
///
/// The BlockMap is a 2D vector of Block. The map is stored this way :
/// m_map[line][column]
///
/// The top left block of the map is m_map[0][0].
/////////////////////////////////////////////////
class BlockMap : public GameObject
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Initializes the object.
        /////////////////////////////////////////////////
        BlockMap(Tetris& tetris, sf::Texture& blocksSpritesheet);

        /////////////////////////////////////////////////
        /// \brief Collision detection.
        ///
        /// Detects collision between a given figure and the blocks of the map and
        /// the map's border.
        ///
        /// \return True if a collision is detected. Else, returns False.
        /////////////////////////////////////////////////
        bool collision(Figure& fig);

        /////////////////////////////////////////////////
        /// \brief Adds blocks to the map.
        ///
        /// This method adds the given figures's blocks to the map.
        ///
        /// \param fig : Reference to a figure.
        /////////////////////////////////////////////////
        void addFigure(Figure& fig);

        /////////////////////////////////////////////////
        /// \brief Destroying complete map lines.
        ///
        /// Search for map lines full of blocks and destroy them.
        ///
        /// \return The number of destroyed lines.
        /////////////////////////////////////////////////
        unsigned int destroyCompleteLines();

        /////////////////////////////////////////////////
        /// \brief Rendering.
        ///
        /// Draws the map.
        /////////////////////////////////////////////////
        void draw();

    protected:

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture& m_blocksSpritesheet;       ///< Reference to the blocks sprite sheet texture.
        std::vector<std::vector<Block> > m_map; ///< Block map (2D table of blocks).
};

#endif // BLOCKMAP_HPP
