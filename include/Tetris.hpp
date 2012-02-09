#ifndef TETRIS_HPP
#define TETRIS_HPP

/////////////////////////////////////////////////
/// \file Tetris.hpp
/// \brief Declaration of the Tetris class.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>
#include "defines.hpp"

class GameState;

/////////////////////////////////////////////////
/// \class Tetris
/// \brief Game root class.
///
/// The Tetris class initializes the window. It also handles the game loop,
/// the game states management and the music.
/////////////////////////////////////////////////
class Tetris
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Initializes the game.
        /////////////////////////////////////////////////
        Tetris();

        /////////////////////////////////////////////////
        /// \brief Destructor.
        ///
        /// Frees the memory.
        /////////////////////////////////////////////////
        virtual ~Tetris();

        /////////////////////////////////////////////////
        /// \brief Starts the Tetris application.
        ///
        /// Plays the music and handles the game loop.
        /////////////////////////////////////////////////
        void Run();

        /////////////////////////////////////////////////
        /// \brief Sets the next game states
        ///
        /// To change the game states, the new game states ID has to
        /// be given to this method.
        ///
        /// \param state : The ID of the next game state.
        /////////////////////////////////////////////////
        void SetNextState(GameStateID state);

        /////////////////////////////////////////////////
        /// \brief Returns a reference to the window object.
        ///
        /// \return Reference to the window.
        /////////////////////////////////////////////////
        sf::RenderWindow& GetWindow();

    protected:

        /////////////////////////////////////////////////
        /// \brief Changes the game state.
        ///
        /// If a new game state has been set, handles the state changing.
        ///
        /// \see SetNextState
        /////////////////////////////////////////////////
        void ChangeState();

        ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        sf::RenderWindow    m_window;       ///< Program's window.
        sf::Music           m_music;        ///< Music.
        GameState*          m_currentState; ///< Pointer to the current game state.
        GameStateID         m_nextState;    ///< ID of the next game state.
};

#endif // TETRIS_HPP
