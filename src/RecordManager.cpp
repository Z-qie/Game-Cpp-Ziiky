
#pragma once
#include <vector>

#include "header.h"
#include "Zy21586Engine.h"
#include "RecordManager.h"
#include <iostream>
#include <fstream>
#include <string>

RecordManager* RecordManager::pRecordManager = nullptr;

RecordManager* RecordManager::getInstance()
{
    if (pRecordManager == nullptr) {
        pRecordManager = new RecordManager();
    }
    return pRecordManager;
}

RecordManager::RecordManager()
{
    // read file
    readRecordFromFile();

};

void RecordManager::updateInGameData(int second, int numOfRune, int numOfKill, int HP) {
    m_iThisSecond = second;
    m_iThisNumofRune = numOfRune;
    m_iThisNumOfKill = numOfKill;
    m_iThisHP = HP;
}

const std::vector<std::string>& RecordManager::decodeResult() {
    m_ioResultText.clear();
    // RUNE ACTIVITED: (8*space) xx
    m_ioResultText.push_back(std::string("RUNE ACTIVITED: ") + std::to_string(m_iThisNumofRune));

    // TIME: xx:xx 
    //             [RECORD!] (LONGEST: xx:xx by XXXX)
    //             [RECORD!] (SHORTEST: xx:xx by XXXX)
    std::string timeStr = "SURVIVING TIME: " + utils_getTimeStr(m_iThisSecond);
    m_ioResultText.push_back(timeStr);

    std::string timeStrLS = "    (LONGEST: " + utils_getTimeStr(m_iLongestSecond) + " by " + m_ioNameOfLS + ")";
    if (m_iThisSecond > m_iLongestSecond)
        timeStrLS += " [RECORD!]";
    m_ioResultText.push_back(timeStrLS);

    std::string timeStrSS = "    (SHORTEST: " + utils_getTimeStr(m_iShorestSecond) + " by " + m_ioNameOfSS + ")";
    if (m_iThisSecond < m_iShorestSecond)
        timeStrSS += " [RECORD!]";
    m_ioResultText.push_back(timeStrSS);

    // KILL: xx    [RECORD!] (Best: 100 by XXXX)
    std::string killStr = "MAX KILL: " + std::to_string(m_iThisNumOfKill);
    killStr += " (BEST:  " + std::to_string(m_iHighestKill) + " by " + m_ioNameOfHK + ")";
    if (m_iThisNumOfKill > m_iHighestKill)
        killStr += " [RECORD!] ";
    m_ioResultText.push_back(killStr);

    // HP: xx [RECORD!] (Best: 100 by XXXX)
    std::string HPStr = "REMAINING HP: " + std::to_string(m_iThisHP);
    HPStr += " (BEST:  " + std::to_string(m_iHighestHP) + " by " + m_ioNameOfHP + ")";
    if (m_iThisHP > m_iHighestHP)
        HPStr += " [RECORD!] ";
    m_ioResultText.push_back(HPStr);

    /*for (size_t i = 0; i < 6; i++)
        std::cout << m_ioResultText[i] << std::endl;*/

    return m_ioResultText;
}

void RecordManager::readRecordFromFile() {
    std::string line;
    std::ifstream myfile("record.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            if (line == "_LONGEST") {
                getline(myfile, line);
                m_iLongestSecond = stoi(line);
                getline(myfile, line);
                m_ioNameOfLS = line;
                continue;
            }
            if (line == "_SHORTEST") {
                getline(myfile, line);
                m_iShorestSecond = stoi(line);
                getline(myfile, line);
                m_ioNameOfSS = line;
                continue;
            }
            if (line == "_KILL") {
                getline(myfile, line);
                m_iHighestKill = stoi(line);
                getline(myfile, line);
                m_ioNameOfHK = line;
                continue;
            }
            if (line == "_HP") {
                getline(myfile, line);
                m_iHighestHP = stoi(line);
                getline(myfile, line);
                m_ioNameOfHP = line;
                continue;
            }
        }
        myfile.close();
    }
    else {
        std::cout << "cannot find the record file" << std::endl;
    }
}


void RecordManager::updateRecordToFile(std::string playerName) {
    //_LONGEST
    if (m_iThisSecond > m_iLongestSecond) {
        m_iLongestSecond = m_iThisSecond;
        m_ioNameOfLS = playerName;
    }
    //_SHORTEST
    if (m_iThisSecond < m_iShorestSecond) {
        m_iShorestSecond = m_iThisSecond;
        m_ioNameOfSS = playerName;
    }
    //_KILL
    if (m_iThisNumOfKill > m_iHighestKill) {
        m_iHighestKill = m_iThisNumOfKill;
        m_ioNameOfHK = playerName;
    }
    //_HP
    if (m_iThisHP > m_iHighestHP) {
        m_iHighestHP = m_iThisHP;
        m_ioNameOfHP = playerName;
    }

    std::ofstream myfile("record.txt");
    if (myfile.is_open())
    {
        myfile << "_LONGEST\n";
        myfile << m_iLongestSecond << "\n";
        myfile << m_ioNameOfLS << "\n";


        myfile << "_SHORTEST\n";
        myfile << m_iShorestSecond << "\n";
        myfile << m_ioNameOfSS << "\n";

        myfile << "_KILL\n";
        myfile << m_iHighestKill << "\n";
        myfile << m_ioNameOfHK << "\n";

        myfile << "_HP\n";
        myfile << m_iHighestHP << "\n";
        myfile << m_ioNameOfHP << "\n";

        myfile.close();
    }
    else std::cout << "Unable to open file" << std::endl;

}

const std::vector<std::string>& RecordManager::decodeRecord() {

    m_ioResultText.clear();

    // TIME: xx:xx 
    //             [RECORD!] (LONGEST: xx:xx by XXXX)
    //             [RECORD!] (SHORTEST: xx:xx by XXXX)
    std::string timeStr = "SURVIVING TIME: ";
    m_ioResultText.push_back(timeStr);

    std::string timeStrLS = "    LONGEST:   " + utils_getTimeStr(m_iLongestSecond) + "  by  " + m_ioNameOfLS;
    m_ioResultText.push_back(timeStrLS);

    std::string timeStrSS = "    SHORTEST:   " + utils_getTimeStr(m_iShorestSecond) + "  by  " + m_ioNameOfSS;
    m_ioResultText.push_back(timeStrSS);

    // KILL: xx    [RECORD!] (Best: 100 by XXXX)
    std::string killStr = "MAX KILL:   ";
    killStr += std::to_string(m_iHighestKill) + "  by  " + m_ioNameOfHK;

    m_ioResultText.push_back(killStr);

    // HP: xx [RECORD!] (Best: 100 by XXXX)
    std::string HPStr = "REMAINING HP:   ";
    HPStr += std::to_string(m_iHighestHP) + "  by  " + m_ioNameOfHP;
    m_ioResultText.push_back(HPStr);

    return m_ioResultText;
}


void RecordManager::resetRecordFile() {
    std::ofstream myfile("record.txt");
    if (myfile.is_open())
    {
        myfile << "_LONGEST\n";
        myfile << "0" << "\n";
        myfile << "NO-RECORD" << "\n";


        myfile << "_SHORTEST\n";
        myfile << "999999" << "\n";
        myfile << "NO-RECORD" << "\n";

        myfile << "_KILL\n";
        myfile << "0" << "\n";
        myfile << "NO-RECORD" << "\n";

        myfile << "_HP\n";
        myfile << "0" << "\n";
        myfile << "NO-RECORD" << "\n";
        myfile.close();
    }
    else std::cout << "Unable to open file" << std::endl;

    // update real time data again
    readRecordFromFile();
}