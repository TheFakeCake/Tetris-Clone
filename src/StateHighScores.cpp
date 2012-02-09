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
    m_bgTexture.LoadFromFile("resources/images/highscores_background.png");
    m_bgSprite.SetTexture(m_bgTexture);

    m_font.LoadFromFile("resources/fonts/visitor1.ttf");

    // Loading the scores
    ScoreManager scores(5);
    scores.LoadFromFile("resources/scores");

    // Creating the score texts
    for(unsigned int i = 0; i < 5 && i < scores.GetNbScores(); i++)
    {
        Score s = scores.GetScore(i);

        std::stringstream strRank;
        strRank << i+1 << ".";

        std::stringstream strScore;
        strScore << s.score;

        m_scoresText.push_back(std::vector< sf::Text >());

        m_scoresText[i].push_back(sf::Text(strRank.str(), m_font));
        m_scoresText[i].push_back(sf::Text(s.player, m_font));
        m_scoresText[i].push_back(sf::Text(strScore.str(), m_font));

        m_scoresText[i][0].SetColor(sf::Color(0, 80, 154));
        m_scoresText[i][0].SetPosition(90 - m_scoresText[i][0].GetRect().Width, 290 + i * 35);
        m_scoresText[i][1].SetColor(sf::Color(0, 80, 154));
        m_scoresText[i][1].SetPosition(100, 290 + i * 35);
        m_scoresText[i][2].SetColor(sf::Color(0, 80, 154));
        m_scoresText[i][2].SetPosition(530 - m_scoresText[i][2].GetRect().Width, 290 + i * 35);
    }
}


/////////////////////////////////////////////////
void StateHighScores::HandleEvents()
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
void StateHighScores::Logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateHighScores::Render()
{
    m_window.Clear();
    m_window.Draw(m_bgSprite);
    for(unsigned int i = 0; i < m_scoresText.size(); i++)
    {
        m_window.Draw(m_scoresText[i][0]);
        m_window.Draw(m_scoresText[i][1]);
        m_window.Draw(m_scoresText[i][2]);
    }
    m_window.Display();
}
