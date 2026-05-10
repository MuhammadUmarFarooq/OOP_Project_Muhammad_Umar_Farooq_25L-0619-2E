#ifndef QUIZ_H
#define QUIZ_H
#include "Assessment.h" 
class Quiz:public Assessment
{
private:
public:
     Quiz(double raw = 0, double max = 100, double wt = 20)
        : Assessment("Quiz", raw, max, wt) {}

    double getWeightedScore() const override {
        if (MaxScore == 0) return 0.0;// to guard against division by zero
        return (rawScore / MaxScore) * Weightage;
    }
};

#endif // QUIZ_H