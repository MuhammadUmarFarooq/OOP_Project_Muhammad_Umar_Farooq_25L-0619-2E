#ifndef WEIGHTAGECONFIG_H
#define WEIGHTAGECONFIG_H
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class WeightageConfig {
public:
    
    static vector<string> types;
    static vector<double> examPcts;
    static vector<double> assignPcts;
    static vector<double> quizPcts;

    // Helper to get weightages for a given course type
    static void getWeightages(const std::string& courseType, double& e, double& a, double& q) {
        for (int i = 0; i < (int)types.size(); i++) {
            if (types[i] == courseType) {
                e = examPcts[i]; a = assignPcts[i]; q = quizPcts[i];
                return;
            }
        }
        e = 40.0; a = 30.0; q = 30.0; // Default fallback
    }
};

#endif // WEIGHTAGECONFIG_H