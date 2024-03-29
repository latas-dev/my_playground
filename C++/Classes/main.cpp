#include "Student.h"
#include "Course.h"
#include <iostream>

int main(int argc, char **argv) {
    // PLAYING WITH FILE IO
    // std::ofstream output("./test/file.txt");
    // std::ifstream input("./test/read_me.txt");

    // if(output.is_open() && input.is_open()) {
    //     output << "This is a sample text file." << std::endl;
    //     output.close(); 
    // } else {
    //     // ERROR
    //     std::cerr << "Error opening files" << std::endl;
    //     return 1;
    // }

    // std::string line;
    // while(std::getline(input, line)) {
    //     std::cout << line << std::endl;
    // }
    // input.close();

    Course my_course("MATH 101");
    my_course.addFromFile("./test/students.txt");

    my_course.printStudents();
    my_course.createCourseFile("./test/math101.txt");

    return 0;
}