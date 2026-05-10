#ifndef Scholarship_H
#define Scholarship_H
#include "AcademicEntity.h"
#include "Student.h"

class Scholarship :public Student{
private:    
    double minGPA;   // threshold the student must maintain
    string status;   // "Good Standing" or "Probation"
           
public:

  Scholarship(const string& id, const string& n,
                       const string& e, double minG = 3.0)
        : Student(id, n, e, "Scholarship"), minGPA(minG), status("Good Standing") {}

    double getMinGPA() const { return minGPA; }
    string getStatus() const { return status; }
    void   checkStatus();   // call after any grade update

    double calculateGPA()    const override;
    void   viewTranscript()  const override;
    void   addCourseGrade(const string& cid, double pct) override;
    void   displayProfile()  override;
    string serialize()       const override;
};
#endif // Scholarship_H