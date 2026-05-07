#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
#include "Assessment.h"

class Assignment : public Assessment {
private:
public:
    Assignment(int Weightage=0, float rawScore=0, float MaxScore=0);
    ~Assignment() {
    }
};

#endif // ASSIGNMENT_H