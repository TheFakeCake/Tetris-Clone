/////////////////////////////////////////////////
/// \file GameObject.hpp
/// \brief Implementation of the GameObject class methods.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "GameObject.hpp"

#include "Tetris.hpp"

/////////////////////////////////////////////////
GameObject::GameObject(Tetris& tetris) :
    m_tetris(tetris),
    m_window(tetris.GetWindow())
{}


/////////////////////////////////////////////////
GameObject::~GameObject()
{}
