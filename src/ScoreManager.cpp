/////////////////////////////////////////////////
/// \file ScoreManager.cpp
/// \brief Implementation of the ScoreManager class.
/// \author Benjamin Ganty
/// \date 22nd November 2011
/// \version 1.0
/////////////////////////////////////////////////

#include "ScoreManager.hpp"

#include <fstream>

/////////////////////////////////////////////////
ScoreManager::ScoreManager(unsigned int nbScores) : m_nbScores(nbScores)
{}


/////////////////////////////////////////////////
ScoreManager::~ScoreManager()
{}


/////////////////////////////////////////////////
void ScoreManager::LoadFromFile(std::string fileName)
{
    m_scores.clear();

    // Opens the file
    std::ifstream file;
    file.open(fileName.c_str());

    // File reading
    while(!file.eof() && m_scores.size() < m_nbScores)
    {
        Score s;
        file >> s.player;
        file >> s.score;

        m_scores.push_back(s);
    }

    file.close();
}


/////////////////////////////////////////////////
void ScoreManager::Write(std::string fileName)
{
    std::ofstream file;
    file.open(fileName.c_str());
    file.clear();

    // Writing into the file
    for(unsigned int i = 0; i < m_scores.size() && i < m_nbScores; i++)
    {
        if(i > 0)
            file << std::endl;
        file << m_scores[i].player << " " << m_scores[i].score;
    }

    file.close();
}


/////////////////////////////////////////////////
bool ScoreManager::IsNewScore(unsigned int score)
{
    if(m_scores.size() < m_nbScores)
        return true;

    for(unsigned int i = 0; i < m_nbScores; i++)
    {
        if(score >= m_scores[i].score)
            return true;
    }

    return false;
}


/////////////////////////////////////////////////
void ScoreManager::AddScore(std::string player, unsigned int score)
{
    bool added = false;

    for(std::vector<Score>::iterator it = m_scores.begin(); it != m_scores.end(); it++)
    {
        if(score >= it->score)
        {
            m_scores.insert(it, Score{player, score});
            added = true;
            break;
        }
    }

    if(!added)
        m_scores.push_back(Score{player, score});

    if(m_scores.size() > m_nbScores)
        m_scores.erase(m_scores.begin() + m_nbScores);
}


/////////////////////////////////////////////////
unsigned int ScoreManager::GetNbScores()
{
    return m_scores.size();
}


/////////////////////////////////////////////////
Score ScoreManager::GetScore(unsigned int index)
{
    if(index < m_scores.size())
        return m_scores[index];

    return Score{"", 0};
}
