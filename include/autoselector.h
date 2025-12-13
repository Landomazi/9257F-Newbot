enum Side { LeftSide, RightSide };
enum AutonMode { Normal, Skills };
enum AWP { NoWinPoint, WinPoint };

extern Side SelectedSide;
extern AutonMode SelectedAutonMode;
extern AWP SelectedWinPoint;
void WaitForSelection(int xMin, int xMax, int yMin, int yMax, void (*onSelect)());
void DisplaySkillsMenu();
void DisplaySideMenu();
void DisplayWinPointMenu();
void DisplayFinalSelection();
void AutonSelectionFlow();