#ifndef EXCHANGE_H
#define EXCHANGE_H
#include "Student.h"
class Exchange :public Student
{
private:
    bool Semester;// pass or fail
public:
    Exchange(bool Semester);
    ~Exchange();    
};






#endif // EXCHANGE_H