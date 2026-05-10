#include "Student.h"
#include <iostream>
#include <iomanip>    // for setw, setprecision, fixed

using namespace std;

// Static member definition — gives the string actual storage in memory 
const string Student::FILE_PATH = "students.txt";

//Enrolment
void Student::enrollCourse(const string& cid) {
    // Only add if not already enrolled — prevents duplicates 
    if (!isEnrolledIn(cid))
        enrolledCourseIDs.push_back(cid);
}

void Student::dropCourse(const string& cid) {
    // Manual search and shift to replace erase-remove idiom 
    int index = -1;
    for (int i = 0; i < (int)enrolledCourseIDs.size(); i++) {
        if (enrolledCourseIDs[i] == cid) {
            index = i;
            break;
        }
    }

    // If found, shift all subsequent elements forward one position
    if (index != -1) {
        for (int i = index; i < (int)enrolledCourseIDs.size() - 1; i++) {
            enrolledCourseIDs[i] = enrolledCourseIDs[i + 1];
        }
        enrolledCourseIDs.pop_back(); // Remove the now-duplicate last element
    }
}

bool Student::isEnrolledIn(const string& cid) const {
    // Manual linear search through enrolledCourseIDs
    for (int i = 0; i < (int)enrolledCourseIDs.size(); i++) {
        if (enrolledCourseIDs[i] == cid) {
            return true;
        }
    }
    return false;
}

//Grade Recording
void Student::addGrade(const string& cid, double pct) {
    // Manual parallel vector management
    transcriptCourseIDs.push_back(cid);
    transcriptPercentages.push_back(pct);
    transcriptLetterGrades.push_back(letterFromPct(pct));
}

string Student::getLetterGrade(const string& cid) const {
    //Linear Search to find the course ID and return corresponding letter grade
    for (int i = 0; i < (int)transcriptCourseIDs.size(); i++) {
        if (transcriptCourseIDs[i] == cid) {
            return transcriptLetterGrades[i];
        }
    }
    return "N/A";
}

void Student::displayProfile() {
    cout << "\n--- Student Profile ---\n"
         << "ID    : " << getID()    << "\n"
         << "Name  : " << getName()  << "\n"
         << "Email : " << getEmail() << "\n"
         << "Type  : " << studentType << "\n";

    if (studentType != "Exchange")
        cout << "GPA   : " << fixed << setprecision(2) << calculateGPA() << "\n";
    else
        cout << "GPA   : N/A (Exchange student uses Pass/Fail)\n";

    // Print enrolled courses using standard int 
    cout << "Enrolled in: ";
    for (int i = 0; i < (int)enrolledCourseIDs.size(); i++) {
        cout << enrolledCourseIDs[i] << " ";
    }
    cout << "\n";
}

// ── Static Helpers ────────────────────────────────────────────────────────────
string Student::letterFromPct(double p) {
    if (p >= 90) return "A+"; 
    if (p >= 85) return "A";
    if (p >= 80) return "A-";
    if (p >= 75) return "B+";
    if (p >= 70) return "B";
    if (p >= 65) return "B-";
    if (p >= 60) return "C+";
    if (p >= 55) return "C";
    if (p >= 50) return "C-";
    if (p >= 45) return "D";
    return "F";
}

double Student::gpaPointFromPct(double p) {
    if (p >= 90) return 4.0; 
    if (p >= 85) return 4.0;
    if (p >= 80) return 3.7;
    if (p >= 75) return 3.3;
    if (p >= 70) return 3.0;
    if (p >= 65) return 2.7;
    if (p >= 60) return 2.3;
    if (p >= 55) return 2.0;
    if (p >= 50) return 1.7;
    if (p >= 45) return 1.0;
    return 0.0;
}
