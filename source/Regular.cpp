#include "Regular.h"
#include <iostream>
#include <string>   
#include "Student.h"

#include "Regular.h"
#include <iostream>
#include <iomanip>
using namespace std;

#include "Regular.h"
#include <iostream>
#include <iomanip>
using namespace std;

double Regular::calculateGPA() const {
    // GPA = average of all course GPA points
    
    if (transcriptCourseIDs.empty()) return 0.0;

    double sum = 0.0;
    // Iterate through parallel vectors using a standard int index
    
    for (int i = 0; i < (int)transcriptCourseIDs.size(); i++) {
        sum += gpaPointFromPct(transcriptPercentages[i]); 
    }

    return sum / (double)transcriptCourseIDs.size();
}

void Regular::viewTranscript() const {
    cout << "\n=== Transcript: " << getName() << " (Regular) ===\n"; 
    cout << left << setw(15) << "CourseID"
                 << setw(10) << "Grade%"
                 << setw(8)  << "Letter" << "\n"
         << string(33, '-') << "\n"; 

    // Loop through parallel vectors to print the table
    // [cite: 1699, 1700, 1758]
    for (int i = 0; i < (int)transcriptCourseIDs.size(); i++) {
        cout << left << setw(15) << transcriptCourseIDs[i]                 // Course ID
                     << setw(10) << fixed << setprecision(2) << transcriptPercentages[i] // Grade %
                     << setw(8)  << letterFromPct(transcriptPercentages[i]) << "\n";    // Letter
    }
    
    cout << "\nCumulative GPA: " << fixed << setprecision(2) << calculateGPA() << "\n"; // [cite: 317, 318]
}

void Regular::addCourseGrade(const string& cid, double pct) {
    // Regular students just store the grade; GPA updates automatically
    // Calls addGrade which appends to parallel vectors
   
    addGrade(cid, pct);
}

void Regular::displayProfile() {
    // Call the base Student::displayProfile() for common info
    Student::displayProfile();
}

string Regular::serialize() const {
    // Produces one pipe-delimited line for students.txt
    // Format: ID|Name|Email|Regular|GPA|N/A
    return getID() + "|" + getName() + "|" + getEmail() + "|Regular|"
         + to_string(calculateGPA()) + "|N/A";
}