/////////////////////////////////////////////////
/// \file Tetris.cpp
/// \brief Implementation of the Tetris class methods.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "Tetris.hpp"

#include <cstdlib>
#include <ctime>

#include "StateTitle.hpp"
#include "StateMenu.hpp"
#include "StateHighScores.hpp"
#include "StateHelp.hpp"
#include "StatePlay.hpp"
#include "StateNewScore.hpp"

/////////////////////////////////////////////////
Tetris::Tetris() : m_nextState(STATE_NULL)
{
    // Initializations
    m_window.create(sf::VideoMode(600,600), "Tetris", sf::Style::Close);
    m_music.openFromFile("resources/audio/tetris_theme.ogg");
    m_music.setVolume(60.0);
    m_music.setLoop(true);
    m_currentState = new StateTitle(*this);

    // Initializing the seed for the rand() function
    srand(time(NULL));

    // Setting the window icon
    sf::Image icon;
    icon.loadFromFile("resources/images/icon.png");
    m_window.setIcon(icon.getWidth(), icon.getHeight(), icon.getPixelsPtr());
}


/////////////////////////////////////////////////
Tetris::~Tetris()
{
    // Destroying the current state object
    delete m_currentState;
}


/////////////////////////////////////////////////
void Tetris::run()
{
    // Frame clock
    sf::Clock frameClock;

    // Playing the music
    m_music.play();

    // Game loop
    while(m_nextState != STATE_EXIT)
    {
        m_currentState->handleEvents();
        m_currentState->logic(frameClock.restart().asMicroseconds());
        changeState();
        m_currentState->render();
    }

    // Stopping the music
    m_music.stop();
}


/////////////////////////////////////////////////
void Tetris::changeState()
{
    // Changes the game state if needed
    if(m_nextState != STATE_NULL && m_nextState != STATE_EXIT)
    {
        GameState* newState = NULL;

        switch(m_nextState)
        {
        case STATE_TITLE:
            newState = new StateTitle(*this);
            break;

        case STATE_MENU:
            newState = new StateMenu(*this);
            break;

        case STATE_PLAY:
            newState = new StatePlay(*this);
            break;

        case STATE_NEW_SCORE:
        {
            // Casting the current state to retrieve the score in StatePlay
            StatePlay* statePlay = static_cast<StatePlay*>(m_currentState);
            newState = new StateNewScore(*this, statePlay->getScore());
            break;
        }

        case STATE_HIGH_SCORES:
            newState = new StateHighScores(*this);
            break;

        case STATE_HELP:
            newState = new StateHelp(*this);
            break;

        default:
            break;
        }

        // State switching
        delete m_currentState;
        m_currentState = newState;
        m_nextState = STATE_NULL;
    }
}


/////////////////////////////////////////////////
void Tetris::setNextState(GameStateID state)
{
    m_nextState = state;
}


/////////////////////////////////////////////////
sf::RenderWindow& Tetris::getWindow()
{
    return m_window;
}
