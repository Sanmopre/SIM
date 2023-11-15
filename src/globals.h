#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

#define CONFIG_PATH std::string("../config/")

#include <chrono>

class Timer {
public:
    Timer() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    double elapsed() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};

#endif // GLOBALS_H
