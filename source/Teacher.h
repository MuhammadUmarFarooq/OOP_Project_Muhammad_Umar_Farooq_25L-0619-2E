#ifndef TEACHER_H
#define TEACHER_H
#include "AcademicEntity.h"
class Teacher : public AcademicEntity
{
private:
    float FeedbackScore; // Assuming feedback score is relevant for teachers
public:
    Teacher(string ID="", string name="", string email="", float FeedbackScore=0.0): AcademicEntity(ID, name, email)
    {
        this->FeedbackScore = FeedbackScore;
    }
   void displayProfile() override
    {
        cout << "Teacher Profile:" << endl;
        cout << "ID: " << getID() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Email: " << getEmail() << endl;
        cout << "Feedback Score: " << FeedbackScore << endl;
    }
};
#endif // TEACHER_H