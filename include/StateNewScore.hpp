#ifndef STATENEWSCORE_HPP
#define STATENEWSCORE_HPP

/////////////////////////////////////////////////
/// \file StateNewScore.hpp
/// \brief Declaration of the StateNewScore class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "GameState.hpp"

/////////////////////////////////////////////////
/// \class StateNewScore
/// \brief New score state.
///
/// This state handles the input of the player's name and
/// the score saving.
/////////////////////////////////////////////////
class StateNewScore : public GameState
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the state's data.
        ///
        /// \param tetris : The parent Tetris object.
        /// \param newScore : The new highscore to save
        /////////////////////////////////////////////////
        StateNewScore(Tetris& tetris, unsigned long newScore);

        /////////////////////////////////////////////////
        /// \brief Event handling.
        ///
        /// Process the user inputs.
        /////////////////////////////////////////////////
        void handleEvents();

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// There's no logic on this state.
        ///
        /// \param elapsedTime : The elapsed time since the last frame.
        /////////////////////////////////////////////////
        void logic(sf::Uint32 elapsedTime);

        /////////////////////////////////////////////////
        /// \brief Rendering
        ///
        /// Draws the elements of the state on the window.
        /////////////////////////////////////////////////
        void render();

    protected:

        /////////////////////////////////////////////////
        /// \brief Character deletion.
        ///
        /// Deletes the last character of the entered player's name.
        /////////////////////////////////////////////////
        void deleteChar();

        /////////////////////////////////////////////////
        /// \brief Adds a character.
        ///
        /// Adds a character at the end of the player's name if it
        /// pass through the character filtering.
        ///
        /// \param character : The character to add.
        /////////////////////////////////////////////////
        void addChar(sf::Uint32 character);

        /////////////////////////////////////////////////
        /// \brief Score saving.
        ///
        /// Saves the score into the score file.
        /////////////////////////////////////////////////
        void saveScore();

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture     m_bgTexture;    ///< Texture of the background.
        sf::Sprite      m_bgSprite;     ///< Sprite of the background.

        sf::Font        m_font;         ///< Texts font.

        unsigned long   m_newScore;     ///< Score.
        sf::Text        m_textNewScore; ///< Score text.

        std::string     m_strName;      ///< Player's name.
        sf::Text        m_textName;     ///< Player's name text.
};

#endif // STATENEWSCORE_HPP
