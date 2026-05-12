/*
 * Elective courses have a lighter exam (2-hour slot) and higher assignment
 * weight (mix of assignments and final project treated as the "exam" component).
 * Default from weightages.txt: 30% exam, 40% assignment, 30% quiz.
 */
#ifndef ELECTIVECOURSE_H
#define ELECTIVECOURSE_H
#include "Course.h"

class ElectiveCourse : public Course {
public:
    ElectiveCourse(const string& cid, const string& t,
                   const string& tid, int cap = 40)
        : Course(cid, t, tid, "Elective", cap) {}

    double calculateFinalGrade(const string& sid,
                               const GradeEntry& g) const override;
    int    getExamDuration() const override { return 120; }  // 2 hours
};

#endif // ELECTIVECOURSE_H