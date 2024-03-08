#pragma once
#include "EnvironmentManager.h"
#include "CommandHandler.h"

EnvironmentManager::EnvironmentManager(std::string newDiskPromptText, Root *Root) 
{ diskPromptText = newDiskPromptText, 
typingCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + 10, typingCoord.y };
cursorCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, cursorCoord.y };
root = Root;
}

void EnvironmentManager::detectKeyPress()
{
    
    updateTime += GetFrameTime();

    if (updateTime >= cursorBlinkTime)
    {
        blinkOn = !blinkOn;
        updateTime = 0.0;

    }
    if (blinkOn)
        DrawText(cursor.c_str(), cursorCoord.x+10, cursorCoord.y, 40, envColor);

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
    if (IsKeyPressed(KEY_ENTER))
    {
        commandHistory += diskPromptText + " " + inputString + "\n\n\n";
        diskPromptCoord = { diskPromptCoord.x, diskPromptCoord.y + verticalCoordJump };
        CommandHandler::executeCommand(this, inputString);
        typingCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance+10, typingCoord.y + verticalCoordJump };
        cursorCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, cursorCoord.y + verticalCoordJump };
        inputString = "";
    }
}

void EnvironmentManager::printEverythingToScreen()
{
    DrawTextEx(font, commandHistory.c_str(), historyCoord, 40, 3, envColor);
    DrawTextEx(font, diskPromptText.c_str(), diskPromptCoord, 40, 3, envColor);
    typingCoord = { static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + 10, typingCoord.y };
    DrawTextEx(font, inputString.c_str(), typingCoord, 40, 3, envColor);
}

void EnvironmentManager::addToCommandHistory(std::string stringToAdd)
{ 
    commandHistory = commandHistory + stringToAdd + "\n\n\n"; 
    cursorCoord = { cursorCoord.x, cursorCoord.y + verticalCoordJump };
    typingCoord = { typingCoord.x, cursorCoord.y};
    diskPromptCoord = { diskPromptCoord.x, cursorCoord.y};
}
