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
    m_normalGameSpeed(450000),
    m_gameSpeed(m_normalGameSpeed),
    m_gameOver(false),
    m_gameOverTimer(0),
    m_moveDownTimer(0),
    m_figMoveDirection(DIRECT_NULL),
    m_rotate(false)
{
    // Loading and initializing resources
    m_bgTexture.loadFromFile("resources/images/play_background.png");
    m_bgSprite.setTexture(m_bgTexture);

    m_gameOverTexture.loadFromFile("resources/images/game_over.png");
    m_gameOverSprite.setTexture(m_gameOverTexture);
    m_gameOverSprite.setPosition(m_window.getSize().x/2 - m_gameOverSprite.getGlobalBounds().width/2,
                                 m_window.getSize().y/2 - m_gameOverSprite.getGlobalBounds().height/2);

    m_blocksSpritesheet.loadFromFile("resources/images/blocks_spritesheet.png");

    m_font.loadFromFile("resources/fonts/visitor1.ttf");

    // Creating the texts
    m_textScore.setFont(m_font);
    m_textScore.setColor(sf::Color(205, 5, 5));
    m_textLvl.setFont(m_font);
    m_textLvl.setColor(sf::Color(205, 5, 5));
    m_textLinesDestroyed.setFont(m_font);
    m_textLinesDestroyed.setColor(sf::Color(205, 5, 5));

    updateTexts();

    // Initializing the figures
    m_currentFig = generateRandomFig();
    m_nextFig = generateRandomFig();
    m_nextFig->setNextFigPos();
}


/////////////////////////////////////////////////
StatePlay::~StatePlay()
{
    delete m_currentFig;
    delete m_nextFig;
}


/////////////////////////////////////////////////
void StatePlay::handleEvents()
{
    sf::Event ev;
    while(m_window.pollEvent(ev))
    {
        // X window button
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_gameSpeed = m_normalGameSpeed / 10;
    else
        m_gameSpeed = m_normalGameSpeed;
}


/////////////////////////////////////////////////
void StatePlay::logic(sf::Uint32 elapsedTime)
{
    m_moveDownTimer += elapsedTime;

    // If the game isn't over
    if(!m_gameOver)
    {
        // Lateral movement
        if(m_figMoveDirection != DIRECT_NULL)
        {
            Figure movedFig = *m_currentFig;
            movedFig.move(m_figMoveDirection);

            // Moves the figure if no collision detected
            if(!m_map.collision(movedFig))
                m_currentFig->move(m_figMoveDirection);

            m_figMoveDirection = DIRECT_NULL;
        }

        // Rotation
        if(m_rotate)
        {
            Figure rotatedFig = *m_currentFig;
            rotatedFig.rotate();

            // Rotates the figure if no collision detected
            if(!m_map.collision(rotatedFig))
                m_currentFig->rotate();

            m_rotate = false;
        }

        // Downward movement
        if(m_moveDownTimer >= m_gameSpeed)
        {
            Figure movedFig = *m_currentFig;
            movedFig.move(DIRECT_DOWN);

            // If the figure can't go down any more (collision)
            if(m_map.collision(movedFig))
            {
                // Test for game over
                if(m_currentFig->isOutOfGame())
                    m_gameOver = true;
                else
                {
                    // Adding the figure's blocks to the map and creating new figures
                    // (next figure becomes the current one).
                    m_map.addFigure(*m_currentFig);

                    delete m_currentFig;
                    m_currentFig = new Figure(m_tetris, m_nextFig->getType(), m_blocksSpritesheet);

                    delete m_nextFig;
                    m_nextFig = generateRandomFig();
                    m_nextFig->setNextFigPos();
                }
            }
            else
                m_currentFig->move(DIRECT_DOWN);

            m_moveDownTimer = 0;

            // Searching for completed lines and adding score
            incScore(m_map.destroyCompleteLines());
        }
    }
    // End of game
    else
    {
        if(m_gameOverTimer >= 2000)
        {
            ScoreManager scores(5);
            scores.loadFromFile("resources/scores");

            // Checking if the score is a new high score
            if(m_score > 0 && scores.isNewScore(m_score))
                m_tetris.setNextState(STATE_NEW_SCORE);
            else
                m_tetris.setNextState(STATE_MENU);
        }
        else
            m_gameOverTimer += elapsedTime;
    }
}


/////////////////////////////////////////////////
void StatePlay::render()
{
    m_window.clear();

    m_window.draw(m_bgSprite);
    m_window.draw(m_textScore);
    m_window.draw(m_textLvl);
    m_window.draw(m_textLinesDestroyed);

    m_map.draw();
    m_currentFig->draw();
    m_nextFig->draw();

    if(m_gameOver)
        m_window.draw(m_gameOverSprite);

    m_window.display();
}


/////////////////////////////////////////////////
unsigned long StatePlay::getScore()
{
    return m_score;
}


/////////////////////////////////////////////////
void StatePlay::incScore(unsigned int nbLinesDestroyed)
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

    updateTexts();
}


/////////////////////////////////////////////////
void StatePlay::updateTexts()
{
    std::stringstream scoreStr;
    scoreStr << m_score;
    m_textScore.setString(scoreStr.str());
    m_textScore.setPosition(450 - m_textScore.getGlobalBounds().width / 2, 220);

    std::stringstream lvlStr;
    lvlStr << m_lvl;
    m_textLvl.setString(lvlStr.str());
    m_textLvl.setPosition(375 - m_textLvl.getGlobalBounds().width / 2, 345);

    std::stringstream linesStr;
    linesStr << m_linesDestroyed;
    m_textLinesDestroyed.setString(linesStr.str());
    m_textLinesDestroyed.setPosition(525 - m_textLinesDestroyed.getGlobalBounds().width / 2, 345);
}


/////////////////////////////////////////////////
Figure* StatePlay::generateRandomFig()
{
    BlockType type = (BlockType)(rand() % (LAST_BLOCK_TYPE + 1) + FIRST_BLOCK_TYPE);

    return new Figure(m_tetris, type, m_blocksSpritesheet);
}
