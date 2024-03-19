#include <iostream>
#include <vector>

int main(int argc, char **argv) {

    int class_amount = 0;
    std::string buffer;
    std::vector<std::string> names;


    std::cout << "How many people are in your class?" << std::endl;
    std::cin >> class_amount;

    for(int i = 0; i < class_amount; i++) {
        std::cout << "Add name " << i+1 << ": ";
        std::cin >> buffer;
        names.push_back(buffer);
    }

    // for(int i = 0; i < class_amount; i++) {
    // for(size_t i = 0; i < names.size(); i++) {
    // for(std::string name : names) {
    for(auto name : names) {
        std::cout << name << std::endl;
    }

    return 0;
}