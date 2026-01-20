## Actionable Update List for Each Checklist Item

### File & Naming Consistency

- **All filenames use consistent spelling and casing**
	- Rename `autosSlector.cpp` to `autoselector.cpp` to match `autoselector.h`.
	- Rename `interialHeading.cpp` to `InertialHeading.cpp` or `inertialHeading.cpp` to match `InertialHeading.h`.
	- Ensure all `.cpp` and `.h` files use the same capitalization and spelling as their header/source pair.

- **All function names are consistently cased**
	- Choose a naming convention (e.g., camelCase or PascalCase) and update all function names to match.
	- Example: If using camelCase, change `BotFacing()` to `botFacing()` if needed.

- **Enum names and values use a consistent style**
	- In `autoselector.h` and `autoselector.cpp`, ensure enums like `Side`, `AutonMode`, and `AWP` use the same casing for values (e.g., `LeftSide`, `RightSide`, `Normal`, `Skills`).
	- Avoid mixing styles like `SKILLS` and `Skills`. 
    - I know this is already fixed, just noting here as a reminder 

- **Variable names are descriptive and follow a consistent convention**
	- Update variables like `kP`, `kI`, `kD` to match your chosen style.
	- Avoid abbreviations unless standard (e.g., use `currentAngle` instead of `currAng`).
    - This is a recommendation/preference, if you prefer `kP`, `kI`, `kD` keep them, just want to call this out to remind you that you can name variables anything you want and the more descriptive the easier it is to read and understand later. 

### Code & Comment Clarity

- **All comments are clear, concise, and free of typos**
	- Fix typos in comments (e.g., “whit” → “with”, “calcuclation” → “calculation”, “cuurent” → “current”, “equivent” → “equivalent”).
	- Remove or reword inappropriate comments (e.g., `//davin is stupid`).
        - I don't care as long as they don't get out of hand AND don't make it into your notebook or interview

- **Function headers include parameter and return value descriptions**
	- Add or update function header comments to describe what each parameter and return value means.

- **All code blocks are free of commented-out or unused code**
	- Remove any blocks of code that are commented out and not needed for reference.
    - I know a lot of students like to leave commented blocks of code so they can turn it on and off later, or use it as a reference. But I would suggest keeping this code base as clean as possible.
      - IF you don't use the code or need it later, remove it and move it to a seperate project/file. try to isolate the unused code.

- **All error messages and print statements use correct spelling and grammar**
	- Review all `printf`, `cout`, or Brain screen messages for typos and clarity.
	  - Not a huge deal as long as you understand what is being logged
- **All documentation uses consistent terminology**
	- Use the same terms for robot parts, sensors, and actions throughout comments and documentation.
      - Same thing here, comments are for you. The more complicated something is the more comments there should be. Comments are meant to give the ability to jump back into the code quicker.

### Header/Source Alignment

- **All function signatures match between headers and source files**
	- Check that every function declared in a header matches the implementation in the source file (parameters, return type, and name).
      - Example:
		- In autonRoutes.h:
		- void AutonomousSkills();
		- In autonRoutes.cpp:
		- void AutonomousSkills(void)
		- Note: The parameter list uses void in the source but is empty in the header. This is functionally 
		- equivalent in C++, but for strict consistency, match them exactly.
	
- **All declared functions are implemented, and all implemented functions are declared**
	- Remove any unused declarations or implementations.
	- Add missing declarations for implemented functions.
		- Example of a match:
			driveStraight.h:
			void DriveStraight(double distance, double speed);
			driveStraight.cpp:
			void DriveStraight(double TargetMovement, double maxSpeed) { ... }
			Note: The parameter names differ (distance vs. TargetMovement, speed vs. maxSpeed). The types match, but for clarity, use the same names in both places.

### General Cleanliness

- **Remove or archive old, unused files**
	- Delete or move aside any files not used in the build or referenced in the code.

- **Remove duplicate or redundant code**
	- Consolidate repeated code blocks into functions or remove them if unnecessary.
	- Example:
		If you have repeated PID control logic in both driveStraight.cpp and turnPid.cpp, consider consolidating it into a shared function.

- **Ensure all files start with a brief description of their purpose**
	- At the top of each `.cpp` and `.h` file, add a comment summarizing what the file is for.

---