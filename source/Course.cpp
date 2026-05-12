/*
 * CONCEPT: Standard Iteration replacing <algorithm>
 * We use standard for-loops with explicit iterators (vector<Student*>::iterator)
 * instead of 'auto' or std::find_if.
 *
 * CONCEPT: Polymorphic dispatch via getFinalGrade()
 * getFinalGrade() calls calculateFinalGrade() which is virtual.
 * Calling through the base class pointer automatically runs the correct
 * overridden version (Core, Elective, or Lab).
 */
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <iomanip>
// <algorithm> and <map> have been removed
using namespace std;

const string Course::FILE_PATH = "courses.txt";

bool Course::enrollStudent(Student* s) {
    if (isFull()) {
        cout << "Error: Course \"" << title << "\" is at full capacity.\n";
        return false;
    }
    if (hasStudent(s->getID())) {
        cout << "Error: Student " << s->getID() << " is already enrolled.\n";
        return false;
    }
    enrolled.push_back(s);
    s->enrollCourse(courseID);  // also update the student's own list
    return true;
}

bool Course::dropStudent(const string& sid) {
    // Standard iterator loop — replaces 'find_if' and lambda
    for (vector<Student*>::iterator it = enrolled.begin(); it != enrolled.end(); ++it) {
        if ((*it)->getID() == sid) {
            (*it)->dropCourse(courseID);  // remove from student's own list
            enrolled.erase(it);
            
            // Also remove their grades from the gradeBook vector if they exist
            for (vector<GradeRecord>::iterator gradeIt = gradeBook.begin(); gradeIt != gradeBook.end(); ++gradeIt) {
                if (gradeIt->studentID == sid) {
                    gradeBook.erase(gradeIt);
                    break;
                }
            }
            return true;
        }
    }
    return false;  // student not found
}

void Course::addStudentDirect(Student* s) {
    // Used by DatabaseManager on startup — does NOT call s->enrollCourse()
    // because we are just restoring the pointer link, not performing a new enrolment
    if (!hasStudent(s->getID()))
        enrolled.push_back(s);
}

Student* Course::findStudent(const string& sid) const {
    for (int i = 0; i < (int)enrolled.size(); i++)
        if (enrolled[i]->getID() == sid) return enrolled[i];
    return nullptr; // Note: use NULL if your compiler doesn't support C++11 nullptr
}

bool Course::hasStudent(const string& sid) const {
    return (findStudent(sid) != nullptr);
}

void Course::setScore(const string& sid, const string& type, double score) {
    int idx = findGradeIndex(sid);
    
    // If the student doesn't have a record yet, create one (mimics map[] behavior)
    if (idx == -1) {
        gradeBook.push_back(GradeRecord(sid, GradeEntry()));
        idx = gradeBook.size() - 1; // It is now the last element
    }

    // Access the entry by reference to modify the actual data
    GradeEntry& g = gradeBook[idx].entry;
    
    if      (type == "Exam")       g.examScore   = score;
    else if (type == "Assignment") g.assignScore = score;
    else if (type == "Quiz")       g.quizScore   = score;
}

double Course::getFinalGrade(const string& sid) const {
    int idx = findGradeIndex(sid);
    if (idx == -1) return 0.0;  // no marks entered yet

    // Polymorphic dispatch — calls CoreCourse, ElectiveCourse, or LabCourse version
    return calculateFinalGrade(sid, gradeBook[idx].entry);
}

void Course::setGradeEntry(const string& sid, const GradeEntry& ge) {
    int idx = findGradeIndex(sid);
    if (idx != -1) {
        gradeBook[idx].entry = ge; // Update existing
    } else {
        gradeBook.push_back(GradeRecord(sid, ge)); // Add new, used by DatabaseManager
    }
}

void Course::displayInfo() const {
    cout << "\n--- Course: " << title << " (" << courseID << ") ---\n"
         << "Type     : " << courseType << "\n"
         << "Teacher  : " << teacherID  << "\n"
         << "Enrolled : " << getEnrolled() << "/" << maxCapacity << "\n"
         << "Exam dur : " << getExamDuration() << " min\n"
         << "Students : ";
    if (enrolled.empty()) cout << "None";
    else for (int i = 0; i < (int)enrolled.size(); i++)
        cout << enrolled[i]->getID() << " ";
    cout << "\n";
}

string Course::serialize() const {
    return courseID + "|" + title + "|" + teacherID + "|"
         + courseType + "|" + to_string(maxCapacity);
}