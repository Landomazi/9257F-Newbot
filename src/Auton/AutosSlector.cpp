/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       AutonSelector.cpp                                         */
/*    Author:       Landon Kiely                                              */
/*    Created:      01/19/2026                                                */
/*    Description:  VEX V5 Autonomous Selector                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Configure.h"

using namespace vex;

enum AutonMode { Skills, NoSkills };
enum MatchType { Match, Elims };
enum Side { LeftSide, RightSide, AWPoint };
enum ElimsSide { ELeft, ERight };

AutonMode selectedAutonMode;
MatchType selectedMatchType;
Side selectedSide;
ElimsSide selectedElimsSide;

// Wait for screen press and return encoded x and y
int WaitForPress() {
    while (!BigBrain.Screen.pressing()) {
        task::sleep(20);
    }
    int x = BigBrain.Screen.xPosition();
    int y = BigBrain.Screen.yPosition();
    while (BigBrain.Screen.pressing()) {
        task::sleep(20);
    }
    return (x << 16) | y;
}

// Generic menu display function compatible with VEX V5
int DisplayMenu(const char* options[], color colors[], int numOptions) {
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(fontType::mono30);
    BigBrain.Screen.setPenColor(white);

    int startX[numOptions];
    int width = 150;
    int x = 40;
    int y = 80;

    for (int i = 0; i < numOptions; i++) {
        BigBrain.Screen.setFillColor(colors[i]);
        BigBrain.Screen.drawRectangle(x, y, width, 150);
        BigBrain.Screen.printAt(x + 15, y + 80, options[i]);
        startX[i] = x;
        x += 190; // spacing between buttons
    }

    while (true) {
        int xy = WaitForPress();
        int px = xy >> 16;
        int py = xy & 0xFFFF;

        for (int i = 0; i < numOptions; i++) {
            if (px >= startX[i] && px <= startX[i] + width &&
                py >= y && py <= y + 150) {
                return i;
            }
        }
    }
}

void AutonSelector() {
    // Step 1: Skills or No Skills
    const char* firstMenu[] = { "Skills", "No Skills" };
    color firstColors[] = { yellow, green };
    int choice = DisplayMenu(firstMenu, firstColors, 2);
    selectedAutonMode = (choice == 0) ? Skills : NoSkills;

    if (selectedAutonMode == NoSkills) {
        // Step 2: Match or Elims
        const char* secondMenu[] = { "Match", "Elims" };
        color secondColors[] = { orange, red };
        choice = DisplayMenu(secondMenu, secondColors, 2);
        selectedMatchType = (choice == 0) ? Match : Elims;

        if (selectedMatchType == Match) {
            // Step 3a: Left / Right / AWP
            const char* matchMenu[] = { "Left", "Right", "AWP" };
            color matchColors[] = { green, orange, blue };
            choice = DisplayMenu(matchMenu, matchColors, 3);
            if (choice == 0) selectedSide = LeftSide;
            else if (choice == 1) selectedSide = RightSide;
            else selectedSide = AWPoint;
        } else {
            // Step 3b: Elims Left / Right
            const char* elimsMenu[] = { "Left", "Right" };
            color elimsColors[] = { green, orange };
            choice = DisplayMenu(elimsMenu, elimsColors, 2);
            selectedElimsSide = (choice == 0) ? ELeft : ERight;
        }
    }

    // Display final selection
    BigBrain.Screen.clearScreen();
    BigBrain.Screen.setFont(fontType::mono30);
    BigBrain.Screen.setPenColor(white);

    if (selectedAutonMode == Skills) {
        BigBrain.Screen.printAt(40, 100, "Running Skills Autonomous");
    } else if (selectedMatchType == Match) {
        BigBrain.Screen.printAt(40, 100, "Running Match: ");
        if (selectedSide == LeftSide) BigBrain.Screen.printAt(220, 100, "Left");
        else if (selectedSide == RightSide) BigBrain.Screen.printAt(220, 100, "Right");
        else BigBrain.Screen.printAt(220, 100, "AWP");
    } else { // Elims
        BigBrain.Screen.printAt(40, 100, "Running Elims: ");
        if (selectedElimsSide == ELeft) BigBrain.Screen.printAt(220, 100, "Left");
        else BigBrain.Screen.printAt(220, 100, "Right");
    }
}