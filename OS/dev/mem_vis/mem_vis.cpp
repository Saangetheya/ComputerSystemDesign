#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string filepath = "./memory.txt";
    std::ifstream file(filepath);

    std::string outfile = "./memory_out.txt";

    freopen64(outfile.c_str(), "w+", stdout);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return 1;
    }

    int c = 0;

    while (!file.eof()) {
        std::string line;
        std::getline(file, line);

        for (int i = 0;i < line.length();i++) {
            if (line[i] == '0') {
                line[i] = ' ';
            }
            else {
                line[i] = '*';
            }
        }

        std::cout << line;
        c++;
        if (c == 80) {
            std::cout << "\n";
            c = 0;
        }
    }
}