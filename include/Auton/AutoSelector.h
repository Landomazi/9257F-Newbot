

// Enumerations for autonomous selection
enum AutonMode { Skills, NoSkills };
enum MatchType { Match, Elims };
enum Side { LeftSide, RightSide, AWPoint };
enum ElimsType { ELeft, ERight};

// Global variables to store selected autonomous options
extern AutonMode SelectedAutonMode;
extern MatchType SelectedMatchType;
extern Side SelectedSide;
extern ElimsType SelectedElimsType;

// Function declarations
int WaitForPress();
int DisplayMenu(const char* options[], vex::color colors[], int numOptions);
void AutonSelector();