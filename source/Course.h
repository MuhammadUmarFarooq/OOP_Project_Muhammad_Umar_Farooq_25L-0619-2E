#ifndef COURSE_H
#define COURSE_H
#include "WeightageConfig.h"
#include <string>
#include <vector>

using namespace std;

class Student;  // forward declaration — full definition in Student.h

// ── GradeEntry ────────────────────────────────────────────────────────────────
// Replaces: struct GradeEntry { double examScore=0, assignScore=0, quizScore=0; };
class GradeEntry {
public:
    double examScore;    // 0-100 normalised percentage for exam
    double assignScore;  // 0-100 normalised percentage for assignments
    double quizScore;    // 0-100 normalised percentage for quizzes

    // Default constructor — zero initialise all scores
    GradeEntry() : examScore(0.0), assignScore(0.0), quizScore(0.0) {}

    GradeEntry(double e, double a, double q)
        : examScore(e), assignScore(a), quizScore(q) {}
};

// ── Course ────────────────────────────────────────────────────────────────────
class Course {
public:
    // Replaces the map's Key-Value pair using standard C++ features
    struct GradeRecord {
        string studentID;
        GradeEntry entry;
        
        GradeRecord(const string& id, const GradeEntry& e) 
            : studentID(id), entry(e) {}
    };

protected:
    string courseID, title, teacherID, courseType;
    int    maxCapacity;
    vector<Student*>    enrolled;    // pointers to enrolled student objects
    
    // Replaced map with a vector of the custom struct
    vector<GradeRecord> gradeBook;   

    // Helper method replacing std::find (from <algorithm>) and map::find()
    int findGradeIndex(const string& sid) const {
        for (int i = 0; i < (int)gradeBook.size(); ++i) {
            if (gradeBook[i].studentID == sid) {
                return i;
            }
        }
        return -1; // Not found
    }

public:
    static const string FILE_PATH;

    Course(const string& cid, const string& t, const string& tid,
           const string& type, int cap = 40)
        : courseID(cid), title(t), teacherID(tid),
          courseType(type), maxCapacity(cap) {}
    virtual ~Course() = default;

    // Basic getters
    string getCourseID()   const { return courseID;   }
    string getTitle()      const { return title;      }
    string getTeacherID()  const { return teacherID;  }
    string getCourseType() const { return courseType;  }
    int    getCapacity()   const { return maxCapacity; }
    int    getEnrolled()   const { return (int)enrolled.size(); }
    bool   isFull()        const { return getEnrolled() >= maxCapacity; }

    const vector<Student*>&    getStudents()  const { return enrolled;  }
    
    // Return type updated to match the new vector representation
    const vector<GradeRecord>& getGradeBook() const { return gradeBook; }

    // Enrolment
    bool     enrollStudent   (Student* s);
    bool     dropStudent     (const string& sid);
    void     addStudentDirect(Student* s);  // for DB load — no side effects
    Student* findStudent     (const string& sid) const;
    bool     hasStudent      (const string& sid) const;

    // Grading
    void   setScore     (const string& sid, const string& type, double score);
    double getFinalGrade(const string& sid) const;
    void   setGradeEntry(const string& sid, const GradeEntry& ge); // for DB load

    // Pure virtual — concrete course types supply their own formula + duration
    virtual double calculateFinalGrade(const string& sid,
                                       const GradeEntry& g) const = 0;
    virtual int    getExamDuration() const = 0;

    virtual void   displayInfo() const;
    virtual string serialize()   const;
};


#endif // COURSE_H
