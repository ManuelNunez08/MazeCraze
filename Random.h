#include <random>

#ifndef PROJECT_3_FINAL_RANDOM_H
#define PROJECT_3_FINAL_RANDOM_H


class Random {
    static std::mt19937 random;
public:
    static int Int(int min, int max);
    static float Float(float min, float max);


};


#endif //PROJECT_3_FINAL_RANDOM_H
