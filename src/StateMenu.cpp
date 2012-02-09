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
    m_bgTexture.LoadFromFile("resources/images/menu_background.png");
    m_menuTexture.LoadFromFile("resources/images/menu_spritesheet.png");

    // Initializing the background sprite
    m_bgSprite.SetTexture(m_bgTexture);

    // Initializing the menu entries
    int entryHeight = m_menuTexture.GetHeight() / (MENU_LAST_ENTRY + 1);
    int entryWidth = m_menuTexture.GetWidth() / 2;
    m_menuEntries.resize(MENU_LAST_ENTRY + 1);

    for(int i = MENU_FIRST_ENTRY; i <= MENU_LAST_ENTRY; i++)
    {
        m_menuEntries[i].SetTexture(m_menuTexture);
        m_menuEntries[i].SetSubRect(sf::IntRect(0, i * entryHeight, entryWidth, entryHeight));
        m_menuEntries[i].SetPosition(m_window.GetWidth()/2 - entryWidth/2, 300 + i * (entryHeight + 30));
    }

    // Setting the default focused menu entry
    m_focusedEntry = MENU_PLAY;
    m_menuEntries[MENU_PLAY].SetSubRect(sf::IntRect(entryWidth, MENU_PLAY * entryHeight, entryWidth, entryHeight));
}


/////////////////////////////////////////////////
void StateMenu::HandleEvents()
{
    sf::Event ev;
    while(m_window.PollEvent(ev))
    {
        if(ev.Type == sf::Event::Closed)
        {
            // Exit the application if the window is closed
            m_tetris.SetNextState(STATE_EXIT);
        }
        else if(ev.Type == sf::Event::KeyPressed)
        {
            switch(ev.Key.Code)
            {
            // Up pressed -> focus the previous menu entry
            case sf::Keyboard::Up:
                if(m_focusedEntry > MENU_FIRST_ENTRY)
                    SetMenuFocus((MenuEntryID)( (int)m_focusedEntry - 1 ));
                break;

            // Down pressed -> focus the next menu entry
            case sf::Keyboard::Down:
                if(m_focusedEntry < MENU_LAST_ENTRY)
                    SetMenuFocus((MenuEntryID)( (int)m_focusedEntry + 1 ));
                break;

            // Enter / Space pressed -> sets the next game state
            case sf::Keyboard::Return:
            case sf::Keyboard::Space:

                switch(m_focusedEntry)
                {
                case MENU_PLAY:
                    m_tetris.SetNextState(STATE_PLAY);
                    break;
                case MENU_HIGH_SCORES:
                    m_tetris.SetNextState(STATE_HIGH_SCORES);
                    break;
                case MENU_HELP:
                    m_tetris.SetNextState(STATE_HELP);
                    break;
                case MENU_EXIT:
                    m_tetris.SetNextState(STATE_EXIT);
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
void StateMenu::Logic(sf::Uint32 elapsedTime)
{}


/////////////////////////////////////////////////
void StateMenu::Render()
{
    m_window.Clear();

    m_window.Draw(m_bgSprite);
    for(int i = MENU_FIRST_ENTRY; i <= MENU_LAST_ENTRY; i++)
        m_window.Draw(m_menuEntries[i]);

    m_window.Display();
}


/////////////////////////////////////////////////
void StateMenu::SetMenuFocus(MenuEntryID id)
{
    // Size of the entry sprite
    int entryHeight = m_menuTexture.GetHeight() / (MENU_LAST_ENTRY + 1);
    int entryWidth = m_menuTexture.GetWidth() / 2;

    // Sets the sprites of the old and new focused entries
    m_menuEntries[m_focusedEntry].SetSubRect(sf::IntRect(0, m_focusedEntry * entryHeight, entryWidth, entryHeight));
    m_menuEntries[id].SetSubRect(sf::IntRect(entryWidth, id * entryHeight, entryWidth, entryHeight));

    m_focusedEntry = id;
}
