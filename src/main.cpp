/////////////////////////////////////////////////
/// \file main.cpp
/// \brief Contains the program's main function.
/// \author Benjamin Ganty
/// \date 15th November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "Tetris.hpp"

/////////////////////////////////////////////////
/// \brief Main function of the program.
///
/// Create a Tetris instance and run the game.
///
/// \param argc : Number of given command-line parameters.
/// \param argv : Command-line parameters.
/// \return Program ending status code.
/////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    Tetris tetris;

    tetris.Run();

    return EXIT_SUCCESS;
}
