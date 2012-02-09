#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

/////////////////////////////////////////////////
/// \file GameObject.hpp
/// \brief Definition of the GameObject class.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/RenderWindow.hpp>
#include "defines.hpp"

class Tetris;

/////////////////////////////////////////////////
/// \class GameObject
/// \brief Tetris game object.
///
/// Stores references to the parent Tetris object and
/// the application window. Every other class that needs to
/// interact with the window or the root object (Tetris)
/// should inherit GameObject.
/////////////////////////////////////////////////
class GameObject
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the member data.
        ///
        /// \param tetris Reference to the parent Tetris object.
        ///
        /////////////////////////////////////////////////
        GameObject(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /// Virtual definition for upcoming inheritance.
        /////////////////////////////////////////////////
        virtual ~GameObject();

    protected:

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        Tetris&             m_tetris;   ///< Reference to the parent Tetris object.
        sf::RenderWindow&   m_window;   ///< Reference to the application window.
};

#endif // GAMEOBJECT_HPP
