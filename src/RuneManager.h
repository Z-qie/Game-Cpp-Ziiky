#pragma once

#include <vector>
#include "Utils.h"

class Rune;

class RuneManager
{
private:
    int m_iTotalRuneNumber{ 0 };
    int m_iActiveRuneNumber{ 0 };

    std::vector<Rune*> runes;

protected:
    RuneManager() {};
    static RuneManager* pRuneManager;

public:
    static RuneManager* getInstance();
    ~RuneManager() { pRuneManager = nullptr; };

    void initRuneAt(int x, int y);

    void setTotalRuneNum() { m_iTotalRuneNumber = runes.size(); };
    int getTotalRuneNum() { return m_iTotalRuneNumber; };
    void incrementActiveRuneNum() { ++m_iActiveRuneNumber; };
    int getCurrentRuneNum() { return m_iActiveRuneNumber; };
    bool isAllRuneActivated() { return m_iActiveRuneNumber == m_iTotalRuneNumber; };

    // method only for developer
    void activeAllRunes() { m_iActiveRuneNumber = m_iTotalRuneNumber; };

    std::vector<Rune*>& getRunes() { return runes; };
};
