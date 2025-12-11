/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       autoselector.cpp                                          */
/*    Author:       Landon.kiely                                              */
/*    Created:      11/19/2025, 7:35:43 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "configure.h"

enum Side { left_side, right_side };
enum AutonMode { NORMAL, SKILLS };
enum WinPoint { NOWINPOINT, WINPOINT };

Side selectedSide;
AutonMode selectedAutonMode;
WinPoint selectedWinPoint;

// Function to wait for user touch selection
int waitForPress() {
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

void displaySkillsMenu() {
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

void displayWinPointMenu() {
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

void displaySideMenu() {
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

void displaySelection() {
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(vex::fontType::mono30);
    BigBrain.Screen.setPenColor(vex::white);

    if (selectedAutonMode == SKILLS) {
        BigBrain.Screen.printAt(40, 100, "Running Skills Autonomous");
    } else {
        BigBrain.Screen.printAt(40, 100, "Running Normal Autonomous");

        if (selectedWinPoint == WINPOINT) {
            BigBrain.Screen.printAt(40, 140, "With Win Point");
        }

        if (selectedWinPoint != WINPOINT) {
            BigBrain.Screen.printAt(40, 180,
                (selectedSide == left_side) ? "Left Side" : "Right Side");
        }
    }
}

void autonSelectionFlow() {
    displaySkillsMenu();
    bool skillChosen = false;
    while (!skillChosen) {
        int xy = waitForPress();
        int x = xy >> 16;
        int y = xy & 0xFFFF;

        if (x >= 40 && x <= 190 && y >= 80 && y <= 230) { // Skills
            selectedAutonMode = SKILLS;
            skillChosen = true;
        } else if (x >= 230 && x <= 380 && y >= 80 && y <= 230) { // No Skills
            selectedAutonMode = NORMAL;
            skillChosen = true;
        }
    }

    if (selectedAutonMode == NORMAL) {
        displayWinPointMenu();
        bool winChosen = false;
        while (!winChosen) {
            int xy = waitForPress();
            int x = xy >> 16;
            int y = xy & 0xFFFF;

            if (x >= 40 && x <= 190 && y >= 80 && y <= 230) { // No Win Point
                selectedWinPoint = NOWINPOINT;
                winChosen = true;
            } else if (x >= 230 && x <= 380 && y >= 80 && y <= 230) { // Win Point
                selectedWinPoint = WINPOINT;
                winChosen = true;
            }
        }
    }

    if (selectedAutonMode == NORMAL && selectedWinPoint != WINPOINT) {
        displaySideMenu();
        bool sideChosen = false;
        while (!sideChosen) {
            int xy = waitForPress();
            int x = xy >> 16;
            int y = xy & 0xFFFF;

            if (x >= 40 && x <= 190 && y >= 80 && y <= 230) { // Left Side
                selectedSide = left_side;
                sideChosen = true;
            } else if (x >= 230 && x <= 380 && y >= 80 && y <= 230) { // Right Side
                selectedSide = right_side;
                sideChosen = true;
            }
        }
    }

    displaySelection();
}