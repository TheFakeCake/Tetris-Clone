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
    m_bgTexture.loadFromFile("resources/images/title_background.png");
    m_bgSprite.setTexture(m_bgTexture);
}


/////////////////////////////////////////////////
void StateTitle::handleEvents()
{
    sf::Event ev;
    while(m_window.pollEvent(ev))
    {
        if(ev.type == sf::Event::Closed)
        {
            // Exit the application if the window is closed
            m_tetris.setNextState(STATE_EXIT);
        }
        else if(ev.type == sf::Event::KeyPressed)
        {
            // Go to the Menu screen if a key is pressed
            m_tetris.setNextState(STATE_MENU);
        }
    }
}


/////////////////////////////////////////////////
void StateTitle::logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateTitle::render()
{
    m_window.clear();
    m_window.draw(m_bgSprite);
    m_window.display();
}
