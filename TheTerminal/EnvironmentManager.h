#pragma once
#include <string>
#include "raylib.h"
#include "Root.h"
class EnvironmentManager
{
public:
    EnvironmentManager(std::string newDiskPromptText, Root *Root);
    float getCursorBlinkTime() { return cursorBlinkTime; }
    float getUpdateTime() { return updateTime; }
    void updateUpdateTime(float updateAmount) { updateTime += updateAmount; }
    bool getBlinkOn() { return blinkOn; }
    std::string getCursorValue() { return cursor; }
    std::string getDiskPromptText(){ return diskPromptText; }
    void setDiskPrompt(std::string newDiskPrompt) { diskPromptText = newDiskPrompt; }
    Vector2 getCursorCoord() { return cursorCoord; }
    Vector2 getTypingCoord() { return typingCoord; }
    Root* getRoot() { return root; }
    std::string getInputString() { return inputString; }
    float getCursorJumpDistance() { return cursorBlinkTime; }
    Font getFont() { return font; }
    void detectKeyPress();
    void detectReturnPress();
    void printEverythingToScreen();
    void addToCommandHistory(std::string stringToAdd);
    Vector2 getDiskPromptTextCoord() { return diskPromptCoord; }
    float getVerticleCoordJump() { return verticalCoordJump; }
    void setDiskPromptCoord(Vector2 newCoord) { diskPromptCoord = newCoord; }

private:
    float cursorBlinkTime = 0.5;
    float updateTime = 0.0;
    bool blinkOn = false;
    float entrySpaceCoord{ 137.0 };
    float verticalCoordJump{ 45 };
    std::string cursor = "_";
    std::string diskPromptText{};
    float cursorJumpDistance = 25.7;
    Vector2 cursorCoord{ static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + cursorJumpDistance, 10 };
    Vector2 typingCoord{ static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, 10 };
    Vector2 historyCoord{10, 10 };
    Vector2 diskPromptCoord{ 10, 10 };
    std::string inputString = "";
    Font font = LoadFont("Px437_IBM_VGA_8x14.ttf");
    std::string commandHistory = "";
    Color envColor = GREEN;
    Root *root{};

};

