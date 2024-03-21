#include "Course.h"
#include "Student.h"
#include <iostream>
#include <fstream>

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

const std::string Course::getName() const {
    return n_name;
}

void Course::addFromFile(const std::string& filename) {
    std::ifstream input(filename);

    if(input.is_open()) {
        std::string first, last;
        int id;
        float average;

        // while(std::getline(input, line)) {
        while(input >> first) {
            input >> last >> id >> average;

            Course::addStudent(Student(first, last, id, average));
        } 

        input.close();
    } else {
        // ERROR
        std::cerr << "Error opening files" << std::endl;
        // return 1;
    }


}

void Course::printStudents() const {
    for(const Student& student : n_list) {
        std::cout << student.getName() << "\t" << student.getId() << "\t" << student.getAverage() << "\n";
    }
}