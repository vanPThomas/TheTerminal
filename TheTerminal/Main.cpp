#include "raylib.h"
#include <iostream>
#include <vector>
#include <string>
#include "EnvironmentManager.h"
#include "Root.h"
#include "HardDrive.h"
#include "MethodLibrary.h"
#include "File.h"
#include "TextFile.h"
#include "EncyclopediaManager.h"

EnvironmentManager* createEnvironmentManager();

int main()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    const int fontSize = 20;
    const int codeSpeed = 5;
    const std::string exePath = MethodLibrary::getExecutablePath();

    InitWindow(screenWidth, screenHeight, "OS Simulator");
    SetTargetFPS(60);

    ToggleFullscreen();
    Texture2D texture = LoadTexture("31589011-cdbc122c-b1bf-11e7-986f-2ebf6bcb8777.png");

    EnvironmentManager* em = createEnvironmentManager();
    EncyclopediaManager* encMan = new EncyclopediaManager();


    //boot sequence variables
    bool hasBooted = false;
    bool hasBootedKa = false;
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
            //TextFile *tf  = (TextFile*)fileList[0];
            //std::cout << tf->content << "\n";
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
            std::string activeProgram = em->getActiveProgram();
            // main program functionality
            if (em->getActiveProgram() == "TERMINAL")
            {
                em->detectKeyPress();
                em->detectReturnPress();
                em->printEverythingToScreen();
            }
            else if (activeProgram == "ENCYCLOPEDIA")
            {
                encMan->runEcyclopedia();
            }

        }
        DrawTextureEx(texture, { 0,0 }, 0, 1.5f, BLACK);
        DrawTextureEx(texture, { 0,5 }, 0, 1.5f, BLACK);
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}

EnvironmentManager* createEnvironmentManager()
{
    std::vector<File*>fileList{};
    File* file1 = new TextFile(130, "KEYS", "TEXT");
    File* file2 = new TextFile(270, "KERNEL SETTINGS", "TEXT");

    fileList.push_back(file1);
    fileList.push_back(file2);
    HardDrive* hardDrive = new HardDrive("A", 32768);
    HardDrive* hardDrive2 = new HardDrive("B", 16384);
    Root* root = new Root();
    root->addHardDrive(hardDrive);
    root->addHardDrive(hardDrive2);
    Folder* folder = new Folder("SYSTEM", NULL);
    Folder* folder2 = new Folder("DRIVERS", folder);
    folder->addFolderToFolders(folder2);
    hardDrive2->addFolder(folder);
    folder->addFileToFiles(file1);
    folder2->addFileToFiles(file2);
    EnvironmentManager* em = new EnvironmentManager(root->getRootPrompt(), root);
    return em;
}