#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    int n_id;
    std::string n_first;
    std::string n_last;
    float n_average;   

public:

    Student();
    Student(int id, std::string first, std::string last, float average);

    const int getId() const;
    const std::string getName() const;
    const float getAverage() const;
};

#endif