#ifndef REGULAR_H
#define REGULAR_H
#include "Student.h"

class Regular:public Student
{
private:
    float GPA;
public:
    Regular(string ID, string name, string email):Student(ID, name, email, "Regular") {
    }
    void displayProfile() override {
        cout << "Regular Student Profile:" << endl;
        cout << "ID: " << getID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
    }
    void calculateGPA() {
        // Implement GPA calculation logic here
        // For demonstration, we'll set a dummy GPA value
        GPA = 3.5; // This should be calculated based on assessments
    }
    ~Regular();
};



#endif // REGULAR_H
