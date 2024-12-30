#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

#define BTN_ADD_MEMBER 1
#define BTN_DISPLAY_MEMBERS 2
#define BTN_EXIT 3
#define LIST_MEMBERS 4
#define EDIT_NAME 5
#define EDIT_AGE 6
#define EDIT_CONTACT 7
#define CB_PLAN 8
#define CB_FEATURES 9
#define BTN_FITNESS_TRACKER 10
#define EDIT_MEMBER_INDEX 11
#define BTN_DISPLAY_MEMBER_DETAILS 102

// MembershipPlan structure to hold plan info
struct MembershipPlan
{
    string name;
    double baseCost;
};

vector<string> members;
vector<MembershipPlan> plans = {
    {"Basic", 2000},
    {"Standard", 4000},
    {"Premium", 6000}};

HWND hName, hAge, hContact, hPlan, hFeatures, hListBox, hMemberIndex;

// Fitness Tracker data
vector<string> fitnessTrackerData = {
    "Step Count: 5000 steps",
    "Calories Burned: 200 kcal",
    "Distance: 3.5 km"};
void checkBloodPressure(int age, ostringstream &output)
{
    if (age < 18)
    {
        output << "Blood Pressure: Low";
    }
    else if (age >= 18 && age < 28)
    {
        output << "Blood Pressure: Normal";
    }
    else if (age >= 28 && age < 36)
    {
        output << "Blood Pressure: High";
    }
    else if (age >= 36 && age < 45)
    {
        output << "Blood Pressure: High";
    }
    else
    {
        output << "Blood Pressure: High";
    }
}

void calculateCaloriesBurned(int age, string planName, ostringstream &output)
{
    int calories = 0;
    if (planName == "Basic")
    {
        calories = 500;
    }
    else if (planName == "Standard")
    {
        calories = 800;
    }
    else if (planName == "Premium")
    {
        calories = 1200;
    }
    output << "Calories Burned: " << calories << " calories";
}

void calculateStepsWalked(ostringstream &output)
{
    int steps = rand() % 10001;
    output << "Steps Walked: " << steps << " steps";
}

void checkBodyTemperature(ostringstream &output)
{
    double temperature = 98.6 + (rand() % 3) - 1;
    output << "Body Temperature: " << temperature << " °F";
}

// Calculate Total Cost
double calculateTotalCost(const MembershipPlan &plan, const string &feature)
{
    double totalCost = plan.baseCost;

    if (feature == "Personal Trainer (+Rs500)")
    {
        totalCost += 500; // Add Rs500 for personal trainer
    }
    else if (feature == "Locker (+Rs200)")
    {
        totalCost += 200; // Add Rs200 for locker
    }
    else if (feature == "Nutrition (+Rs300)")
    {
        totalCost += 300; // Add Rs300 for nutrition
    }

    return totalCost;
}

// Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
    {
        // Set background color
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(173, 216, 230)));

        // Add Member Form
        CreateWindow("STATIC", "Name:", WS_VISIBLE | WS_CHILD, 20, 20, 100, 20, hwnd, NULL, NULL, NULL);
        hName = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 20, 300, 30, hwnd, (HMENU)EDIT_NAME, NULL, NULL);

        CreateWindow("STATIC", "Age:", WS_VISIBLE | WS_CHILD, 20, 60, 100, 20, hwnd, NULL, NULL, NULL);
        hAge = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 60, 300, 30, hwnd, (HMENU)EDIT_AGE, NULL, NULL);

        CreateWindow("STATIC", "Contact:", WS_VISIBLE | WS_CHILD, 20, 100, 100, 20, hwnd, NULL, NULL, NULL);
        hContact = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 100, 300, 30, hwnd, (HMENU)EDIT_CONTACT, NULL, NULL);

        CreateWindow("STATIC", "Plan:", WS_VISIBLE | WS_CHILD, 20, 140, 100, 20, hwnd, NULL, NULL, NULL);
        hPlan = CreateWindow("COMBOBOX", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 120, 140, 300, 200, hwnd, (HMENU)CB_PLAN, NULL, NULL);
        for (const auto &plan : plans)
        {
            SendMessage(hPlan, CB_ADDSTRING, 0, (LPARAM)plan.name.c_str());
        }

        CreateWindow("STATIC", "Additional Features:", WS_VISIBLE | WS_CHILD, 20, 180, 200, 20, hwnd, NULL, NULL, NULL);

        // ComboBox for Features (Personal Trainer, Locker, Nutrition)
        hFeatures = CreateWindow("COMBOBOX", "", WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 120, 200, 300, 200, hwnd, (HMENU)CB_FEATURES, NULL, NULL);
        SendMessage(hFeatures, CB_ADDSTRING, 0, (LPARAM) "None");
        SendMessage(hFeatures, CB_ADDSTRING, 0, (LPARAM) "Personal Trainer (+Rs500)");
        SendMessage(hFeatures, CB_ADDSTRING, 0, (LPARAM) "Locker (+Rs200)");
        SendMessage(hFeatures, CB_ADDSTRING, 0, (LPARAM) "Nutrition (+Rs300)");

        // Buttons
        CreateWindow("BUTTON", "Add Member", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 20, 260, 150, 40, hwnd, (HMENU)BTN_ADD_MEMBER, NULL, NULL);
        CreateWindow("BUTTON", "Display Members", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 180, 260, 150, 40, hwnd, (HMENU)BTN_DISPLAY_MEMBERS, NULL, NULL);
        CreateWindow("BUTTON", "Display Fitness Tracker", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 340, 260, 200, 40, hwnd, (HMENU)BTN_FITNESS_TRACKER, NULL, NULL);
        CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 560, 260, 80, 40, hwnd, (HMENU)BTN_EXIT, NULL, NULL);
        CreateWindow("BUTTON", "Display Member Details",
                     WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     660, 260, 200, 40, hwnd, (HMENU)BTN_DISPLAY_MEMBER_DETAILS,
                     (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), NULL);

        // List Box
        hListBox = CreateWindow("LISTBOX", "", WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY, 20, 320, 500, 200, hwnd, (HMENU)LIST_MEMBERS, NULL, NULL);

        // Create Member Index Input Box
        CreateWindow("STATIC", "Enter Member Index:", WS_VISIBLE | WS_CHILD, 20, 530, 120, 20, hwnd, NULL, NULL, NULL);
        hMemberIndex = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 530, 100, 30, hwnd, (HMENU)EDIT_MEMBER_INDEX, NULL, NULL);

        // Change the color of the buttons
        HWND hwndAddMember = GetDlgItem(hwnd, BTN_ADD_MEMBER);
        HWND hwndDisplayMembers = GetDlgItem(hwnd, BTN_DISPLAY_MEMBERS);
        HWND hwndFitnessTracker = GetDlgItem(hwnd, BTN_FITNESS_TRACKER);
        HWND hwndExit = GetDlgItem(hwnd, BTN_EXIT);

        // Set the background color of the buttons to light green
        SetClassLongPtr(hwndAddMember, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(144, 238, 144)));
        SetClassLongPtr(hwndDisplayMembers, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(144, 238, 144)));
        SetClassLongPtr(hwndFitnessTracker, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(144, 238, 144)));
        SetClassLongPtr(hwndExit, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(RGB(255, 99, 71)));

        break;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == BTN_ADD_MEMBER)
        {
            char name[50], contact[50];
            int age;
            GetWindowText(hName, name, 50);
            GetWindowText(hContact, contact, 50);
            age = GetDlgItemInt(hwnd, EDIT_AGE, NULL, FALSE);

            if (strlen(name) > 0 && strlen(contact) > 0 && age > 0)
            {
                int selectedPlanIndex = SendMessage(hPlan, CB_GETCURSEL, 0, 0);
                if (selectedPlanIndex == CB_ERR)
                {
                    MessageBox(hwnd, "Please select a plan!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                MembershipPlan selectedPlan = plans[selectedPlanIndex];

                // Get the selected feature from the ComboBox
                int selectedFeatureIndex = SendMessage(hFeatures, CB_GETCURSEL, 0, 0);
                if (selectedFeatureIndex == CB_ERR)
                {
                    MessageBox(hwnd, "Please select a feature!", "Error", MB_OK | MB_ICONERROR);
                    break;
                }

                char selectedFeature[100];
                SendMessage(hFeatures, CB_GETLBTEXT, selectedFeatureIndex, (LPARAM)selectedFeature);
                double totalCost = calculateTotalCost(selectedPlan, selectedFeature);

                ostringstream memberInfo;
                memberInfo << name << " | " << age << " | " << contact << " | " << selectedPlan.name << " | " << selectedFeature << " | Rs" << totalCost;
                members.push_back(memberInfo.str());

                // Add member info to the ListBox
                SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)memberInfo.str().c_str());
            }
            else
            {
                MessageBox(hwnd, "Please fill all fields correctly!", "Error", MB_OK | MB_ICONERROR);
            }
        }
        else if (LOWORD(wParam) == BTN_DISPLAY_MEMBERS)
        {
            for (const auto &member : members)
            {
                SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)member.c_str());
            }
        }
        else if (LOWORD(wParam) == BTN_FITNESS_TRACKER)
        {
            // Get the index from the input box
            char indexText[10];
            GetWindowText(hMemberIndex, indexText, 10);
            int index = atoi(indexText);

            if (index >= 0 && index < members.size())
            {
                // Prepare the fitness tracker data as a string
                ostringstream fitnessData;
                fitnessData << "Fitness Tracker Data for Member " << index << ":\n";
                for (const auto &data : fitnessTrackerData)
                {
                    fitnessData << data << "\n";
                }

                // Call fitness functions and add them to the string
                int age = 30;                 // Replace with actual age from member
                string planName = "Standard"; // Replace with actual plan name from member

                // Add blood pressure info
                ostringstream bloodPressureStream;
                checkBloodPressure(age, bloodPressureStream);

                // Add calories burned info
                ostringstream caloriesBurnedStream;
                calculateCaloriesBurned(age, planName, caloriesBurnedStream);

                // Add steps walked info
                ostringstream stepsWalkedStream;
                calculateStepsWalked(stepsWalkedStream);

                // Add body temperature info
                ostringstream bodyTemperatureStream;
                checkBodyTemperature(bodyTemperatureStream);

                // Combine all the data into the message
                fitnessData << "\n"
                            << bloodPressureStream.str();
                fitnessData << "\n"
                            << caloriesBurnedStream.str();
                fitnessData << "\n"
                            << stepsWalkedStream.str();
                fitnessData << "\n"
                            << bodyTemperatureStream.str();

                // Display the fitness tracker data in a message box
                MessageBox(hwnd, fitnessData.str().c_str(), "Fitness Tracker Data", MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                MessageBox(hwnd, "Invalid member index!", "Error", MB_OK | MB_ICONERROR);
            }
        }
        else if (LOWORD(wParam) == BTN_DISPLAY_MEMBER_DETAILS)
{
    // Get the index from the input box
    char indexText[10];
    GetWindowText(hMemberIndex, indexText, 10);
    int index = atoi(indexText);  // Convert input to integer

    // Check if the index is valid
    if (index >= 0 && index < members.size())
    {
        // Fetch the member details
        string memberDetails = members[index];

        // Display member details in a message box
        MessageBox(hwnd, memberDetails.c_str(), "Member Details", MB_OK | MB_ICONINFORMATION);
    }
    else
    {
        MessageBox(hwnd, "Invalid member index!", "Error", MB_OK | MB_ICONERROR);
    }
}


        else if (LOWORD(wParam) == BTN_EXIT)
        {
            PostQuitMessage(0);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main()
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "FitnessCenterClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "Fitness Center Membership System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 900, 700,
        NULL, NULL, wc.hInstance, NULL);

    if (hwnd)
    {
        ShowWindow(hwnd, SW_SHOWNORMAL);
        UpdateWindow(hwnd);

        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}
