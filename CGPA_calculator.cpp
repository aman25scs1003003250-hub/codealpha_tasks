#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

using namespace std;

double getGradePoint(string grade) {

    for (char &ch : grade)
    {
        ch = toupper(ch);
    }

    if (grade == "O")
        return 10.0;
    else if (grade == "A+")
        return 9.0;
    else if (grade == "A")
        return 8.0;
    else if (grade == "B+")
        return 7.0;
    else if (grade == "B")
        return 6.0;
    else if (grade == "C")
        return 5.0;
    else if (grade == "F")
        return 0.0;
    else
        return -1.0;
}

int main()
{
    int numberOfCourses;

    double totalCredits = 0.0;
    double totalGradePoints = 0.0;

    cout << "=============================================\n";
    cout << "          CGPA CALCULATOR\n";
    cout << "=============================================\n\n";

    do
    {
        cout << "Enter number of courses: ";
        cin >> numberOfCourses;

        if (numberOfCourses <= 0)
        {
            cout << "Invalid input! Number of courses must be greater than 0.\n";
        }

    } while (numberOfCourses <= 0);

    string courseName[100];
    string grade[100];
    double creditHours[100];
    double gradePoint[100];
    double weightedGradePoint[100];

    for (int i = 0; i < numberOfCourses; i++)
    {
        cout << "\n---------- Course " << i + 1 << " ----------\n";

        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, courseName[i]);

        do
        {
            cout << "Enter credit hours: ";
            cin >> creditHours[i];

            if (creditHours[i] <= 0)
            {
                cout << "Credit hours must be greater than 0.\n";
            }

        } while (creditHours[i] <= 0);

        do
        {
            cout << "Enter grade (O, A+, A, B+, B, C, F): ";
            cin >> grade[i];

            gradePoint[i] = getGradePoint(grade[i]);

            if (gradePoint[i] == -1.0)
            {
                cout << "Invalid grade! Please enter a valid grade.\n";
            }

        } while (gradePoint[i] == -1.0);

        weightedGradePoint[i] =
            gradePoint[i] * creditHours[i];

        totalCredits += creditHours[i];
        totalGradePoints += weightedGradePoint[i];
    }

    double semesterGPA = totalGradePoints / totalCredits;

    double previousCGPA;
    double previousCredits;

    cout << "\n=============================================\n";
    cout << "       PREVIOUS ACADEMIC RECORD\n";
    cout << "=============================================\n";

    do
    {
        cout << "Enter previous total credits (0 if first semester): ";
        cin >> previousCredits;

        if (previousCredits < 0)
        {
            cout << "Credits cannot be negative.\n";
        }

    } while (previousCredits < 0);

    if (previousCredits > 0)
    {
        do
        {
            cout << "Enter previous CGPA: ";
            cin >> previousCGPA;

            if (previousCGPA < 0 || previousCGPA > 10)
            {
                cout << "CGPA must be between 0 and 10.\n";
            }

        } while (previousCGPA < 0 || previousCGPA > 10);
    }
    else
    {
        previousCGPA = 0.0;
    }

    double overallCGPA;

    if (previousCredits == 0)
    {
        overallCGPA = semesterGPA;
    }
    else
    {
        double previousGradePoints =
            previousCGPA * previousCredits;

        overallCGPA =
            (previousGradePoints + totalGradePoints) /
            (previousCredits + totalCredits);
    }

    cout << "\n\n===============================================================\n";
    cout << "                    COURSE RESULT\n";
    cout << "===============================================================\n";

    cout << left
         << setw(25) << "Course"
         << setw(12) << "Credits"
         << setw(12) << "Grade"
         << setw(15) << "Grade Point"
         << setw(15) << "Weighted Points"
         << endl;

    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < numberOfCourses; i++)
    {
        cout << left
             << setw(25) << courseName[i]
             << setw(12) << creditHours[i]
             << setw(12) << grade[i]
             << setw(15) << gradePoint[i]
             << setw(15) << weightedGradePoint[i]
             << endl;
    }

    cout << "---------------------------------------------------------------\n";

    cout << fixed << setprecision(2);

    cout << "\nTotal Credits       : " << totalCredits;
    cout << "\nTotal Grade Points  : " << totalGradePoints;
    cout << "\nSemester GPA        : " << semesterGPA;
    cout << "\nOverall CGPA        : " << overallCGPA;

    cout << "\n\n=============================================\n";
    cout << "       CGPA CALCULATION COMPLETED\n";
    cout << "=============================================\n";

    return 0;
}