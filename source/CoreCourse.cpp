#include "CoreCourse.h"
// "WeightageConfig.h" is already included via Course.h

double CoreCourse::calculateFinalGrade(const string& /*sid*/, const GradeEntry& g) const {
    // 1. Declare variables to hold the weightages
    double examWt = 0.0;
    double assignWt = 0.0;
    double quizWt = 0.0;

    // 2. Fetch weightages using your pass-by-reference helper
    WeightageConfig::getWeightages("Core", examWt, assignWt, quizWt);

    // 3. Scale each score by its percentage weight
    // E.g. examScore=80, examWt=50  →  80 * (50 / 100.0) = 40 contribution
    double finalPct = (g.examScore   * examWt   / 100.0)
                    + (g.assignScore * assignWt / 100.0)
                    + (g.quizScore   * quizWt   / 100.0);
                    
    return finalPct;
}