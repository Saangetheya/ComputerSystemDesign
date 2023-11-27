#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>

void setIO(std::string inputfile, std::string outputfile) {
    freopen64(inputfile.c_str(), "r", stdin);
    freopen64(outputfile.c_str(), "w", stdout);
}

void logmain(int count, int max, int min) {
    int c = count;
    float mean = 0;
    std::unordered_map<int, int> occ;

    while (c--) {
        int t;
        std::cin >> t;
        int old = occ[t];
        occ[t]++;
        int got = (count - c);
        mean = ((mean * (got - 1)) + t) / got;

        double res = 0;
        for (int i = min;i <= max;i++) {
            res += (std::pow((std::abs(occ[t] - mean)), 2) * (occ[t] - old + 1) / 1e4);
        }

        std::cout << res << "\n";
    }
}

int main(int argc, char* argv[]) {
    // logmain(1000, 99, 0);
    for (int i = 0;i < 10;i++) {
        char outfile[100], inputfile[100];
        sprintf(inputfile, "./traces/rand_test_%d.txt", i);
        sprintf(outfile, "./traces/rand_runmean_%d.txt", i);
        setIO(inputfile,outfile);
        logmain(1000,99,0);
    }
}