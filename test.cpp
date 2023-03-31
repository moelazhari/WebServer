#include <iostream>
#include <fstream> // for ifstream class

int main() {
    std::string filename = "test.txt"; // replace with your filename
    
    // Try to open file in binary mode
    std::ifstream file(filename.c_str(), std::ios::binary);
    if (file.good()) {
        std::cout << "File is executable" << std::endl;
    } else {
        std::cout << "File is not executable" << std::endl;
    }
    
    return 0;
}