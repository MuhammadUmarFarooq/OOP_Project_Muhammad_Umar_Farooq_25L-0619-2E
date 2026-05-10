#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "Assessment.h"

class Assignment : public Assessment {
private:
public:
    Assignment(double raw = 0, double max = 100, double wt = 30)
        : Assessment("Assignment", raw, max, wt) {}

    double getWeightedScore() const override {
        if (MaxScore == 0) return 0.0;// to guard against division by zero
        return (rawScore / MaxScore) * Weightage;
    }
};

#endif // ASSIGNMENT_H