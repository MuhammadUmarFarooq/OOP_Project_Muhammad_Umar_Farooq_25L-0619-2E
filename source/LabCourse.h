#ifndef LABCOURSE_H
#define LABCOURSE_H
#include "Course.h"

/*
 * Lab courses have NO final exam (getExamDuration() returns 0).
 * The Scheduler skips them during timetabling.
 * Grade is 100% continuous assessment (assignments + quizzes only).
 * Default: 0% exam, 60% assignment, 40% quiz from weightages.txt.
 * requiresComputers = true forces the Scheduler to assign a computer lab.
 */

class LabCourse : public Course {
    bool requiresComputers;  // Scheduler uses this to find a suitable room

public:
    LabCourse(const string& cid, const string& t,
              const string& tid, int cap = 25)
        : Course(cid, t, tid, "Lab", cap), requiresComputers(true) {}

    bool   needsComputers()  const { return requiresComputers; }
    double calculateFinalGrade(const string& sid,
                               const GradeEntry& g) const override;
    int    getExamDuration() const override { return 0; }  // no exam
};


#endif // LABCOURSE_H