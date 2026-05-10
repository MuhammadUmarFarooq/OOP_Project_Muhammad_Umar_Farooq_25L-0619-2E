#include "Exchange.h"
#include <iomanip>
#include <iostream>
using namespace std;


void Exchange::addCourseGrade(const string& cid, double pct) {
    // Manual search to see if the course already has a grade to prevent duplicates
    int index = -1;
    for (int i = 0; i < (int)passFailCourseIDs.size(); i++) {
        if (passFailCourseIDs[i] == cid) {
            index = i;
            break;
        }
    }

    // Convert numeric percentage to Pass/Fail; 50% is the passing threshold
    string result = (pct >= 50.0) ? "Pass" : "Fail";

    if (index != -1) {
        // Update existing record in parallel vectors
        passFailStatus[index] = result;
    } else {
        // Add new record to parallel vectors [cite: 457]
        passFailCourseIDs.push_back(cid);
        passFailStatus.push_back(result);
    }
    
    // Exchange students do NOT accumulate GPA points [cite: 431, 436]
}

void Exchange::viewTranscript()const {
    // Use getName() accessor to retrieve private base class member [cite: 494, 502]
    cout << "\n=== Transcript: " << getName() << " (Exchange — Pass/Fail) ===\n"
         << left << setw(15) << "CourseID" << "Result\n"
         << string(22, '-') << "\n";

    // Standard for loop using int to iterate through parallel vectors [cite: 459]
    for (int i = 0; i < (int)passFailCourseIDs.size(); i++) {
        cout << left << setw(15) << passFailCourseIDs[i] << passFailStatus[i] << "\n";
    }
}

void Exchange::displayProfile() {
    // Use accessors getID(), getName(), and getEmail() to avoid encapsulation errors [cite: 466, 488, 489]
    cout << "\n--- Student Profile ---\n"
         << "ID    : " << getID()    << "\n"
         << "Name  : " << getName()  << "\n"
         << "Email : " << getEmail() << "\n"
         << "Type  : Exchange\n"
         << "GPA   : N/A (Pass/Fail system)\n"
         << "Courses: ";
         
    // Use standard int for loop to print enrolled course IDs [cite: 358, 453]
    for (int i = 0; i < (int)enrolledCourseIDs.size(); i++) {
        cout << enrolledCourseIDs[i] << " ";
    }
    cout << "\n";
}

string Exchange::serialize() const {
    // Produces one pipe-delimited line for students.txt [cite: 374, 455]
    // Uses accessors for inherited private members [cite: 460, 466]
    return getID() + "|" + getName() + "|" + getEmail() + "|Exchange|N/A|N/A";
}