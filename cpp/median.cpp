#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int quick_select(const std::vector<int>& values, size_t k) {
    if (values.size() == 1) {
        return values[0];
    }

    const int pivot = values[0];

    std::vector<int> lows, highs, pivots;
    lows.reserve(values.size() / 2);
    highs.reserve(values.size() / 2);

    for (size_t i = 0; i < values.size(); ++i) {
        if (values[i] < pivot) {
            lows.push_back(values[i]);
        }
        else if (values[i] > pivot) {
            highs.push_back(values[i]);
        }
        else {
            pivots.push_back(values[i]);
        }
    }

    if (k < lows.size()) {
        return quick_select(lows, k);
    }
    else if (k < lows.size() + pivots.size()) {
        return pivots[0];
    }
    else {
        return quick_select(highs, k - lows.size() - pivots.size());
    }
}

int quick_select_median(const std::vector<int>& values) {
    return quick_select(values, values.size() / 2);
}

template <typename TimePointType>
int get_millis_between(const TimePointType& start, const TimePointType& end) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

size_t get_size(const std::string& arg) {
    size_t size_parsed;
    const size_t result = std::stoi(arg, &size_parsed);
    if (size_parsed != arg.size() || result <= 0)
    {
        std::cerr << "Invalid argument (need integer > 0)" << std::endl;
        exit(1);
    }

    return result;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Need argument (integer > 0)" << std::endl;
        exit(1);
    }
    const size_t size = get_size(argv[1]);

    const auto gen_start = std::chrono::high_resolution_clock::now();

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(1, 12345678);

    std::vector<int> values;
    values.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        values.push_back(dis(gen));
    }

    const auto gen_end = std::chrono::high_resolution_clock::now();

    const auto find_start = std::chrono::high_resolution_clock::now();
    const int result = quick_select_median(values);
    const auto find_end = std::chrono::high_resolution_clock::now();

    std::cout << "Result is: " << result << std::endl;
    std::cout << "Gen took : " << get_millis_between(gen_start, gen_end) << "ms" << std::endl;
    std::cout << "Find took: " << get_millis_between(find_start, find_end) << "ms" << std::endl;

    return 0;
}
