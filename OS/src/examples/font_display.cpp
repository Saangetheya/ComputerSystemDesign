#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>

// should take 64 bit value and print the mem segment of it in 8x8 mem in file
std::string from_int(int8_t a) {
    std::bitset<8> bt(a);

    std::string s(8, ' ');
    for (int i = 0;i < 8;i++) {
        if (bt.test(i)) {
            s[i] = '*';
        }
    }

    return s;
}

int main() {
    int n, t = 0;
    std::cin >> n;

    while (t < n) {
        int64_t p;
        std::cin >> p;
        std::string file_name = "font_" + std::to_string(t) + ".txt";
        std::ofstream file_stream(file_name, std::ios::binary);

        for (int i = 7;i >=0;i--) {
            int8_t g = (p >> 8 * i);
            file_stream << from_int(g) << "\n";
        }

        file_stream  <<"\n";
        t++;
    }
}