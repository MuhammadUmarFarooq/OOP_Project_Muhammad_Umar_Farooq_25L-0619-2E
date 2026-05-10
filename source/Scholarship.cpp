#include "Scholarship.h"
#include <iostream>
#include <string>
#include "Student.h"
#include "AcademicEntity.h"


#include "Scholarship.h"
#include <iostream>
#include <iomanip>
using namespace std;

double Scholarship::calculateGPA() const {
    // GPA = average of all course GPA points 
    if (transcriptCourseIDs.empty()) return 0.0; 

    double sum = 0.0;
    // Iterate through parallel vectors using a standard int index 
    for (int i = 0; i < (int)transcriptCourseIDs.size(); i++) {
        sum += gpaPointFromPct(transcriptPercentages[i]);
    }

    return sum / (double)transcriptCourseIDs.size(); 
}

void Scholarship::checkStatus() {
    // Update status based on scholarship-specific business rules 
    if (calculateGPA() < minGPA)
        status = "Probation"; 
    else
        status = "Good Standing"; 
}

void Scholarship::addCourseGrade(const string& cid, double pct) {
    // store grade in parallel vectors (inherited from Student) 
    addGrade(cid, pct); 
    // immediately re-evaluate scholarship status 
    checkStatus(); 
}

void Scholarship::viewTranscript() const {
    cout << "\n=== Transcript: " << getName() << " (Scholarship) ===\n" 
         << "Status : " << status
         << "  |  Min GPA Required: " << fixed << setprecision(2) << minGPA << "\n"
         << left << setw(15) << "CourseID"
                 << setw(10) << "Grade%"
                 << setw(8)  << "Letter" << "\n"
         << string(33, '-') << "\n";

    // Loop through parallel vectors to print the table 
    for (int i = 0; i < (int)transcriptCourseIDs.size(); i++) {
        cout << left << setw(15) << transcriptCourseIDs[i] 
                     << setw(10) << fixed << setprecision(2) << transcriptPercentages[i] 
                     << setw(8)  << letterFromPct(transcriptPercentages[i]) << "\n";
    }

    cout << "\nGPA: " << fixed << setprecision(2) << calculateGPA() << "\n"; 
}

void Scholarship::displayProfile() {
    Student::displayProfile();  // prints common fields 
    cout << "Min GPA Required : " << fixed << setprecision(2) << minGPA  << "\n";
    cout << "Scholarship Status: " << status << "\n";
}

string Scholarship::serialize() const {
    // Format: ID|Name|Email|Scholarship|minGPA|status 
    return getID() + "|" + getName() + "|" + getEmail() + "|Scholarship|" 
         + to_string(minGPA) + "|" + status; 
}

