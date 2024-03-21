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

const std::string& Course::getName() const {
    return n_name;
}

void Course::addFromFile(const std::string& filename) {
    std::ifstream input(filename);

    if(input.is_open()) {
        int id;
        std::string first, last;
        float average;

        // while(std::getline(input, line)) {
        while(input >> id) {
            input >> first >> last >> average;

            Course::addStudent(Student(id, first, last, average));
        } 

        input.close();
    } else {
        // ERROR
        std::cerr << "Error opening files" << std::endl;
        // return 1;
    }


}

void Course::createCourseFile(const std::string& filename) const {
    std::ofstream output(filename);

    output << n_name << std::endl;

    for(const Student& student : n_list) {
        output  << student.getId()      << " " 
                << student.getName()    << " " 
                << student.getAverage() << std::endl;
    }
    output.close();
}

void Course::printStudents() const {
    for(const Student& student : n_list) {
        std::cout   << student.getId()      << " " 
                    << student.getName()    << " " 
                    << student.getAverage() << "\n";
    }
}