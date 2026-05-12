#include "LabCourse.h"
// "WeightageConfig.h" is already included via Course.h

double LabCourse::calculateFinalGrade(const string& /*sid*/, const GradeEntry& g) const {
    // 1. Declare variables to hold the weightages
    double examWt = 0.0, assignWt = 0.0, quizWt = 0.0;

    // 2. Fetch weightages using your pass-by-reference helper
    WeightageConfig::getWeightages("Lab", examWt, assignWt, quizWt);

    // 3. Return the calculated final grade
    // As you noted, examPct is 0 for Lab, so we safely omit it from the math!
    return (g.assignScore * assignWt / 100.0)
         + (g.quizScore   * quizWt   / 100.0);
}