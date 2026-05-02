#include "Assessment.h"
#include <iostream>
#include <string>

Assessment::Assessment(int Weightage, float rawScore, float MaxScore) {
    this->Weightage = Weightage;
    this->rawScore = rawScore;
    this->MaxScore = MaxScore;
}
