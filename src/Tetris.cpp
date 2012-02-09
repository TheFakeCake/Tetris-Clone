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
    m_window.Create(sf::VideoMode(600,600), "Tetris", sf::Style::Close);
    m_music.OpenFromFile("resources/audio/tetris_theme.ogg");
    m_music.SetVolume(60.0);
    m_currentState = new StateTitle(*this);

    // Initializing the seed for the rand() function
    srand(time(NULL));

    // Setting the window icon
    sf::Image icon;
    icon.LoadFromFile("resources/images/icon.png");
    m_window.SetIcon(icon.GetWidth(), icon.GetHeight(), icon.GetPixelsPtr());
}


/////////////////////////////////////////////////
Tetris::~Tetris()
{
    // Destroying the current state object
    delete m_currentState;
}


/////////////////////////////////////////////////
void Tetris::Run()
{
    // Game loop
    while(m_nextState != STATE_EXIT)
    {
        // Starting to play the music if it's stopped
        if(m_music.GetStatus() == sf::Music::Stopped)
            m_music.Play();

        m_currentState->HandleEvents();
        m_currentState->Logic(m_window.GetFrameTime());
        ChangeState();
        m_currentState->Render();
    }

    // Stopping the music
    m_music.Stop();
}


/////////////////////////////////////////////////
void Tetris::ChangeState()
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
            newState = new StateNewScore(*this, statePlay->GetScore());
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
void Tetris::SetNextState(GameStateID state)
{
    m_nextState = state;
}


/////////////////////////////////////////////////
sf::RenderWindow& Tetris::GetWindow()
{
    return m_window;
}
