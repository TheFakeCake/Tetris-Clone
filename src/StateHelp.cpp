/////////////////////////////////////////////////
/// \file StateHelp.cpp
/// \brief Implementation of the StateHelp class.
/// \author Benjamin Ganty
/// \date 22nd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "StateHelp.hpp"

#include <SFML/Window/Event.hpp>

#include "Tetris.hpp"

/////////////////////////////////////////////////
StateHelp::StateHelp(Tetris& tetris) : GameState(tetris)
{
    // Loading the background
    m_bgTexture.loadFromFile("resources/images/help_background.png");
    m_bgSprite.setTexture(m_bgTexture);
}


/////////////////////////////////////////////////
void StateHelp::handleEvents()
{
    sf::Event ev;
    while(m_window.pollEvent(ev))
    {
        // X window button clicked
        if(ev.type == sf::Event::Closed)
        {
            m_tetris.setNextState(STATE_EXIT);
        }
        // A key is pressed
        else if(ev.type == sf::Event::KeyPressed)
        {
            m_tetris.setNextState(STATE_MENU);
        }
    }
}


/////////////////////////////////////////////////
void StateHelp::logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateHelp::render()
{
    m_window.clear();
    m_window.draw(m_bgSprite);
    m_window.display();
}
