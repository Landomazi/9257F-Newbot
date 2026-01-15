/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autoselector.cpp                                          */
/*    Author:       Landon.kiely                                              */
/*    Created:      11/19/2025, 7:35:43 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Configure.h"

enum Side { LeftSide, RightSide };
enum AutonMode { Normal, Skills };
enum AWP { NoWinPoint, WinPoint };

Side SelectedSide;
AutonMode SelectedAutonMode;
AWP SelectedWinPoint;

// Function to wait for user touch selection
int WaitForPress() {
    while (!BigBrain.Screen.pressing()) {
        vex::task::sleep(20);
    }
    int x = BigBrain.Screen.xPosition();
    int y = BigBrain.Screen.yPosition();
    while (BigBrain.Screen.pressing()) { // wait for release
        vex::task::sleep(20);
    }
    return x << 16 | y; // encode x and y into one int
}

void DisplaySkillsMenu() {
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(vex::fontType::mono30);
    BigBrain.Screen.setPenColor(vex::white);

    BigBrain.Screen.setFillColor(vex::yellow);
    BigBrain.Screen.drawRectangle(40, 80, 150, 150);
    BigBrain.Screen.printAt(80, 160, "Skills");

    BigBrain.Screen.setFillColor(vex::green);
    BigBrain.Screen.drawRectangle(230, 80, 150, 150);
    BigBrain.Screen.printAt(250, 160, "No Skills");
}

void DisplayWinPointMenu() {
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(vex::fontType::mono30);
    BigBrain.Screen.setPenColor(vex::white);

    BigBrain.Screen.setFillColor(vex::green);
    BigBrain.Screen.drawRectangle(40, 80, 150, 150);
    BigBrain.Screen.printAt(55, 160, "No Win Point");

    BigBrain.Screen.setFillColor(vex::orange);
    BigBrain.Screen.drawRectangle(230, 80, 150, 150);
    BigBrain.Screen.printAt(255, 160, "Win Point");
}

void DisplaySideMenu() {
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(vex::fontType::mono30);
    BigBrain.Screen.setPenColor(vex::white);

    BigBrain.Screen.setFillColor(vex::green);
    BigBrain.Screen.drawRectangle(40, 80, 150, 150);
    BigBrain.Screen.printAt(55, 160, "Left Side");

    BigBrain.Screen.setFillColor(vex::orange);
    BigBrain.Screen.drawRectangle(230, 80, 150, 150);
    BigBrain.Screen.printAt(255, 160, "Right Side");
}

void DisplaySelection() {
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(vex::fontType::mono30);
    BigBrain.Screen.setPenColor(vex::white);
    BigBrain.Screen.setFillColor(vex::black);

    if (SelectedAutonMode == Skills) {
        BigBrain.Screen.printAt(40, 100, "Running Skills Autonomous");
    } else {
        BigBrain.Screen.printAt(40, 100, "Running Normal Autonomous");

        if (SelectedWinPoint == WinPoint) {
            BigBrain.Screen.printAt(40, 140, "With Win Point");
        } else if (SelectedSide == LeftSide){
         BigBrain.Screen.printAt(40,140, " Left Side");
        } else BigBrain.Screen.printAt(40, 140, " Right Side");

    }
}

void AutonSelectionFlow() {
    
    DisplaySkillsMenu();
    bool skillChosen = false;
    while (!skillChosen) {
        int xy = WaitForPress();
        int x = xy >> 16;
        int y = xy & 0xFFFF;

        if (x >= 40 && x <= 190 && y >= 80 && y <= 230) { // Skills
            SelectedAutonMode = Skills;
            skillChosen = true;
        } else if (x >= 230 && x <= 380 && y >= 80 && y <= 230) { // No Skills
            SelectedAutonMode = Normal;
            skillChosen = true;
        }
    }

    if (SelectedAutonMode == Normal) {
        DisplayWinPointMenu();
        bool winChosen = false;
        while (!winChosen) {
            int xy = WaitForPress();
            int x = xy >> 16;
            int y = xy & 0xFFFF;

            if (x >= 40 && x <= 190 && y >= 80 && y <= 230) { // No Win Point
                SelectedWinPoint = NoWinPoint;
                winChosen = true;
            } else if (x >= 230 && x <= 380 && y >= 80 && y <= 230) { // Win Point
                SelectedWinPoint = WinPoint;
                winChosen = true;
            }
        }
    }

    if (SelectedWinPoint == NoWinPoint){
        DisplaySideMenu();
        bool sideChosen = false;
        while (!sideChosen){
            int xy = WaitForPress();
            int x = xy >> 16;
            int y = xy & 0xFFFF;

            if (x >= 40 && x <= 190 && y >= 80 && y <= 230) { // No Win Point
                SelectedSide = LeftSide;
                sideChosen = true;
            } else if (x >= 230 && x <= 380 && y >= 80 && y <= 230) { // Win Point
                SelectedSide = RightSide;
                sideChosen = true;
            }
        }
    }

    DisplaySelection();
}