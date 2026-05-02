#ifndef STUDENT_H
#define STUDENT_H

class Student
{
private:
    float GPA;
public:
    Student(float GPA) {
      
    }

    virtual void calculateGPA() = 0;

    virtual void ViewTranscript() = 0;

    
};




#endif // STUDENT_H