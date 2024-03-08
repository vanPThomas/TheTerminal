#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include "EnvironmentManager.h"
#include "Root.h"
#include "HardDrive.h"

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int fontSize = 20;
    const int codeSpeed = 5;

    InitWindow(screenWidth, screenHeight, "OS Simulator");
    SetTargetFPS(60);

    ToggleFullscreen();

    HardDrive hd{ "A", 32768 };
    HardDrive hd2{ "B", 16384 };
    Root* root = new Root();
    root->addHardDrive(hd);
    root->addHardDrive(hd2);
    EnvironmentManager* em = new EnvironmentManager(root->getRootPrompt(), root);
    std::string systemBootingMessage = "HoloGeisha OS booting ...";
    em->addToCommandHistory(systemBootingMessage);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        em->detectKeyPress();
        em->detectReturnPress();
        em->printEverythingToScreen();
        EndDrawing();
    }



    CloseWindow();
    return 0;
}