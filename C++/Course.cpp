#include "Course.h"
#include <iostream>

Course::Course() {}
Course::Course(std::string name) 
    : n_name(name) {}

void Course::addStudent(const Student& student) {
    n_list.push_back(student);
}

void Course::addList(const std::vector<Student>& list) {
    for(const Student& student : list) {
        n_list.push_back(student);
    }
}

std::string Course::getName() const {
    return n_name;
}

void Course::printStudents() {
    for(const Student& student : n_list) {
        std::cout << student.getName() << "\n";
    }
}