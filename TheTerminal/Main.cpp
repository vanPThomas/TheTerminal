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

    Image myImage = LoadImage("31589011-cdbc122c-b1bf-11e7-986f-2ebf6bcb8777.png");
    Texture2D texture = LoadTextureFromImage(myImage);
    UnloadImage(myImage);

    //create temporary system
    HardDrive* hardDrive = new HardDrive("A", 32768);
    HardDrive* hardDrive2 = new HardDrive("B", 16384);
    Root* root = new Root();
    root->addHardDrive(hardDrive);
    root->addHardDrive(hardDrive2);
    Folder* folder = new Folder("SYSTEM", NULL);
    Folder* folder2 = new Folder("DRIVERS", folder);
    folder->addFolderToFolders(folder2);
    hardDrive2->addFolder(folder);
    EnvironmentManager* em = new EnvironmentManager(root->getRootPrompt(), root);

    //boot sequence variables
    bool hasBooted = false;
    bool waiting = false;
    float bootNextUpdate = MethodLibrary::getRandomNumber(500, 2000) / 1000;
    float currentBootTime = 0.0f;

    //begin the program
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (!hasBooted)
        {
            // boot sequence
            if (currentBootTime > bootNextUpdate)
            {
                //print next boot sequence line
                bootNextUpdate = MethodLibrary::getRandomNumber(100, 300) / 1000.0f;
                currentBootTime = 0.0f;
                hasBooted = em->bootSequence();
                em->printCommandHistory();
            }
            else
            {
                // wait for next boot sequence line
                currentBootTime += GetFrameTime();
                em->printCommandHistory();
            }
        }
        else
        {
            // main program functionality
            em->detectKeyPress();
            em->detectReturnPress();
            em->printEverythingToScreen();
        }
        DrawTextureEx(texture, { 0,0 }, 0, 1.5f, BLACK);
        DrawTextureEx(texture, { 0,5 }, 0, 1.5f, BLACK);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}