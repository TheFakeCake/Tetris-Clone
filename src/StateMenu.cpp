/////////////////////////////////////////////////
/// \file StateMenu.cpp
/// \brief Implementation of the StateMenu class methods.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "StateMenu.hpp"

#include <SFML/Window/Event.hpp>

#include "Tetris.hpp"

/////////////////////////////////////////////////
StateMenu::StateMenu(Tetris& tetris) : GameState(tetris)
{
    // Loading the resources
    m_bgTexture.loadFromFile("resources/images/menu_background.png");
    m_menuTexture.loadFromFile("resources/images/menu_spritesheet.png");

    // Initializing the background sprite
    m_bgSprite.setTexture(m_bgTexture);

    // Initializing the menu entries
    int entryHeight = m_menuTexture.getHeight() / (MENU_LAST_ENTRY + 1);
    int entryWidth = m_menuTexture.getWidth() / 2;
    m_menuEntries.resize(MENU_LAST_ENTRY + 1);

    for(int i = MENU_FIRST_ENTRY; i <= MENU_LAST_ENTRY; i++)
    {
        m_menuEntries[i].setTexture(m_menuTexture);
        m_menuEntries[i].setTextureRect(sf::IntRect(0, i * entryHeight, entryWidth, entryHeight));
        m_menuEntries[i].setPosition(m_window.getSize().x/2 - entryWidth/2, 300 + i * (entryHeight + 30));
    }

    // Setting the default focused menu entry
    m_focusedEntry = MENU_PLAY;
    m_menuEntries[MENU_PLAY].setTextureRect(sf::IntRect(entryWidth, MENU_PLAY * entryHeight, entryWidth, entryHeight));
}


/////////////////////////////////////////////////
void StateMenu::handleEvents()
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
            switch(ev.key.code)
            {
            // Up pressed -> focus the previous menu entry
            case sf::Keyboard::Up:
                if(m_focusedEntry > MENU_FIRST_ENTRY)
                    setMenuFocus((MenuEntryID)((int)m_focusedEntry - 1));
                break;

            // Down pressed -> focus the next menu entry
            case sf::Keyboard::Down:
                if(m_focusedEntry < MENU_LAST_ENTRY)
                    setMenuFocus((MenuEntryID)((int)m_focusedEntry + 1));
                break;

            // Enter / Space pressed -> sets the next game state
            case sf::Keyboard::Return:
            case sf::Keyboard::Space:

                switch(m_focusedEntry)
                {
                case MENU_PLAY:
                    m_tetris.setNextState(STATE_PLAY);
                    break;
                case MENU_HIGH_SCORES:
                    m_tetris.setNextState(STATE_HIGH_SCORES);
                    break;
                case MENU_HELP:
                    m_tetris.setNextState(STATE_HELP);
                    break;
                case MENU_EXIT:
                    m_tetris.setNextState(STATE_EXIT);
                    break;
                }

                break;

            default:
                break;
            }
        }
    }
}


/////////////////////////////////////////////////
void StateMenu::logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateMenu::render()
{
    m_window.clear();

    m_window.draw(m_bgSprite);
    for(int i = MENU_FIRST_ENTRY; i <= MENU_LAST_ENTRY; i++)
        m_window.draw(m_menuEntries[i]);

    m_window.display();
}


/////////////////////////////////////////////////
void StateMenu::setMenuFocus(MenuEntryID id)
{
    // Size of the entry sprite
    int entryHeight = m_menuTexture.getHeight() / (MENU_LAST_ENTRY + 1);
    int entryWidth = m_menuTexture.getWidth() / 2;

    // Sets the sprites of the old and new focused entries
    m_menuEntries[m_focusedEntry].setTextureRect(sf::IntRect(0, m_focusedEntry * entryHeight, entryWidth, entryHeight));
    m_menuEntries[id].setTextureRect(sf::IntRect(entryWidth, id * entryHeight, entryWidth, entryHeight));

    m_focusedEntry = id;
}
