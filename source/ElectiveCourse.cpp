#include "ElectiveCourse.h"
// "WeightageConfig.h" is already included via Course.h

double ElectiveCourse::calculateFinalGrade(const string& /*sid*/, const GradeEntry& g) const {
    // 1. Declare the variables to hold the fetched weights
    double examWt = 0.0, assignWt = 0.0, quizWt = 0.0;
    
    // 2. Fetch the weights using your pass-by-reference method
    WeightageConfig::getWeightages("Elective", examWt, assignWt, quizWt);

    // 3. Return the calculated final grade
    return (g.examScore   * examWt   / 100.0)
         + (g.assignScore * assignWt / 100.0)
         + (g.quizScore   * quizWt   / 100.0);
}