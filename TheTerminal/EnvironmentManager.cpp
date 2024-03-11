#pragma once
#include "EnvironmentManager.h"
#include "CommandHandler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <list>

EnvironmentManager::EnvironmentManager(std::string newDiskPromptText, Root* Root)
{
    diskPromptText = newDiskPromptText;
    typingCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + 10, typingCoord.y };
    cursorCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, cursorCoord.y };
    root = Root;
}

void EnvironmentManager::detectKeyPress()
{
    // detect what key has been pressed
    updateTime += GetFrameTime();

    if (updateTime >= cursorBlinkTime)
    {
        blinkOn = !blinkOn;
        updateTime = 0.0;

    }
    if (blinkOn)
        DrawText(cursor.c_str(), cursorCoord.x + 10, cursorCoord.y, 40, envColor);

    if (IsKeyPressed(KEY_APOSTROPHE)) {
        inputString += "'";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(KEY_SPACE)) {
        inputString += " ";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(KEY_BACKSPACE) && !inputString.empty()) {
        inputString.pop_back();
        Vector2 newCursorCoord{ cursorCoord.x - cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(KEY_COMMA))
    {
        inputString += ",";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(KEY_PERIOD))
    {
        inputString += ".";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(49) && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)))
    {
        inputString += "!";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(50))
    {
        inputString += "?";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(64))
    {
        inputString += "@";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else if (IsKeyPressed(KEY_SLASH))
    {
        inputString += "/";
        Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
        cursorCoord = newCursorCoord;
    }
    else {
        for (int key = KEY_ZERO; key <= KEY_NINE; ++key) {
            if (IsKeyPressed(key)) {
                char character = static_cast<char>(key - KEY_ZERO + '0');
                inputString += character;
                Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
                cursorCoord = newCursorCoord;
            }
        }

        for (int key = KEY_A; key <= KEY_Z; ++key) {
            if (IsKeyPressed(key)) {
                char character = static_cast<char>(key - KEY_A + 'A');
                inputString += character;
                Vector2 newCursorCoord{ cursorCoord.x + cursorJumpDistance, cursorCoord.y };
                cursorCoord = newCursorCoord;
            }
        }
    }
}

void EnvironmentManager::detectReturnPress()
{
    // detect if ENTER was pressed
    if (IsKeyPressed(KEY_ENTER))
    {
        commandHistory += diskPromptText + " " + inputString + "\n\n\n";
        if (!inputString.empty())
        {
            CommandHandler::executeCommand(this, inputString);
        }
        if (GetScreenHeight() - 200 > cursorCoord.y)
        {
            diskPromptCoord = { diskPromptCoord.x, diskPromptCoord.y + verticalCoordJump };
            typingCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + 10, typingCoord.y + verticalCoordJump };
            cursorCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, cursorCoord.y + verticalCoordJump };
        }
        else
        {
            cursorCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, cursorCoord.y };
            historyCoord = { historyCoord.x, historyCoord.y - verticalCoordJump };
        }

        inputString = "";
    }
}

void EnvironmentManager::printEverythingToScreen()
{
    // print everything to screen
    printCommandHistory();
    DrawTextEx(font, diskPromptText.c_str(), diskPromptCoord, 40, 3, envColor);
    typingCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + 10, typingCoord.y };
    DrawTextEx(font, inputString.c_str(), typingCoord, 40, 3, envColor);
}

void EnvironmentManager::addToCommandHistory(std::string stringToAdd)
{
    // add a line to the command history
    commandHistory = commandHistory + stringToAdd + "\n\n\n";
    if (GetScreenHeight() - 200 > cursorCoord.y)
    {
        cursorCoord = { cursorCoord.x, cursorCoord.y + verticalCoordJump };
        typingCoord = { typingCoord.x, typingCoord.y + verticalCoordJump };
        diskPromptCoord = { diskPromptCoord.x, diskPromptCoord.y + verticalCoordJump };
    }
    else
    {
        cursorCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, cursorCoord.y };
        historyCoord = { historyCoord.x, historyCoord.y - verticalCoordJump };
    }
}

bool EnvironmentManager::bootSequence()
{
    // create boot sequence
    if (bootSequencePlace < bootSequenceList.size())
    {
        auto it = std::next(bootSequenceList.begin(), bootSequencePlace);
        std::string bootCommand = *it;

        addToCommandHistory(bootCommand);
        bootSequencePlace++;
        return false;
    }
    else
    {
        return true;
    }
}

void EnvironmentManager::printCommandHistory()
{
    // print command history
    DrawTextEx(font, commandHistory.c_str(), historyCoord, 40, 3, envColor);
}