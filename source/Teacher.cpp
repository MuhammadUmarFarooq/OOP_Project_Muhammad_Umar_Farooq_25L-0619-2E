#include "Teacher.h"
#include <iostream>
#include "AcademicEntity.h"

 Teacher::Teacher(string ID="", string name="", string email="", float FeedbackScore=0.0): AcademicEntity(ID, name, email)
    {
        this->FeedbackScore = FeedbackScore;
    }

    