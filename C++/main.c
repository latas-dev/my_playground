#include <iostream>

int main(int argc, char **argv) {

    int age = 33;
    std::string first_name = "Pedro";
    std::string last_name = "Alvarez";
    std::string full_name = first_name + " " + last_name;

    std::cout << "Hello, World!" << std::endl;
    std::cout << "My name is " << full_name << ", nice to meet you!" << std::endl;
    std::cout << "I'm " << age << " years old." << std::endl;
}