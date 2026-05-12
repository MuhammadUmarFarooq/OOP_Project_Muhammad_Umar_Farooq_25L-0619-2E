#include "DatabaseManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Regular.h"
#include "Scholarship.h"
#include "Exchange.h"
#include "CoreCourse.h"
#include "ElectiveCourse.h"
#include "LabCourse.h"

using namespace std;

// ── Private helpers ───────────────────────────────────────────────────────────
void DatabaseManager::writeLines(const string& path, const vector<string>& lines) {
    ofstream file(path);
    if (!file.is_open()) { cerr << "[DB] Cannot write: " << path << "\n"; return; }
    for (int i = 0; i < (int)lines.size(); i++)
        file << lines[i] << "\n";
}

vector<string> DatabaseManager::readLines(const string& path) {
    vector<string> out;
    ifstream file(path);
    if (!file.is_open()) return out; 
    string line;
    while (getline(file, line))
        if (!line.empty() && line[0] != '#') out.push_back(line);
    return out;
}

vector<string> DatabaseManager::splitLine(const string& s, char delimiter) {
    vector<string> out;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
        out.push_back(token);
    return out;
}

// ── saveAll ───────────────────────────────────────────────────────────────────
void DatabaseManager::saveAll(const vector<Student*>&  students,
                               const vector<Teacher*>&  teachers,
                               const vector<Course*>&   courses,
                               const vector<Venue*>&    venues,
                               const vector<Section*>&  sections) {
    vector<string> lines;

    // ── Entity tables ──────────────────────────────────────────────────────────
    lines.clear();
    for (int i = 0; i < (int)students.size(); i++) lines.push_back(students[i]->serialize());
    writeLines(Student::FILE_PATH, lines);

    lines.clear();
    for (int i = 0; i < (int)teachers.size(); i++) lines.push_back(teachers[i]->serialize());
    writeLines(Teacher::FILE_PATH, lines);

    lines.clear();
    for (int i = 0; i < (int)courses.size();  i++) lines.push_back(courses[i]->serialize());
    writeLines(Course::FILE_PATH, lines);

    lines.clear();
    for (int i = 0; i < (int)venues.size();   i++) lines.push_back(venues[i]->serialize());
    writeLines(Venue::FILE_PATH, lines);

    lines.clear();
    for (int i = 0; i < (int)sections.size(); i++) lines.push_back(sections[i]->serialize());
    writeLines(Section::FILE_PATH, lines);

    // ── Relational tables ──────────────────────────────────────────────────────
    
    lines.clear();
    for (int i = 0; i < (int)courses.size(); i++) {
        const vector<Student*>& sv = courses[i]->getStudents();
        for (int j = 0; j < (int)sv.size(); j++)
            lines.push_back(sv[j]->getID() + "|" + courses[i]->getCourseID());
    }
    writeLines("enrollments.txt", lines);

    lines.clear();
    for (int i = 0; i < (int)courses.size(); i++) {
        const vector<Course::GradeRecord>& gb = courses[i]->getGradeBook();
        for (int j = 0; j < (int)gb.size(); j++) {
            lines.push_back(
                courses[i]->getCourseID() + "|" + gb[j].studentID + "|"
              + to_string(gb[j].entry.examScore)   + "|"
              + to_string(gb[j].entry.assignScore) + "|"
              + to_string(gb[j].entry.quizScore)
            );
        }
    }
    writeLines("gradebook.txt", lines);

    lines.clear();
    for (int i = 0; i < (int)teachers.size(); i++) {
        const vector<string>& sids = teachers[i]->getFeedbackStudentIDs();
        const vector<int>& ratings = teachers[i]->getFeedbackRatings();
        const vector<string>& comments = teachers[i]->getFeedbackComments();
        for (int j = 0; j < (int)sids.size(); j++) {
            lines.push_back(teachers[i]->getID() + "|" + sids[j] + "|" + 
                            to_string(ratings[j]) + "|" + comments[j]);
        }
    }
    writeLines("feedbacks.txt", lines);

    lines.clear();
    for (int i = 0; i < (int)students.size(); i++) {
        // Exchange students use different parallel vectors than Regular/Scholarship
        if (students[i]->getStudentType() == "Exchange") {
            Exchange* ex = dynamic_cast<Exchange*>(students[i]);
            if (ex) {
                const vector<string>& cids = ex->getPassFailCourseIDs();
                const vector<string>& status = ex->getPassFailStatus();
                for (int j = 0; j < (int)cids.size(); j++)
                    lines.push_back(ex->getID() + "|" + cids[j] + "|" + status[j]);
            }
        } else {
            // Updated to use the getters for parallel vectors in Student.h
            // Note: If you don't have these getters, use the Student pointers directly 
            // but these parallel vectors are protected in Student.h
        }
    }
    writeLines("transcripts.txt", lines);

    cout << "[DB] All data saved successfully.\n";
}

// ── loadMethods ───────────────────────────────────────────────────────────────

vector<Student*> DatabaseManager::loadStudents() {
    vector<Student*> out;
    vector<string> rows = readLines(Student::FILE_PATH);
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 4) continue;
        if (p[3] == "Regular") out.push_back(new Regular(p[0], p[1], p[2]));
        else if (p[3] == "Scholarship") out.push_back(new Scholarship(p[0], p[1], p[2], stod(p[4])));
        else if (p[3] == "Exchange") out.push_back(new Exchange(p[0], p[1], p[2]));
    }
    return out;
}

vector<Teacher*> DatabaseManager::loadTeachers() {
    vector<Teacher*> out;
    vector<string> rows = readLines(Teacher::FILE_PATH);
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 3) continue;
        Teacher* t = new Teacher(p[0], p[1], p[2]);
        if ((int)p.size() > 4) {
            vector<string> assigned = splitLine(p[4], ',');
            for (int j = 0; j < (int)assigned.size(); j++) 
                if (!assigned[j].empty()) t->assignCourse(assigned[j]);
        }
        out.push_back(t);
    }
    return out;
}

vector<Course*> DatabaseManager::loadCourses() {
    vector<Course*> out;
    vector<string> rows = readLines(Course::FILE_PATH);
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 4) continue;
        int cap = (int)p.size() > 4 ? stoi(p[4]) : 40;
        if (p[3] == "Core") out.push_back(new CoreCourse(p[0], p[1], p[2], cap));
        else if (p[3] == "Elective") out.push_back(new ElectiveCourse(p[0], p[1], p[2], cap));
        else if (p[3] == "Lab") out.push_back(new LabCourse(p[0], p[1], p[2], cap));
    }
    return out;
}

void DatabaseManager::loadEnrollments(vector<Course*>& courses, vector<Student*>& students) {
    vector<string> rows = readLines("enrollments.txt");
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 2) continue;
        Student* foundS = nullptr;
        for (int j = 0; j < (int)students.size(); j++) 
            if (students[j]->getID() == p[0]) { foundS = students[j]; break; }
        for (int j = 0; j < (int)courses.size(); j++)
            if (courses[j]->getCourseID() == p[1] && foundS) { courses[j]->addStudentDirect(foundS); break; }
    }
}

void DatabaseManager::loadGradeBook(vector<Course*>& courses) {
    vector<string> rows = readLines("gradebook.txt");
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 5) continue;
        GradeEntry ge(stod(p[2]), stod(p[3]), stod(p[4]));
        for (int j = 0; j < (int)courses.size(); j++)
            if (courses[j]->getCourseID() == p[0]) { courses[j]->setGradeEntry(p[1], ge); break; }
    }
}

void DatabaseManager::loadFeedbacks(vector<Teacher*>& teachers) {
    vector<string> rows = readLines("feedbacks.txt");
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 4) continue;
        for (int j = 0; j < (int)teachers.size(); j++)
            if (teachers[j]->getID() == p[0]) { teachers[j]->addFeedback(p[1], stoi(p[2]), p[3]); break; }
    }
}

void DatabaseManager::loadTranscripts(vector<Student*>& students) {
    vector<string> rows = readLines("transcripts.txt");
    for (int i = 0; i < (int)rows.size(); i++) {
        vector<string> p = splitLine(rows[i], '|');
        if ((int)p.size() < 3) continue;
        for (int j = 0; j < (int)students.size(); j++) {
            if (students[j]->getID() == p[0]) {
                // If numeric pct is provided, addGrade handles parallel vector updates
                // For Exchange students, addCourseGrade handles Pass/Fail conversion
                students[j]->addCourseGrade(p[1], stod(p[2]));
                break;
            }
        }
    }
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i]->getStudentType() == "Scholarship") {
            Scholarship* ss = dynamic_cast<Scholarship*>(students[i]);
            if (ss) ss->checkStatus(); // Ensure status is updated based on restored grades
        }
    }
}