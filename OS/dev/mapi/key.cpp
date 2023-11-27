#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#define KEYIOMAP 0

#include <mem.c>


bool is_end(char c) {
    return (c == 27);
}
void setIO() {
    std::cout.sync_with_stdio(false);
    std::cin.tie(nullptr);
}

void log_message(std::string msg) {
    std::cout << "\r" << msg << std::flush;
}

void test_log() {
    int c = 10;
    std::string base = "Hi there! ";
    while (c--) {
        log_message(base + std::to_string(c));
    }
}

int main(int argc, char* argv[]) {
    setIO();
    init();

    if (fp != nullptr) {
        while (true) {
            char c;
            std::cin >> c;

            if (is_end(c)) {
                break;
            }
            else {
                log_message("Wrote " + std::string(1, c) + " to file");
                write(c, KEYIOMAP);
            }
        }
    }
    else {
        std::cerr << "Error: Could not open file " << filename << std::endl;
    }
}