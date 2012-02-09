/////////////////////////////////////////////////
/// \file StatePlay.cpp
/// \brief Implementation of the StatePlay class.
/// \author Benjamin Ganty
/// \date 23rd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "StatePlay.hpp"

#include <sstream>

#include <SFML/Window/Event.hpp>

#include "Tetris.hpp"
#include "ScoreManager.hpp"
#include "BlockMap.hpp"
#include "Figure.hpp"

/////////////////////////////////////////////////
StatePlay::StatePlay(Tetris& tetris) :
    GameState(tetris),
    m_map(tetris, m_blocksSpritesheet),
    m_score(0),
    m_lvl(0),
    m_linesDestroyed(0),
    m_normalGameSpeed(450),
    m_gameSpeed(m_normalGameSpeed),
    m_gameOver(false),
    m_gameOverTimer(0),
    m_moveDownTimer(0),
    m_figMoveDirection(DIRECT_NULL),
    m_rotate(false)
{
    // Loading and initializing resources
    m_bgTexture.LoadFromFile("resources/images/play_background.png");
    m_bgSprite.SetTexture(m_bgTexture);

    m_gameOverTexture.LoadFromFile("resources/images/game_over.png");
    m_gameOverSprite.SetTexture(m_gameOverTexture);
    m_gameOverSprite.SetPosition(m_window.GetWidth()/2 - m_gameOverSprite.GetSize().x/2,
                                 m_window.GetHeight()/2 - m_gameOverSprite.GetSize().y/2);

    m_blocksSpritesheet.LoadFromFile("resources/images/blocks_spritesheet.png");

    m_font.LoadFromFile("resources/fonts/visitor1.ttf");

    // Creating the texts
    m_textScore.SetFont(m_font);
    m_textScore.SetColor(sf::Color(205, 5, 5));
    m_textLvl.SetFont(m_font);
    m_textLvl.SetColor(sf::Color(205, 5, 5));
    m_textLinesDestroyed.SetFont(m_font);
    m_textLinesDestroyed.SetColor(sf::Color(205, 5, 5));

    UpdateTexts();

    // Initializing the figures
    m_currentFig = GenerateRandomFig();
    m_nextFig = GenerateRandomFig();
    m_nextFig->SetNextFigPos();
}


/////////////////////////////////////////////////
StatePlay::~StatePlay()
{
    delete m_currentFig;
    delete m_nextFig;
}


/////////////////////////////////////////////////
void StatePlay::HandleEvents()
{
    sf::Event ev;
    while(m_window.PollEvent(ev))
    {
        // X window button
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

            // Space pressed
            case sf::Keyboard::Space:
                m_rotate = true;
                break;

            // Left pressed
            case sf::Keyboard::Left:
                m_figMoveDirection = DIRECT_LEFT;
                break;

            // Right pressed
            case sf::Keyboard::Right:
                m_figMoveDirection = DIRECT_RIGHT;
                break;

            default:
                break;
            }
        }
    }

    // Setting the game speed. Faster if "Down" is pressed.
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Down))
        m_gameSpeed = m_normalGameSpeed / 10;
    else
        m_gameSpeed = m_normalGameSpeed;
}


/////////////////////////////////////////////////
void StatePlay::Logic(sf::Uint32 elapsedTime)
{
    m_moveDownTimer += elapsedTime;

    // If the game isn't over
    if(!m_gameOver)
    {
        // Lateral movement
        if(m_figMoveDirection != DIRECT_NULL)
        {
            Figure movedFig = *m_currentFig;
            movedFig.Move(m_figMoveDirection);

            // Moves the figure if no collision detected
            if(!m_map.Collision(movedFig))
                m_currentFig->Move(m_figMoveDirection);

            m_figMoveDirection = DIRECT_NULL;
        }

        // Rotation
        if(m_rotate)
        {
            Figure rotatedFig = *m_currentFig;
            rotatedFig.Rotate();

            // Rotates the figure if no collision detected
            if(!m_map.Collision(rotatedFig))
                m_currentFig->Rotate();

            m_rotate = false;
        }

        // Downward movement
        if(m_moveDownTimer >= m_gameSpeed)
        {
            Figure movedFig = *m_currentFig;
            movedFig.Move(DIRECT_DOWN);

            // If the figure can't go down any more (collision)
            if(m_map.Collision(movedFig))
            {
                // Test for game over
                if(m_currentFig->IsOutOfGame())
                    m_gameOver = true;
                else
                {
                    // Adding the figure's blocks to the map and creating new figures
                    // (next figure becomes the current one).
                    m_map.AddFigure(*m_currentFig);

                    delete m_currentFig;
                    m_currentFig = new Figure(m_tetris, m_nextFig->GetType(), m_blocksSpritesheet);

                    delete m_nextFig;
                    m_nextFig = GenerateRandomFig();
                    m_nextFig->SetNextFigPos();
                }
            }
            else
                m_currentFig->Move(DIRECT_DOWN);

            m_moveDownTimer = 0;

            // Searching for completed lines and adding score
            IncScore(m_map.DestroyCompleteLines());
        }
    }
    // End of game
    else
    {
        if(m_gameOverTimer >= 2000)
        {
            ScoreManager scores(5);
            scores.LoadFromFile("resources/scores");

            // Checking if the score is a new high score
            if(m_score > 0 && scores.IsNewScore(m_score))
                m_tetris.SetNextState(STATE_NEW_SCORE);
            else
                m_tetris.SetNextState(STATE_MENU);
        }
        else
            m_gameOverTimer += elapsedTime;
    }
}


/////////////////////////////////////////////////
void StatePlay::Render()
{
    m_window.Clear();

    m_window.Draw(m_bgSprite);
    m_window.Draw(m_textScore);
    m_window.Draw(m_textLvl);
    m_window.Draw(m_textLinesDestroyed);

    m_map.Draw();
    m_currentFig->Draw();
    m_nextFig->Draw();

    if(m_gameOver)
        m_window.Draw(m_gameOverSprite);

    m_window.Display();
}


/////////////////////////////////////////////////
unsigned long StatePlay::GetScore()
{
    return m_score;
}


/////////////////////////////////////////////////
void StatePlay::IncScore(unsigned int nbLinesDestroyed)
{
    // Increasing the score
    switch(nbLinesDestroyed)
    {
    case 1:
        m_score += 40 * (m_lvl + 1);
        break;
    case 2:
        m_score += 100 * (m_lvl + 1);
        break;
    case 3:
        m_score += 300 * (m_lvl + 1);
        break;
    case 4:
        m_score += 1200 * (m_lvl + 1);
        break;
    default:
        break;
    }

    m_linesDestroyed += nbLinesDestroyed;

    // Checks for increasing level
    if(m_linesDestroyed / 10 > m_lvl)
    {
        m_lvl = m_linesDestroyed / 10;

        // Increasing difficulty (game speed)
        if(m_normalGameSpeed > 100)
            m_normalGameSpeed -= 50;
    }

    UpdateTexts();
}


/////////////////////////////////////////////////
void StatePlay::UpdateTexts()
{
    std::stringstream scoreStr;
    scoreStr << m_score;
    m_textScore.SetString(scoreStr.str());
    m_textScore.SetPosition(450 - m_textScore.GetRect().Width / 2, 220);

    std::stringstream lvlStr;
    lvlStr << m_lvl;
    m_textLvl.SetString(lvlStr.str());
    m_textLvl.SetPosition(375 - m_textLvl.GetRect().Width / 2, 345);

    std::stringstream linesStr;
    linesStr << m_linesDestroyed;
    m_textLinesDestroyed.SetString(linesStr.str());
    m_textLinesDestroyed.SetPosition(525 - m_textLinesDestroyed.GetRect().Width / 2, 345);
}


/////////////////////////////////////////////////
Figure* StatePlay::GenerateRandomFig()
{
    BlockType type = (BlockType)(rand() % (LAST_BLOCK_TYPE + 1) + FIRST_BLOCK_TYPE);

    return new Figure(m_tetris, type, m_blocksSpritesheet);
}
