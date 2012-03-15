#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

/////////////////////////////////////////////////
/// \file ScoreManager.hpp
/// \brief Declaration of the ScoreManager class.
/// \author Benjamin Ganty
/// \date 22nd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include <string>
#include <vector>

/////////////////////////////////////////////////
/// \struct Score
/// \brief Contains a player's name and the player's score.
/////////////////////////////////////////////////
struct Score
{
    std::string player; ///< Player's name
    unsigned int score; ///< Player's score
};

/////////////////////////////////////////////////
/// \class ScoreManager
/// \brief ScoreManager is used to read / write / compare scores.
///
/// This manager provides the ability to load and write scores.
/// Score comparison is also possible.
/// High scores are stored in this manager.
/////////////////////////////////////////////////
class ScoreManager
{
    public:

        /////////////////////////////////////////////////
        /// \brief Constructor
        ///
        /// Initializes the object.
        ///
        /// \param nbScores : The maximum number of scores to manage.
        /////////////////////////////////////////////////
        ScoreManager(unsigned int nbScores);

        /////////////////////////////////////////////////
        /// \brief Destructor
        ///
        /// Virtual declaration.
        /////////////////////////////////////////////////
        virtual ~ScoreManager();

        /////////////////////////////////////////////////
        /// \brief Scores loading.
        ///
        /// Loads the scores from a file.
        ///
        /// \param fileName : The file in which the scores a stored.
        /////////////////////////////////////////////////
        void loadFromFile(std::string fileName);

        /////////////////////////////////////////////////
        /// \brief Scores writing.
        ///
        /// Writes the scores into a file.
        ///
        /// \param fileName : The file in which the scores have to be written.
        /////////////////////////////////////////////////
        void write(std::string fileName);

        /////////////////////////////////////////////////
        /// \brief Score comparison.
        ///
        /// Tells if a score is higher than one the stored scores or not.
        ///
        /// \param score : The score compare.
        ///
        /// \return True if score is a new high score, otherwise False.
        /////////////////////////////////////////////////
        bool isNewScore(unsigned int score);

        /////////////////////////////////////////////////
        /// \brief Adding score.
        ///
        /// Adds a score if it is higher
        ///
        /// \param player : The player's name.
        /// \param score : The score.
        /////////////////////////////////////////////////
        void addScore(std::string player, unsigned int score);

        /////////////////////////////////////////////////
        /// \brief Returns the number of stored scores.
        ///
        /// \return Number of stored scores.
        /////////////////////////////////////////////////
        unsigned int getNbScores();

        /////////////////////////////////////////////////
        /// \brief Retrieving scores.
        ///
        /// Returns the score that is stored at the specified index. The scores are sorted
        /// in a manner that the higher one is at the index 0, then, 1 , 2, 3, ...
        ///
        /// \param index : The index of the score.
        ///
        /// \return If the given index exists, returns the score of the index.\n
        ///         Else, returns an empty score.
        /////////////////////////////////////////////////
        Score getScore(unsigned int index);

    protected:

        /////////////////////////////////////////////////
        // Member Data
        /////////////////////////////////////////////////
        std::vector<Score>  m_scores;   ///< Scores.
        unsigned int        m_nbScores; ///< Number of scores to read / write / compare
};

#endif // SCOREMANAGER_HPP
