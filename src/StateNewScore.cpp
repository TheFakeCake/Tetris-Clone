/////////////////////////////////////////////////
/// \file StateNewScore.cpp
/// \brief Implementation of the StateNewScore class methods.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "StateNewScore.hpp"

#include <sstream>

#include <SFML/Window/Event.hpp>

#include "Tetris.hpp"
#include "ScoreManager.hpp"

/////////////////////////////////////////////////
StateNewScore::StateNewScore(Tetris& tetris, unsigned long newScore) : GameState(tetris), m_newScore(newScore), m_strName("")
{
    // Resources loading
    m_bgTexture.LoadFromFile("resources/images/newscore_background.png");
    m_bgSprite.SetTexture(m_bgTexture);

    m_font.LoadFromFile("resources/fonts/visitor1.ttf");

    // Initializing the texts
    std::stringstream newScoreStr;
    newScoreStr << newScore;

    m_textNewScore.SetFont(m_font);
    m_textNewScore.SetColor(sf::Color(205, 5, 5));
    m_textNewScore.SetString(newScoreStr.str());
    m_textNewScore.SetPosition(m_window.GetWidth()/2 - m_textNewScore.GetRect().Width/2, 275);

    m_textName.SetFont(m_font);
    m_textName.SetColor(sf::Color(205, 5, 5));
    m_textName.SetPosition(0, 395);
}


/////////////////////////////////////////////////
void StateNewScore::HandleEvents()
{
    sf::Event ev;
    while(m_window.PollEvent(ev))
    {
        // X window button clicked
        if(ev.Type == sf::Event::Closed)
        {
            m_tetris.SetNextState(STATE_EXIT);
        }
        else if(ev.Type == sf::Event::KeyPressed)
        {
            switch(ev.Key.Code)
            {
            // Escape pressed
            case sf::Keyboard::Escape:
                m_tetris.SetNextState(STATE_MENU);
                break;

            // Backspace pressed
            case sf::Keyboard::Back:
                DeleteChar();
                break;

            // Enter pressed
            case sf::Keyboard::Return:
                SaveScore();
                break;

            default:
                break;
            }
        }
        // Character entered
        else if(ev.Type == sf::Event::TextEntered)
        {
            AddChar(ev.Text.Unicode);
        }
    }
}


/////////////////////////////////////////////////
void StateNewScore::Logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateNewScore::Render()
{
    m_window.Clear();
    m_window.Draw(m_bgSprite);
    m_window.Draw(m_textNewScore);
    m_window.Draw(m_textName);
    m_window.Display();
}


/////////////////////////////////////////////////
void StateNewScore::DeleteChar()
{
    if(m_strName.length() > 0)
    {
        m_strName.erase(m_strName.length() - 1);
        m_textName.SetString(m_strName);
        m_textName.SetX(m_window.GetWidth()/2 - m_textName.GetRect().Width/2);
    }
}


/////////////////////////////////////////////////
void StateNewScore::AddChar(sf::Uint32 character)
{
    // Player's name can't exceed 16 characters
    if(m_strName.length() < 16)
    {
        // Character filtering a-z , A-Z , 0-9 , _
        if((character >= 'a' && character <= 'z') ||
           (character >= 'A' && character <= 'Z') ||
           (character >= '0' && character <= '9') ||
           character == '_' || character == ' ')
        {
            // Changing space character to underscore
            if(character == ' ')
                character = '_';

            m_strName.push_back(character);
            m_textName.SetString(m_strName);
            m_textName.SetX(m_window.GetWidth()/2 - m_textName.GetRect().Width/2);
        }
    }
}


/////////////////////////////////////////////////
void StateNewScore::SaveScore()
{
    // Checks if a name has been entered
    if(m_strName.length() == 0)
        return;

    // Saves the score
    ScoreManager scores(5);
    scores.LoadFromFile("resources/scores");
    scores.AddScore(m_strName, m_newScore);
    scores.Write("resources/scores");

    // Changing game state
    m_tetris.SetNextState(STATE_HIGH_SCORES);
}
