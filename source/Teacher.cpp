#include "Teacher.h"
#include <iostream>
#include "AcademicEntity.h"
#include <iomanip>

using namespace std;

const string Teacher::FILE_PATH = "teachers.txt";

void Teacher::recalcAvg() {
    // Recompute average from scratch using the ratings parallel vector
    if (feedbackRatings.empty()) { 
        avgScore = 0.0; 
        return; 
    }

    double sum = 0.0;
    // Iterate through parallel ratings vector using standard int
    for (int i = 0; i < (int)feedbackRatings.size(); i++) {
        sum += feedbackRatings[i];
    }
    avgScore = sum / (double)feedbackRatings.size();
}

void Teacher::addFeedback(const string& sid, int r, const string& c) {
    // Basic validation for 1-5 star scale
    if (r < 1 || r > 5) { 
        cout << "Rating must be between 1 and 5.\n"; 
        return; 
    }

    // Add entries to each parallel vector to keep data synchronized
    feedbackStudentIDs.push_back(sid);
    feedbackRatings.push_back(r);
    feedbackComments.push_back(c);
    
    recalcAvg();
}

void Teacher::assignCourse(const string& cid) {
    assignedCourseIDs.push_back(cid);
}

void Teacher::displayProfile() {
    // Use public accessors getID(), getName(), and getEmail() to retrieve base class data
    cout << "\n--- Teacher Profile ---\n"
         << "ID    : " << getID()    << "\n"
         << "Name  : " << getName()  << "\n"
         << "Email : " << getEmail() << "\n"
         << "Score : " << fixed << setprecision(2) << avgScore << "/5.0\n"
         << "Courses: ";

    for (int i = 0; i < (int)assignedCourseIDs.size(); i++) {
        cout << assignedCourseIDs[i] << " ";
    }
    cout << "\n";
}

void Teacher::displayFeedbacks() const {
    // Use getName() accessor for inherited private member
    cout << "\n=== Feedbacks for " << getName() << " ===\n";
    
    if (feedbackStudentIDs.empty()) { 
        cout << "No feedback yet.\n"; 
        return; 
    }

    // Use standard for loop to iterate across parallel feedback vectors
    for (int i = 0; i < (int)feedbackStudentIDs.size(); i++) {
        cout << "Student : " << feedbackStudentIDs[i]
             << "  |  Rating: " << feedbackRatings[i] << "/5\n"
             << "Comment : " << feedbackComments[i] << "\n\n";
    }
    cout << "Overall Average: " << fixed << setprecision(2) << avgScore << "/5\n";
}

string Teacher::serialize() const {
    // Format: ID|Name|Email|AvgScore|course1,course2,
    string courses;
    for (int i = 0; i < (int)assignedCourseIDs.size(); i++) {
        courses += assignedCourseIDs[i] + ",";
    }

    // Use accessors for inherited private members to satisfy encapsulation
    return getID() + "|" + getName() + "|" + getEmail() + "|"
         + to_string(avgScore) + "|" + courses;
}
    