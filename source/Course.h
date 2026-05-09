#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include "Student.h"
using namespace std;
class Course
{
private:
    string CourseID;
    string TeacherID;
    vector<Student*> enrolledStudents;

public:
    Course();
    virtual void CalculateFinalGrade() = 0;
    virtual void getExamDuration() = 0;
    
    ~Course();
};




#endif // COURSE_H