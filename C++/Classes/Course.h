#ifndef COURSE_H
#define COURSE_H

#include "Student.h"
#include <string>
#include <vector>

class Course {

    std::string n_name;
    std::vector<Student> n_list;

public:

    Course();
    Course(std::string name);

    void addStudent(const Student& student);
    void addList(const std::vector<Student>& list);
    const std::string getName() const;
    void addFromFile(const std::string& filename);
    void printStudents() const;

};

#endif