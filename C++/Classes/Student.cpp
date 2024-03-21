#include "Student.h"

Student::Student() {}

Student::Student(std::string first, std::string last, int id, float average)
    : n_first(first) , n_last(last) , n_id(id) , n_average(average) {}

float Student::getAverage() const {
    return n_average;
} 

int Student::getId() const {
    return n_id;
}

std::string Student::getName() const {
    return n_first + " " + n_last;
} 