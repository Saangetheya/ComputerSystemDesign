#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    std::string filename = "sample.txt";
    std::fstream file(filename, std::ios::trunc | std::ios::out | std::ios::in);

    if (!file.is_open()) {
        return 1;
    }


    int total_line = 10;
    for (int i = 0;i < total_line;i++) {
        std::string tmp(8, '0');
        file << tmp << "\n";
    }

    file.seekg(0, std::ios_base::beg);

    int write_at = 5; // index from 0
    std::string pre;
    int c = 0;
    while (std::getline(file, pre)) {
        if (c == write_at) {
            file << "mynewcon\n";
            break;
        }

        std::cout << pre << " " << c << "\n";
        c++;
    }

    int row = 2, col = 3;
    write_at = row;
    c = 0;

    file.seekg(0, std::ios_base::beg);

    while (std::getline(file, pre)) {
        if (c == (row-1)) {
            std::string tmp(8, '0');
            tmp[col] = '1';

            file << tmp << "\n";
            break;
        }

        c++;
    }

    file.flush();
    file.close();
}