#ifndef ASSESSMENT_H
#define ASSESSMENT_H

#include <string>
class Assessment {
protected:

string assessType;   
double Weightage;
double rawScore;
double MaxScore;

public:

Assessment(const string& t, double raw, double max, double wt)
        : assessType(t), rawScore(raw), MaxScore(max), Weightage(wt) {}
        
         virtual ~Assessment() = default;
     string getType()      const { return assessType; }
    double getRawScore()  const { return rawScore;   }
    double getMaxScore()  const { return MaxScore;   }
    double getWeightage() const { return Weightage;  }

    // Setters — allow a teacher to update marks or reconfigure weights
    void setRawScore (double s) { rawScore  = s; }
    void setWeightage(double w) { Weightage = w; }
virtual double getWeightedScore() const = 0;




};

#endif