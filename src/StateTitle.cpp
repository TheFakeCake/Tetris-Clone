/////////////////////////////////////////////////
/// \file StateTitle.cpp
/// \brief Implementation of the StateTitle class methods.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "StateTitle.hpp"

#include <SFML/Window/Event.hpp>

#include "Tetris.hpp"

/////////////////////////////////////////////////
StateTitle::StateTitle(Tetris& tetris) : GameState(tetris)
{
    m_bgTexture.LoadFromFile("resources/images/title_background.png");
    m_bgSprite.SetTexture(m_bgTexture);
}


/////////////////////////////////////////////////
void StateTitle::HandleEvents()
{
    sf::Event ev;
    while(m_window.PollEvent(ev))
    {
        if(ev.Type == sf::Event::Closed)
        {
            // Exit the application if the window is closed
            m_tetris.SetNextState(STATE_EXIT);
        }
        else if(ev.Type == sf::Event::KeyPressed)
        {
            // Go to the Menu screen if a key is pressed
            m_tetris.SetNextState(STATE_MENU);
        }
    }
}


/////////////////////////////////////////////////
void StateTitle::Logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateTitle::Render()
{
    m_window.Clear();
    m_window.Draw(m_bgSprite);
    m_window.Display();
}
