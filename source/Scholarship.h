#ifndef Scholarship_H
#define Scholarship_H

#include "Student.h"

class Scholarship :public Student{
private:    
    bool selectedForScholarship;           
public:

Scholarship(bool selectedForScholarship);
};
#endif // Scholarship_H