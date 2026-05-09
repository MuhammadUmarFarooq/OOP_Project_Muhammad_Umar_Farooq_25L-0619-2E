#ifndef STUDENT_H
#define STUDENT_H
#include "AcademicEntity.h"
class Student:public AcademicEntity
{
private:
    string Type; // Regular, Exchange, Scholarship
public:
    Student(string ID="", string name="", string email="", string Type=""):AcademicEntity(ID, name, email ) {
        this->Type = Type;
    } 

    virtual void displayProfile() = 0;
    virtual void calculateGPA() = 0;

    virtual void ViewTranscript() = 0;


};




#endif // STUDENT_H