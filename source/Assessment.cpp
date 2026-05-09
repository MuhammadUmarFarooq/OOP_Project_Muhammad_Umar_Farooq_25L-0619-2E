#include "Assessment.h"
#include <iostream>
#include <string>

Assessment::Assessment(int Weightage=0, float rawScore=0, float MaxScore=0) {
    this->Weightage = Weightage;
    this->rawScore = rawScore;
    this->MaxScore = MaxScore;
}
