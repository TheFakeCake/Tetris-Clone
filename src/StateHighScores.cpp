/////////////////////////////////////////////////
/// \file StateHighScores.cpp
/// \brief Implementation of the StateHighScores class.
/// \author Benjamin Ganty
/// \date 24 November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "StateHighScores.hpp"

#include <sstream>

#include <SFML/Window/Event.hpp>

#include "Tetris.hpp"
#include "ScoreManager.hpp"

/////////////////////////////////////////////////
StateHighScores::StateHighScores(Tetris& tetris) : GameState(tetris)
{
    // Loading resources
    m_bgTexture.loadFromFile("resources/images/highscores_background.png");
    m_bgSprite.setTexture(m_bgTexture);

    m_font.loadFromFile("resources/fonts/visitor1.ttf");

    // Loading the scores
    ScoreManager scores(5);
    scores.loadFromFile("resources/scores");

    // Creating the score texts
    for(unsigned int i = 0; i < 5 && i < scores.getNbScores(); i++)
    {
        Score s = scores.getScore(i);

        std::stringstream strRank;
        strRank << i+1 << ".";

        std::stringstream strScore;
        strScore << s.score;

        m_scoresText.push_back(std::vector< sf::Text >());

        m_scoresText[i].push_back(sf::Text(strRank.str(), m_font));
        m_scoresText[i].push_back(sf::Text(s.player, m_font));
        m_scoresText[i].push_back(sf::Text(strScore.str(), m_font));

        m_scoresText[i][0].setColor(sf::Color(0, 80, 154));
        m_scoresText[i][0].setPosition(90 - m_scoresText[i][0].getGlobalBounds().width, 290 + i * 35);
        m_scoresText[i][1].setColor(sf::Color(0, 80, 154));
        m_scoresText[i][1].setPosition(100, 290 + i * 35);
        m_scoresText[i][2].setColor(sf::Color(0, 80, 154));
        m_scoresText[i][2].setPosition(530 - m_scoresText[i][2].getGlobalBounds().width, 290 + i * 35);
    }
}


/////////////////////////////////////////////////
void StateHighScores::handleEvents()
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
void StateHighScores::logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateHighScores::render()
{
    m_window.clear();
    m_window.draw(m_bgSprite);
    for(unsigned int i = 0; i < m_scoresText.size(); i++)
    {
        m_window.draw(m_scoresText[i][0]);
        m_window.draw(m_scoresText[i][1]);
        m_window.draw(m_scoresText[i][2]);
    }
    m_window.display();
}
