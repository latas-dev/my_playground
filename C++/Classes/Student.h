#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
    std::string n_first;
    std::string n_last;
    int n_id;
    float n_average;   

public:

    Student();
    Student(std::string first, std::string last, int id, float average);

    float getAverage() const;
    int getId() const;
    std::string getName() const;
};

#endif