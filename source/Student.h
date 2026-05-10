#ifndef STUDENT_H
#define STUDENT_H
#include "AcademicEntity.h"
#include <vector>
#include <string>   
class Student:public AcademicEntity
{
protected:
    string studentType;                
    vector<string> enrolledCourseIDs; // list of courseIDs this student is enrolled in
    
    // Parallel vectors 
    vector<string> transcriptCourseIDs; // IDs of courses with completed grades
    vector<double> transcriptPercentages; // 0.0 - 100.0 
    vector<string> transcriptLetterGrades;// A, A-, B+, etc.
public:

    static const string FILE_PATH; // shared path "students.txt"
   
    Student(const string& id, const string& n,
            const string& e, const string& type)
        : AcademicEntity(id, n, e), studentType(type) {
        file_path = FILE_PATH; // set inherited file_path from AcademicEntity 
    }
    virtual ~Student() = default;

    string getStudentType() const { return studentType; } 
    const vector<string>& getEnrolled() const { return enrolledCourseIDs; }
    
    //functions to manage course enrollments and transcripts
    void enrollCourse(const string& cid);
    void dropCourse(const string& cid);
    bool isEnrolledIn(const string& cid) const;
    

    void addGrade(const string& cid, double pct); 
    string getLetterGrade(const string& cid) const;

    // Pure virtuals - each student type implements these differently
    virtual double calculateGPA() const = 0; 

    virtual void viewTranscript() const = 0;


    // Polymorphic grade update (GPA vs Pass/Fail)
    virtual void addCourseGrade(const string& cid, double pct) = 0;

    virtual void displayProfile() = 0;
    


    // Static utility functions
    static string letterFromPct(double pct);
    static double gpaPointFromPct(double pct);
    

};




#endif // STUDENT_H