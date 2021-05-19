#pragma once

#include "header.h"

#include "RuneManager.h"
#include "CaveGenerator.H"
#include "Rune.h"

RuneManager* RuneManager::pRuneManager = nullptr;

RuneManager* RuneManager::getInstance()
{
    if (pRuneManager == nullptr) {
        pRuneManager = new RuneManager();
    }
    return pRuneManager;
}

void RuneManager::initRuneAt(int x, int y) {
    runes.push_back(new Rune(x, y));
}