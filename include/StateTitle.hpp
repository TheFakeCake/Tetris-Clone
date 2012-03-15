#ifndef STATETITLE_HPP
#define STATETITLE_HPP

/////////////////////////////////////////////////
/// \file StateTitle.hpp
/// \brief Declaration of the StateTitle class.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GameState.hpp"

/////////////////////////////////////////////////
/// \class StateTitle
/// \brief Title screen.
///
/// This game state handles the title screen of the application.
/////////////////////////////////////////////////
class StateTitle : public GameState
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the state's data (graphic resources).
        ///
        /// \param tetris : The parent Tetris object.
        /////////////////////////////////////////////////
        StateTitle(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Event handling.
        ///
        /// Process the user inputs.
        /////////////////////////////////////////////////
        void handleEvents();

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// There is no logic to process on the title screen.
        ///
        /// \param elapsedTime : Elapsed time since the last frame.
        /////////////////////////////////////////////////
        void logic(sf::Uint32 elapsedTime);

        /////////////////////////////////////////////////
        /// \brief Rendering
        ///
        /// Draws the background image on the window.
        /////////////////////////////////////////////////
        void render();

    protected:

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture     m_bgTexture;    ///< Background texture.
        sf::Sprite      m_bgSprite;     ///< Background sprite.
};

#endif // STATETITLE_HPP
