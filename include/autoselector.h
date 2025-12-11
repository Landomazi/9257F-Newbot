enum Side { left_SIDE, right_SIDE };
enum AutonMode { NORMAL, SKILLS };
enum WinPoint { NOWINPOINT, WINPOINT };

extern Side selectedSide;
extern AutonMode selectedAutonMode;
extern WinPoint selectedWinPoint;
void waitForSelection(int xMin, int xMax, int yMin, int yMax, void (*onSelect)());
void displaySkillsMenu();
void displaySideMenu();
void displayWinPointMenu();
void displayFinalSelection();
void autonSelectionFlow();