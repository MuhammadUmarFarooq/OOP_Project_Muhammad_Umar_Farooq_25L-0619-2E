#ifndef QUIZ_H
#define QUIZ_H
#include "Assessment.h" 
class Quiz:public Assessment
{
private:
public:
    Quiz(int Weightage=0, float rawScore=0, float MaxScore=0);
    ~Quiz() {
    }
};

#endif // QUIZ_H