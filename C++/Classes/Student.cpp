#include "Student.h"

Student::Student() {}

Student::Student(int id, std::string first, std::string last, float average)
    : n_id(id) , n_first(first) , n_last(last) , n_average(average) {}

const int Student::getId() const {
    return n_id;
}

const std::string Student::getName() const {
    return n_first + " " + n_last;
}

const float Student::getAverage() const {
    return n_average;
}