#pragma once

enum AutonMode { Skills, NoSkills };
enum MatchType { Match, Elims };
enum Side { LeftSide, RightSide, AWPoint };
enum ElimsSide { ELeft, ERight };

// Global variables to store selected autonomous options
extern AutonMode SelectedAutonMode;
extern MatchType SelectedMatchType;
extern Side SelectedAutoSide;
extern ElimsSide SelectedElimsSide;

// Function declarations
int WaitForPress();
int DisplayMenu(const char* options[], vex::color colors[], int numOptions);
void AutonSelector();