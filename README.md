
Fitness Center Membership System - README
Overview
The Fitness Center Membership System is a Windows desktop application built using the Win32 API. The application allows the management of members at a fitness center by adding members, displaying member details, and tracking fitness data. The system supports membership plans with additional features, calculates costs based on selected plans and features, and provides a fitness tracker displaying health-related information like blood pressure, calories burned, steps walked, and body temperature.

Features:
Add Member: Allows the addition of a new member by filling in their name, age, contact, selected plan, and additional features.
Display Members: Displays a list of all the members in the system with their details.
Display Member Details: Displays the full details of a specific member based on the entered index.
Fitness Tracker: Displays fitness-related data like steps walked, calories burned, blood pressure, and body temperature for a specific member.
Exit: Exits the application.
Requirements
Operating System: Windows
Development Tools: Microsoft Visual Studio or any C++ IDE that supports Win32 API
Libraries: The application uses Windows API (Win32 API) to create the graphical user interface (GUI).
Getting Started
1. Clone the repository (or copy the source code to your local machine).
bash
Copy code
git clone https://github.com/your-username/fitness-center-membership-system.git
2. Open the project in your C++ IDE (e.g., Visual Studio).
If using Visual Studio, you can open the .cpp file directly or create a new Win32 project and replace the code with the contents of this file.
3. Compile and Run the application:
Ensure that your IDE is set up to compile and run Win32 applications.
Build the project and execute the program.
Application Overview
UI Components:
Text Fields:

Name: Input field for the member's name.
Age: Input field for the member's age.
Contact: Input field for the member's contact details.
ComboBoxes:

Plan: Dropdown to select the membership plan (Basic, Standard, or Premium).
Additional Features: Dropdown to select additional features (Personal Trainer, Locker, Nutrition, or None).
Buttons:

Add Member: Adds a member based on the information entered in the text fields and dropdowns.
Display Members: Displays a list of all members in the system.
Display Member Details: Displays details of a member based on the entered member index.
Fitness Tracker: Displays fitness tracker information for a specific member.
Exit: Closes the application.
Listbox:

Displays a list of all added members along with their basic details.
Member Index Input:

Allows users to enter a member index to view specific member details or fitness tracker data.
Calculations:
Total Membership Cost: The total cost for each member is calculated based on the selected plan and features:

Basic Plan: Rs. 2000
Standard Plan: Rs. 4000
Premium Plan: Rs. 6000
Additional features include Personal Trainer (+Rs500), Locker (+Rs200), and Nutrition (+Rs300).
Fitness Tracker Data:

Steps Walked: Random number between 0 and 10,000 steps.
Calories Burned: Calculated based on the selected plan (Basic: 500, Standard: 800, Premium: 1200).
Blood Pressure: Based on the member's age.
Body Temperature: Random value between 97.6°F and 99.6°F.
Fitness Tracker Functions:
checkBloodPressure: Provides blood pressure based on the member's age.
calculateCaloriesBurned: Computes calories burned based on the selected membership plan.
calculateStepsWalked: Generates a random number of steps walked.
checkBodyTemperature: Simulates a body temperature based on a random value.
Usage
Add a New Member:

Enter the member's details (name, age, contact, plan, and features).
Click the Add Member button to add the member to the system.
Display All Members:

Click the Display Members button to see the list of all added members in the ListBox.
Display Specific Member Details:

Enter the member index in the "Enter Member Index" field.
Click the Display Member Details button to view the details of the selected member.
Display Fitness Tracker Data:

Enter the member index in the "Enter Member Index" field.
Click the Display Fitness Tracker button to view fitness data for the member (steps walked, calories burned, blood pressure, and body temperature).
Exit the Application:

Click the Exit button to close the application.
Code Structure
Main Function:
The main function initializes the Windows application, creates a window, and runs the message loop to handle user input.
WindowProc Function:
The WindowProc function is responsible for handling the events and messages that occur in the window (such as button clicks, text field changes, etc.).
It handles actions like adding members, displaying members, and showing fitness tracker data.
Fitness Tracker Functions:
Functions like checkBloodPressure, calculateCaloriesBurned, calculateStepsWalked, and checkBodyTemperature simulate health-related data.
Troubleshooting
Error: "Invalid member index!"
Ensure that the index entered is within the valid range of the member list.

Error: "Please fill all fields correctly!"
Make sure all required fields are filled before adding a member.

Error: "Please select a plan!"
Select a valid membership plan before adding a member.

License
This project is licensed under the MIT License - see the LICENSE file for details.
