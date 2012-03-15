#ifndef STATEPLAY_HPP
#define STATEPLAY_HPP

/////////////////////////////////////////////////
/// \file StatePlay.hpp
/// \brief Declaration of the StatePlay class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "GameState.hpp"
#include "BlockMap.hpp"

/////////////////////////////////////////////////
/// \class StatePlay
/// \brief Tetris playing state.
///
/// This game state handles a game of Tetris.
/////////////////////////////////////////////////
class StatePlay : public GameState
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the state's data and the game of Tetris.
        ///
        /// \param tetris : The parent Tetris object.
        /////////////////////////////////////////////////
        StatePlay(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /// Frees the memory
        /////////////////////////////////////////////////
        virtual ~StatePlay();

        /////////////////////////////////////////////////
        /// \brief Event handling.
        ///
        /// Process the user inputs.
        /////////////////////////////////////////////////
        void handleEvents();

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// Processes the logic of the Tetris game (downward movement of the figure,
        /// collisions checking, scoring, ...).
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

        /////////////////////////////////////////////////
        /// \brief Returns the score.
        ///
        /// Returns the player's current score. This method is mainly
        /// used to get the score after the end of the game, when the
        /// state changes to the StateNewScore.
        ///
        /// \return The player's score.
        /////////////////////////////////////////////////
        unsigned long getScore();

    protected:

        /////////////////////////////////////////////////
        /// \brief Scoring.
        ///
        /// Add points to the score, updates the level and the difficulty.
        /// The score updating requires the number of lines destroyed at the same time.
        /// More points for more lines destroyed at the same time :\n
        ///
        /// 1 line : 40 * (level + 1) points\n
        /// 2 lines : 100 * (level + 1) points\n
        /// 3 lines : 300 * (level + 1) points\n
        /// 4 lines : 1200 * (level + 1) points\n
        ///
        /// \param nbLinesDestroyed : Number of lines destroyed.
        /////////////////////////////////////////////////
        void incScore(unsigned int nbLinesDestroyed);

        /////////////////////////////////////////////////
        /// \brief Updates the dynamic texts on the screen.
        ///
        /// Updates the content and the position of all the score texts on the screen.
        /////////////////////////////////////////////////
        void updateTexts();

        /////////////////////////////////////////////////
        /// \brief Creates a random figure.
        ///
        /// This random figure creating function is used the generate figures randomly
        /// at the initialization of the game and when a figure stops moving downward.
        ///
        /// \return Pointer to the random figure.
        /////////////////////////////////////////////////
        Figure* generateRandomFig();


        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture     m_bgTexture;        ///< Texture of the background.
        sf::Sprite      m_bgSprite;         ///< Sprite of the background.
        sf::Texture     m_gameOverTexture;  ///< Game over texture.
        sf::Sprite      m_gameOverSprite;   ///< Game over sprite.
        sf::Texture     m_blocksSpritesheet;///< Sprites sheet of the blocks.
        sf::Font        m_font;             ///< Text's font.

        BlockMap        m_map;              ///< Game map (block table).
        Figure*         m_currentFig;       ///< Current controlled figure.
        Figure*         m_nextFig;          ///< Preview of the next figure.

        unsigned long   m_score;            ///< Player's score.
        unsigned long   m_lvl;              ///< Game level.
        unsigned long   m_linesDestroyed;   ///< Number of lines destroyed.
        sf::Uint32      m_normalGameSpeed;  ///< Normal game speed.
        sf::Uint32      m_gameSpeed;        ///< Current game speed.
        bool            m_gameOver;         ///< Game over flag.
        sf::Uint32      m_gameOverTimer;    ///< Time that the game over message stayed on screen.

        sf::Uint32      m_moveDownTimer;    ///< Elapsed time since last downward movement of the figure.
        Direction       m_figMoveDirection; ///< Direction of possible lateral movement of the figure.
        bool            m_rotate;           ///< Figure rotation flag.

        sf::Text        m_textScore;            ///< Score text.
        sf::Text        m_textLvl;              ///< Level text
        sf::Text        m_textLinesDestroyed;   ///< Number of lines destroyed text.
};

#endif // STATEPLAY_HPP
