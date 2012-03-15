#ifndef STATEHELP_HPP
#define STATEHELP_HPP

/////////////////////////////////////////////////
/// \file StateHelp.hpp
/// \brief Declaration of the StateHelp class.
/// \author Benjamin Ganty
/// \date 22nd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GameState.hpp"

/////////////////////////////////////////////////
/// \class StateHelp
/// \brief Help screen.
///
/// This state shows the help.
/////////////////////////////////////////////////
class StateHelp : public GameState
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the state's data (graphic resources).
        ///
        /// \param tetris : The parent Tetris object.
        /////////////////////////////////////////////////
        StateHelp(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Events handling.
        ///
        /// Processes all the user inputs.
        /////////////////////////////////////////////////
        void handleEvents();

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// There is no logic in the help screen.
        ///
        /// \param elapsedTime : Elapsed time since the last frame.
        /////////////////////////////////////////////////
        void logic(sf::Uint32 elapsedTime);

        /////////////////////////////////////////////////
        /// \brief Rendering.
        ///
        /// Draws the help screen on the window.
        /////////////////////////////////////////////////
        void render();

    protected:

        /////////////////////////////////////////////////
        // Member data
        /////////////////////////////////////////////////
        sf::Texture m_bgTexture;    ///< Texture of the background.
        sf::Sprite  m_bgSprite;     ///< Sprite of the background.
};

#endif // STATEHELP_HPP
