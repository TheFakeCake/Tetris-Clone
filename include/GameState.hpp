#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

/////////////////////////////////////////////////
/// \file GameState.hpp
/// \brief Declaration of the GameState class.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "GameObject.hpp"

/////////////////////////////////////////////////
/// \class GameState
/// \brief Abstract game state class.
///
/// A game state is made of three main parts. The event handling,
/// the logic updating, and the rendering. Each step is executed into
/// the game loop of the parent Tetris object.
/////////////////////////////////////////////////
class GameState : public GameObject
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Extends to the GameObject constructor.
        ///
        /// \param tetris : The parent Tetris object.
        /////////////////////////////////////////////////
        GameState(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Event handling.
        ///
        /// Processes all the user's input events.
        /////////////////////////////////////////////////
        virtual void HandleEvents() = 0;

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// Handles the logic of the game state (updating, checking, etc ...).
        ///
        /// \param elapsedTime : Elapsed time since the last frame.
        /////////////////////////////////////////////////
        virtual void Logic(sf::Uint32 elapsedTime) = 0;

        /////////////////////////////////////////////////
        /// \brief Rendering.
        ///
        /// Handles the rendering of the game state.
        /////////////////////////////////////////////////
        virtual void Render() = 0;
};

#endif // GAMESTATE_HPP
