#ifndef STATEHIGHSCORES_HPP
#define STATEHIGHSCORES_HPP

/////////////////////////////////////////////////
/// \file StateHighScores.hpp
/// \brief Declaration of the StateHighScores class.
/// \author Benjamin Ganty
/// \date 24 November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "GameState.hpp"

/////////////////////////////////////////////////
/// \class StateHighScores
/// \brief High scores screen.
///
/// This state shows the high scores.
/////////////////////////////////////////////////
class StateHighScores : public GameState
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the state's data.
        ///
        /// \param tetris : The parent Tetris object.
        /////////////////////////////////////////////////
        StateHighScores(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Events handling.
        ///
        /// Processes all the user inputs.
        /////////////////////////////////////////////////
        void handleEvents();

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// There is no logic in the high scores screen.
        ///
        /// \param elapsedTime : Elapsed time since the last frame.
        /////////////////////////////////////////////////
        void logic(sf::Uint32 elapsedTime);

        /////////////////////////////////////////////////
        /// \brief Rendering.
        ///
        /// Draws the high scores screen.
        /////////////////////////////////////////////////
        void render();

    protected:

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture m_bgTexture;    ///< Texture of the background.
        sf::Sprite  m_bgSprite;     ///< Sprite of the background.
        sf::Font    m_font;         ///< Font.

        std::vector<std::vector<sf::Text> > m_scoresText; ///< Scores texts.
};

#endif // STATEHIGHSCORES_HPP
