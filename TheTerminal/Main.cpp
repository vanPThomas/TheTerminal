#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include "EnvironmentManager.h"
#include "Root.h"
#include "HardDrive.h"
#include "MethodLibrary.h"

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int fontSize = 20;
    const int codeSpeed = 5;

    InitWindow(screenWidth, screenHeight, "OS Simulator");
    SetTargetFPS(60);

    ToggleFullscreen();

    HardDrive* hardDrive = new HardDrive("A", 32768);
    HardDrive* hardDrive2 = new HardDrive("B", 16384);
    Root* root = new Root();
    root->addHardDrive(hardDrive);
    root->addHardDrive(hardDrive2);
    Folder* folder = new Folder("TESTFOLDER", NULL);
    Folder* folder2 = new Folder("TEST", folder);
    folder->addFolderToFolders(folder2);
    hardDrive2->addFolder(folder);
    EnvironmentManager* em = new EnvironmentManager(root->getRootPrompt(), root);
    bool hasBooted = false;
    bool waiting = false;
    float bootNextUpdate = MethodLibrary::getRandomNumber(500, 2000) / 1000;
    float currentBootTime = 0.0f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!hasBooted)
        {
            if (currentBootTime > bootNextUpdate)
            {
                bootNextUpdate = MethodLibrary::getRandomNumber(100, 300) / 1000.0f;
                currentBootTime = 0.0f;
                hasBooted = em->bootSequence();
                em->printCommandHistory();
            }
            else
            {
                currentBootTime += GetFrameTime();
                em->printCommandHistory();
            }
        }
        else
        {
            em->detectKeyPress();
            em->detectReturnPress();
            em->printEverythingToScreen();
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}