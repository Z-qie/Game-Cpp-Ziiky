#pragma once

#include "Utils.h"

//Handles read/wirte to the record file and return result string list accordingly.
class RecordManager
{
protected:
    RecordManager();
    static RecordManager* pRecordManager;
private:
    // in game data
    int m_iThisSecond{ 0 };
    int m_iThisNumofRune{ 0 };
    int m_iThisNumOfKill{ 0 };
    int m_iThisHP{ 0 };
    // data from record
    int m_iLongestSecond{ 0 };
    int m_iShorestSecond{ 0 };
    int m_iHighestKill{ 0 };
    int m_iHighestHP{ 0 };
    std::string m_ioNameOfLS;
    std::string m_ioNameOfSS;
    std::string m_ioNameOfHK;
    std::string m_ioNameOfHP;

    std::vector<std::string> m_ioResultText;

public:
    static RecordManager* getInstance();

    ~RecordManager()
    {
        pRecordManager = nullptr;
    };

    void readRecordFromFile();
    void updateRecordToFile(std::string playerName);
    void resetRecordFile();
    void updateInGameData(int second, int numOfRune, int numOfKill, int HP);
    const std::vector<std::string>& decodeResult();
    const std::vector<std::string>& decodeRecord();

};

