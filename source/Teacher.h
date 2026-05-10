#ifndef TEACHER_H
#define TEACHER_H
#include "AcademicEntity.h"

#include <vector>
#include <string>

using namespace std;

class Teacher : public AcademicEntity {
    vector<string> assignedCourseIDs;  // list of courseIDs this teacher is in

    // Parallel vectors replacing the Feedback class 
    vector<string> feedbackStudentIDs; // IDs of students who left feedback
    vector<int>    feedbackRatings;    // 1–5 star ratings
    vector<string> feedbackComments;   // free-text comments

    double avgScore; // running average of all ratings (1–5) 

    void recalcAvg(); // private — called internally whenever feedback changes

public:
    static const string FILE_PATH;

    Teacher(const string& id, const string& n, const string& e)
        : AcademicEntity(id, n, e), avgScore(0.0) { 
        file_path = FILE_PATH; // shared path "teachers.txt" 
    }

    // Updated feedback methods to use primitive parameters instead of a Feedback object
    void addFeedback(const string& sid, int rating, const string& comment);
    
    double getAverageScore() const { return avgScore; }
    void assignCourse(const string& cid);

    const vector<string>& getAssignedCourses() const { return assignedCourseIDs; }
    
    // Manual getters for parallel feedback data vectors
    const vector<string>& getFeedbackStudentIDs() const { return feedbackStudentIDs; }
    const vector<int>&    getFeedbackRatings()    const { return feedbackRatings;    }
    const vector<string>& getFeedbackComments()   const { return feedbackComments;   }

    void displayProfile() override;
    void displayFeedbacks() const;
    string serialize() const override;
};
#endif // TEACHER_H