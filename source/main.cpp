#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
// <limits>, <algorithm>, and <map> have been removed
#include "DatabaseManager.h"
#include "Schedular.h"
#include "WeightageConfig.h"
#include "Regular.h"
#include "Scholarship.h"
#include "Exchange.h"

using namespace std;

// ── Global Application State ──────────────────────────────────────────────────
vector<Student*>  students;
vector<Teacher*>  teachers;
vector<Course*>   courses;
vector<Venue*>    venues;
vector<Section*>  sections;

// ── Input Utilities ───────────────────────────────────────────────────────────
void clearInput() {
    cin.clear();
    // Replaced numeric_limits with a large constant to clear the buffer
    cin.ignore(10000, '\n'); 
}

int getInt(const string& prompt) {
    int v;
    cout << prompt;
    while (!(cin >> v)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Enter a number: "; 
    }
    clearInput();
    return v;
}

double getDbl(const string& prompt) {
    double v;
    cout << prompt;
    while (!(cin >> v)) { 
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        cout << "Enter a number: "; 
    }
    clearInput();
    return v;
}

string getStr(const string& prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

// ── Lookup Functions ──────────────────────────────────────────────────────────
Student* findStudent(const string& id) {
    for (int i = 0; i < (int)students.size(); i++)
        if (students[i]->getID() == id) return students[i];
    return nullptr;
}

Teacher* findTeacher(const string& id) {
    for (int i = 0; i < (int)teachers.size(); i++)
        if (teachers[i]->getID() == id) return teachers[i];
    return nullptr;
}

Course* findCourse(const string& id) {
    for (int i = 0; i < (int)courses.size(); i++)
        if (courses[i]->getCourseID() == id) return courses[i];
    return nullptr;
}

Venue* findVenue(const string& id) {
    for (int i = 0; i < (int)venues.size(); i++)
        if (venues[i]->getRoomID() == id) return venues[i];
    return nullptr;
}

// ── Manual Sort Helper (Replacing <algorithm> sort) ───────────────────────────
void rankTeachers(vector<Teacher*>& ranked) {
    int n = (int)ranked.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ranked[j]->getAverageScore() < ranked[j + 1]->getAverageScore()) {
                Teacher* temp = ranked[j];
                ranked[j] = ranked[j + 1];
                ranked[j + 1] = temp;
            }
        }
    }
}

// ── Display Helpers ───────────────────────────────────────────────────────────
void separator(char c = '-', int w = 50) { cout << string(w, c) << "\n"; }
void header(const string& t) {
    separator('=');
    int pad = (48 - (int)t.size()) / 2;
    cout << string(pad > 0 ? pad : 0, ' ') << t << "\n";
    separator('=');
}

// ══════════════════════════════════════════════════════════════════════════════
// MENU LOGIC
// ══════════════════════════════════════════════════════════════════════════════

void menuStudents() {
    int ch;
    do {
        header("Student Management");
        cout << "  1. Add Student\n  2. List All Students\n  3. View Profile\n  0. Back\n";
        ch = getInt("> ");

        if (ch == 1) {
            string id = getStr("ID: ");
            if (findStudent(id)) { cout << "Exists.\n"; continue; }
            string nm = getStr("Name: ");
            string em = getStr("Email: ");
            cout << "1. Regular, 2. Scholarship, 3. Exchange\n";
            int t = getInt("Choice: ");

            if (t == 1) students.push_back(new Regular(id, nm, em));
            else if (t == 2) students.push_back(new Scholarship(id, nm, em, getDbl("Min GPA: ")));
            else if (t == 3) students.push_back(new Exchange(id, nm, em));
        }
        else if (ch == 2) {
            for (int i = 0; i < (int)students.size(); i++) students[i]->displayProfile();
        }
    } while (ch != 0);
}

void menuCourses() {
    int ch;
    do {
        header("Course Management");
        cout << "  1. Add Course\n  2. Enter Marks\n  0. Back\n";
        ch = getInt("> ");

        if (ch == 2) {
            string cid = getStr("Course ID: ");
            Course* c = findCourse(cid);
            if (!c) continue;

            string sid = getStr("Student ID: ");
            Student* s = findStudent(sid);
            if (!s || !c->hasStudent(sid)) continue;

            int at = getInt("1. Exam, 2. Assign, 3. Quiz: ");
            string type = (at == 1) ? "Exam" : (at == 2) ? "Assignment" : "Quiz";
            double score = getDbl("Score: ");

            c->setScore(sid, type, score);
            s->addCourseGrade(cid, c->getFinalGrade(sid));
            
            if (s->getStudentType() == "Scholarship") {
                Scholarship* ss = dynamic_cast<Scholarship*>(s);
                if (ss) ss->checkStatus();
            }
        }
    } while (ch != 0);
}

// ══════════════════════════════════════════════════════════════════════════════
// MAIN
// ══════════════════════════════════════════════════════════════════════════════

int main() {
    students = DatabaseManager::loadStudents();
    teachers = DatabaseManager::loadTeachers();
    courses  = DatabaseManager::loadCourses(); 
    venues   = DatabaseManager::loadVenues();  
    sections = DatabaseManager::loadSections();

    DatabaseManager::loadEnrollments(courses, students);
    DatabaseManager::loadGradeBook(courses);  
    DatabaseManager::loadFeedbacks(teachers); 
    DatabaseManager::loadTranscripts(students);

    int ch;
    do {
        header("FAST NUCES Portal");
        cout << "1. Students\n2. Teachers\n3. Courses\n4. Scheduler\n0. Save & Exit\n";
        ch = getInt("> ");

        if (ch == 1) menuStudents();
        else if (ch == 3) menuCourses();
        else if (ch == 4) {
            Scheduler sched(sections, venues, courses);
            sched.assignVenues();
        }
    } while (ch != 0);

    DatabaseManager::saveAll(students, teachers, courses, venues, sections);

    // Final Memory Cleanup
    for (int i = 0; i < (int)students.size(); i++) delete students[i];
    for (int i = 0; i < (int)teachers.size(); i++) delete teachers[i];
    for (int i = 0; i < (int)courses.size();  i++) delete courses[i];
    for (int i = 0; i < (int)venues.size();   i++) delete venues[i];
    for (int i = 0; i < (int)sections.size(); i++) delete sections[i];

    return 0;
}