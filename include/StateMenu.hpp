#ifndef STATEMENU_HPP
#define STATEMENU_HPP

/////////////////////////////////////////////////
/// \file StateMenu.hpp
/// \brief Declaraction of the StateMenu class.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "GameState.hpp"

/////////////////////////////////////////////////
/// \class StateMenu
/// \brief Menu screen.
///
/// Handles the main menu screen.
/////////////////////////////////////////////////
class StateMenu : public GameState
{
    /////////////////////////////////////////////////
    /// \enum MenuEntryID
    /// \brief Constants that represents menu entries.
    /////////////////////////////////////////////////
    enum MenuEntryID
    {
        MENU_PLAY,                      ///< "Play" entry.
        MENU_HIGH_SCORES,               ///< "High Scores" entry.
        MENU_HELP,                      ///< "Help" entry.
        MENU_EXIT,                      ///< "Exit" entry.
        MENU_FIRST_ENTRY = MENU_PLAY,   ///< The first menu entry ("Play").
        MENU_LAST_ENTRY = MENU_EXIT     ///< The last menu entry ("Exit").
    };

    public:

        /////////////////////////////////////////////////
        /// \brief Constructor.
        ///
        /// Initializes the member data and the menu.
        ///
        /// \param tetris : The parent Tetris object.
        /////////////////////////////////////////////////
        StateMenu(Tetris& tetris);

        /////////////////////////////////////////////////
        /// \brief Events handling.
        ///
        /// Processes all the user inputs.
        /////////////////////////////////////////////////
        void handleEvents();

        /////////////////////////////////////////////////
        /// \brief Logic.
        ///
        /// There is no logic in the menu screen.
        ///
        /// \param elapsedTime : Elapsed time since the last frame.
        /////////////////////////////////////////////////
        void logic(sf::Uint32 elapsedTime);

        /////////////////////////////////////////////////
        /// \brief Rendering.
        ///
        /// Draws on the menu screen on the window.
        /////////////////////////////////////////////////
        void render();

    protected:

        /////////////////////////////////////////////////
        /// \brief Sets the focus on a given menu entry.
        ///
        /// \param id : The menu entry to focus.
        /////////////////////////////////////////////////
        void setMenuFocus(MenuEntryID id);

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        sf::Texture     m_bgTexture;    ///< Background texture.
        sf::Sprite      m_bgSprite;     ///< Background sprite.

        sf::Texture     m_menuTexture;  ///< Menu entries texture (sprites sheet)

        std::vector< sf::Sprite >   m_menuEntries;  ///< Sprites of the menu entries
        MenuEntryID                 m_focusedEntry; ///< The focused menu entry
};

#endif // STATEMENU_HPP
