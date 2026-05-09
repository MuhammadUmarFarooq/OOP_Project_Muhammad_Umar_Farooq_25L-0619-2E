#ifndef Scholarship_H
#define Scholarship_H
#include "AcademicEntity.h"
#include "Student.h"

class Scholarship :public Student{
private:    
float GPA; // Assuming GPA is relevant for scholarship students
    bool ScholarshipMantained;           
public:

Scholarship(string ID, string name, string email, bool selectedForScholarship):Student(ID, name, email, "Scholarship") {
    this->ScholarshipMantained = selectedForScholarship;                                                                          
}

void displayProfile() override {
    cout << "Scholarship Student Profile:" << endl;
    cout << "ID: " << getID() << endl;
    cout << "Name: " << getName() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Selected for Scholarship: " << (ScholarshipMantained ? "Yes" : "No") << endl;
}
void calculateGPA() override {
    // Implement GPA calculation logic here
    // For demonstration, we'll set a dummy GPA value
    this->GPA = 3.8; // This should be calculated based on assessments
    cout << "Calculated GPA: " << GPA << endl;
    if (GPA<3.0)
    {
        ScholarshipMantained = false;
        cout << "Scholarship status: Not Maintained" << endl;
    }
    
}
};
#endif // Scholarship_H