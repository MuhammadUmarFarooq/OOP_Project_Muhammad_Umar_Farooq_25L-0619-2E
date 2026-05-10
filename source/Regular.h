#ifndef REGULAR_H
#define REGULAR_H
#include "Student.h"

class Regular:public Student
{
private:
    float GPA;
public:
    Regular(const string& id, const string& n, const string& e)
        : Student(id, n, e, "Regular") {}

    double calculateGPA()    const override;
    void   viewTranscript()  const override;
    void   addCourseGrade(const string& cid, double pct) override;
    void   displayProfile()  override;
    string serialize()       const override;
};



#endif // REGULAR_H
