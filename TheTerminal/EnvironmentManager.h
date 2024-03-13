#pragma once
#include <string>
#include <list>
#include "raylib.h"
#include "Root.h"
#include "HardDrive.h"
class EnvironmentManager
{
public:
    EnvironmentManager(std::string g, Root* Root);
    float getCursorBlinkTime() { return cursorBlinkTime; }
    float getUpdateTime() { return updateTime; }
    void updateUpdateTime(float updateAmount) { updateTime += updateAmount; }
    bool getBlinkOn() { return blinkOn; }
    std::string getCursorValue() { return cursor; }
    std::string getDiskPromptText() { return diskPromptText; }
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
    void setCommandHistory(std::string newCommandHistory) { commandHistory = newCommandHistory; }
    Vector2 getDiskPromptTextCoord() { return diskPromptCoord; }
    float getVerticleCoordJump() { return verticalCoordJump; }
    void setDiskPromptCoord(Vector2 newCoord) { diskPromptCoord = newCoord; }
    bool bootSequence();
    void printCommandHistory();
    void setCurrentDriveLocation(HardDrive* hd) { currentDriveLocation = hd; }
    HardDrive* getCurrentDriveLocation() { return currentDriveLocation; }
    void setCurrentFolderLocation(Folder* folder) { currentFolderLocation = folder; }
    Folder* getCurrentFolderLocation() { return currentFolderLocation; }
    std::list<std::string> getCurrentPath() { return currentPath; }
    void setCurrentPath(std::list<std::string> newCurentPath) { currentPath = newCurentPath; }
    void setHistoryCoord(Vector2 newHistoryCoord) { historyCoord = newHistoryCoord; }
    void setCursorCoord(Vector2 newCursorCoord) { cursorCoord = newCursorCoord; }
    void setTypingCoord(Vector2 newTypingCoord) { typingCoord = newTypingCoord; }

private:
    float cursorBlinkTime = 0.5f;
    float updateTime = 0.0f;
    bool blinkOn = false;
    float entrySpaceCoord{ 137.0f };
    float verticalCoordJump{ 45.0f };
    std::string cursor = "_";
    std::string diskPromptText{};
    float cursorJumpDistance = 25.7f;
    Vector2 cursorCoord{ static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance + cursorJumpDistance, 10 };
    Vector2 typingCoord{ static_cast<float>(diskPromptText.length()) * cursorJumpDistance + cursorJumpDistance, 10 };
    Vector2 historyCoord{ 10, 10 };
    Vector2 diskPromptCoord{ 10, 10 };
    std::string inputString = "";
    Font font = LoadFont("Px437_IBM_VGA_8x14.ttf");
    std::string commandHistory = "";
    Color envColor = GREEN;
    Root* root{};
    HardDrive* currentDriveLocation{};
    Folder* currentFolderLocation{};
    std::list<std::string> currentPath{};

    std::list<std::string> bootSequenceList = {
        "Detecting CPU ..." ,
        "Initiating the Kishimoto D42 microprocessor",
        "with an advanced RISC architecture.",
        "Verifying firmware compatibility: NeoFlash BIOS v1.3.7.",
        "Firmware Warning: NeoFlash BIOS version outdated.",
        "Consider upgrading for enhanced performance.",
        "Initializing Zephyr chipset (v2.7)...",
        "Detecting graphics card ...",
        "Identified Komorebi CGA video adapter with 320x200 resolution.",
        "Detecting sound card...",
        "Found Utahime PC speaker for basic beep tones.",
        "Detecting storage device ...",
        "Discovering 5.25\" floppy drive and 10 MB NeoFlash hard disk.",
        "Error: Disk read failure on the 5.25\" floppy drive.",
        "Check for floppy disk and retry."
        "Detecting network interface...",
        "Identified ArgentTech Ethernet card with 10Mbps speed.",
        "Detecting mouse device...",
        "Found Sakura Gakuin Mouse with ball tracking.",
        "Peripheral Failure: Sakura Gakuin Mouse ball tracking malfunction.",
        "Replace or clean the ball.",
        "Detecting keyboard device...",
        "Detected Yuriko Model P keyboard with tactile feedback.",
        "Optimizing tactile feedback algorithms for the Yuriko Model P keyboard.",
        "Detecting printer device...",
        "Identified KanjiBlast matrix printer with 80 columns of text output.",
        "Finished detecting hardware, starting system services...",
        "",
        "Kishimoto Systems presents ...",
        "The Fade proudly unveils...",
        "HoloGeisha OS is booting ...",
        "Loading Knight OS Kernel",
        "Starting memory management...",
        "Initializing Chang file system...",
        "Configuring network interfaces...",
        "Connecting to the cyberweb...",
        "Error 404: Cyberweb not found. Attempting reconnection...",
        "Connected to the Cyberweb",
        "Setting up virtual consoles...",
        "Detecting hardware drivers...",
        "Calibrating timers and clocks...",
        "Launching init process...",
        "Starting daemons...",
        "Enabling logging and debugging facilities...",
        "Running user authentication services...",
        "Initiating system services...",
        "Loading last session state...",
        "Finished booting, welcome to HoloGeisha OS!",
        ""
    };
    int bootSequencePlace = 0;
};

