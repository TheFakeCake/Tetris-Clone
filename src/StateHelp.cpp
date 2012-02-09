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
    m_bgTexture.LoadFromFile("resources/images/help_background.png");
    m_bgSprite.SetTexture(m_bgTexture);
}


/////////////////////////////////////////////////
void StateHelp::HandleEvents()
{
    sf::Event ev;
    while(m_window.PollEvent(ev))
    {
        // X window button clicked
        if(ev.Type == sf::Event::Closed)
        {
            m_tetris.SetNextState(STATE_EXIT);
        }
        // A key is pressed
        else if(ev.Type == sf::Event::KeyPressed)
        {
            m_tetris.SetNextState(STATE_MENU);
        }
    }
}


/////////////////////////////////////////////////
void StateHelp::Logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateHelp::Render()
{
    m_window.Clear();
    m_window.Draw(m_bgSprite);
    m_window.Display();
}
