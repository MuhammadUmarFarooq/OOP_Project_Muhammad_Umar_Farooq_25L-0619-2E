/*
 * Core courses are lecture-based with a 3-hour final exam (180 minutes).
 * Weightages (50% exam, 30% assignment, 20% quiz by default) come from
 * weightages.txt via WeightageConfig — fully configurable without recompiling.
 */
#pragma once
#include "Course.h"
#include <string>

using namespace std;

class CoreCourse : public Course {
public:
    CoreCourse(const string& cid, const string& t,
               const string& tid, int cap = 40)
        : Course(cid, t, tid, "Core", cap) {}

    // Signature remains exactly the same
    double calculateFinalGrade(const string& sid,
                               const GradeEntry& g) const override;
                               
    int getExamDuration() const override { return 180; }  // 3 hours
};