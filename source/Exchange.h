#ifndef EXCHANGE_H
#define EXCHANGE_H
#include "Student.h"
class Exchange :public Student
{
private:
    bool Semester;// pass or fail
public:
    Exchange(string ID="", string name="", string email="", bool Semester=false):Student(ID, name, email, "Exchange") {
        this->Semester = Semester;
    }
    void displayProfile() override {
        cout << "Exchange Student Profile:" << endl;
        cout << "ID: " << getID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Semester: " << (Semester ? "Pass" : "Fail") << endl;
    }
    void calculateGPA() override {
        // Implement GPA calculation logic here
        // For demonstration, we'll set a dummy GPA value
        float GPA = 3.2; // This should be calculated based on assessments
        cout << "Calculated GPA: " << GPA << endl;
    }
    ~Exchange();    
};






#endif // EXCHANGE_H