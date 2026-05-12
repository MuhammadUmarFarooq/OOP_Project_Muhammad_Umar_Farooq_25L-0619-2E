#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

// Include necessary headers
#include <iostream>
#include <vector>
#include <string>
#include "AcademicEntity.h"
#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Assessment.h"
#include "venue.h"
#include "Section.h"
#include <fstream>
#include <sstream>

// Forward declarations
class Student;
class Course;
class Assessment;
class Regular;
class Scholarship;
class Exchange;
 
/*
 * CONCEPT: Persistence Layer (File-Based Database)
 * DatabaseManager is responsible for all file reading and writing.
 * It knows the format of every .txt file and creates/restores all objects.
 *
 * The system uses NORMALISED files — each concern is in its own file:
 *   students.txt       — who the students are
 *   enrollments.txt    — which student is in which course
 *   gradebook.txt      — what scores each student has per course
 *   transcripts.txt    — final computed percentage per course per student
 *   feedbacks.txt      — teacher feedback entries
 *
 * This mirrors the relational database concept of separate tables.
 *
 * All methods are static — DatabaseManager is a utility class, never
 * instantiated. You call DatabaseManager::saveAll(...) directly.
 */

class DatabaseManager {
public:
    // ── Save ──────────────────────────────────────────────────────────────────
    static void saveAll(const vector<Student*>&  students,
                        const vector<Teacher*>&  teachers,
                        const vector<Course*>&   courses,
                        const vector<Venue*>&    venues,
                        const vector<Section*>&  sections);

    // ── Load entity tables ─────────────────────────────────────────────────────
    static vector<Student*>  loadStudents();
    static vector<Teacher*>  loadTeachers();
    static vector<Course*>   loadCourses();
    static vector<Venue*>    loadVenues();
    static vector<Section*>  loadSections();

    // ── Load relational tables (call AFTER loading entities) ───────────────────
    // Links Student* pointers into Course::enrolled vectors
    static void loadEnrollments(vector<Course*>& courses,
                                vector<Student*>& students);
    // Restores each student's exam/assignment/quiz scores
    static void loadGradeBook  (vector<Course*>& courses);
    // Restores teacher feedback entries
    static void loadFeedbacks  (vector<Teacher*>& teachers);
    // Restores each student's transcript (final grades per course)
    static void loadTranscripts(vector<Student*>& students);

private:
    static void           writeLines(const string& path,
                                     const vector<string>& lines);
    static vector<string> readLines (const string& path);
    static vector<string> splitLine (const string& s, char delimiter);
};

#endif // DATABASEMANAGER_H
