#ifndef EXCHANGE_H
#define EXCHANGE_H
#include "Student.h"
class Exchange :public Student
{
private:
    vector<string> passFailCourseIDs; // list of courseIDs this exchange student is enrolled in with Pass/Fail grading
    vector<string> passFailStatus;    // "Pass" or "Fail" corresponding to the above courses
public:
    Exchange(const std::string& id, const std::string& n, const std::string& e)
        : Student(id, n, e, "Exchange") {}

    // Accessors for parallel vectors
    const std::vector<std::string>& getPassFailCourseIDs() const { return passFailCourseIDs; }
    const std::vector<std::string>& getPassFailStatus() const { return passFailStatus; }

    
    double calculateGPA()    const override { return -1.0; } 
    
    void   viewTranscript() const override;
    void   addCourseGrade(const std::string& cid, double pct) override;
    void   displayProfile()  override;
    std::string serialize()        const override;


};


#endif // EXCHANGE_H