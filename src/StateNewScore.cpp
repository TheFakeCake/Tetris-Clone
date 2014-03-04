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
    m_bgTexture.loadFromFile("resources/images/newscore_background.png");
    m_bgSprite.setTexture(m_bgTexture);

    m_font.loadFromFile("resources/fonts/visitor1.ttf");

    // Initializing the texts
    std::stringstream newScoreStr;
    newScoreStr << newScore;

    m_textNewScore.setFont(m_font);
    m_textNewScore.setColor(sf::Color(205, 5, 5));
    m_textNewScore.setString(newScoreStr.str());
    m_textNewScore.setPosition(m_window.getSize().x/2 - m_textNewScore.getGlobalBounds().width/2, 275);

    m_textName.setFont(m_font);
    m_textName.setColor(sf::Color(205, 5, 5));
    m_textName.setPosition(0, 395);
}


/////////////////////////////////////////////////
void StateNewScore::handleEvents()
{
    sf::Event ev;
    while(m_window.pollEvent(ev))
    {
        // X window button clicked
        if(ev.type == sf::Event::Closed)
        {
            m_tetris.setNextState(STATE_EXIT);
        }
        else if(ev.type == sf::Event::KeyPressed)
        {
            switch(ev.key.code)
            {
            // Escape pressed
            case sf::Keyboard::Escape:
                m_tetris.setNextState(STATE_MENU);
                break;

            // Backspace pressed
            case sf::Keyboard::BackSpace:
                deleteChar();
                break;

            // Enter pressed
            case sf::Keyboard::Return:
                saveScore();
                break;

            default:
                break;
            }
        }
        // Character entered
        else if(ev.type == sf::Event::TextEntered)
        {
            addChar(ev.text.unicode);
        }
    }
}


/////////////////////////////////////////////////
void StateNewScore::logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateNewScore::render()
{
    m_window.clear();
    m_window.draw(m_bgSprite);
    m_window.draw(m_textNewScore);
    m_window.draw(m_textName);
    m_window.display();
}


/////////////////////////////////////////////////
void StateNewScore::deleteChar()
{
    if(m_strName.length() > 0)
    {
        m_strName.erase(m_strName.length() - 1);
        m_textName.setString(m_strName);
        m_textName.setPosition(m_window.getSize().x/2 - m_textName.getGlobalBounds().width/2,
                               m_textName.getPosition().y);
    }
}


/////////////////////////////////////////////////
void StateNewScore::addChar(sf::Uint32 character)
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
            m_textName.setString(m_strName);
            m_textName.setPosition(m_window.getSize().x/2 - m_textName.getGlobalBounds().width/2,
                                   m_textName.getPosition().y);
        }
    }
}


/////////////////////////////////////////////////
void StateNewScore::saveScore()
{
    // Checks if a name has been entered
    if(m_strName.length() == 0)
        return;

    // Saves the score
    ScoreManager scores(5);
    scores.loadFromFile("resources/scores");
    scores.addScore(m_strName, m_newScore);
    scores.write("resources/scores");

    // Changing game state
    m_tetris.setNextState(STATE_HIGH_SCORES);
}
