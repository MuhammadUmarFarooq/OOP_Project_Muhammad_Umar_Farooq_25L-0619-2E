#ifndef EXAM_H
#define EXAM_H
#include "Assessment.h"

class Exam:public Assessment
{
private:
    
public:
    Exam(double raw = 0, double max = 100, double wt = 50)
        : Assessment("Exam", raw, max, wt) {}

    double getWeightedScore() const override {
        if (MaxScore == 0) return 0.0;  // guard against division by zero
        return (rawScore / MaxScore) * Weightage;
    }
};

#endif // EXAM_H