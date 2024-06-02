#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <chrono>
#include <tuple>
#include <functional>

#pragma region

std::string readFile(const std::string& filePath) {
    std::ifstream myfile(filePath);

    if (!myfile) {
        std::cout<<"Error opening input file"<< std::endl;
        return std::string();
    }

    std::stringstream buffer;
    buffer << myfile.rdbuf();

    return buffer.str();
}

std::vector<std::string> readLines(const std::string& filePath) {
    std::ifstream myfile(filePath);
    std::vector<std::string> lines;

    if (!myfile) {
        std::cout<<"Error opening input file"<< std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(myfile, line))
    {
        lines.push_back(line);
    }

    return lines;
}

void showResult(const std::string& prefix, const std::tuple<int, int64_t>& resultTuple) {
    auto [result, microseconds] = resultTuple;
    double milliseconds = static_cast<double>(microseconds) / 1000;
    double seconds = static_cast<double>(milliseconds) / 1000;
    std::cout << prefix << result << "\t" 
    <<  "(Took " 
    << std::fixed << std::setprecision(6) << microseconds << "µs\t" 
    << std::fixed << std::setprecision(6) << milliseconds << "ms\t" 
    << seconds << "s)" << std::endl;
}

template <typename Func, typename... Args>
auto measureExecutionTime(Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    // Call the function with the provided arguments and get the result
    auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    return std::make_tuple(result, duration);
}

#pragma endregion Helper functions for file reading, time measurement and program flow.


int handleCase1(std::vector<std::string> input) {
    return 0;
}

int handleCase2(std::vector<std::string> input) {
    return 0;
}


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        std::cout << "Please provide input to the program\n";
        return 1;
    }

    std::string inputFile = std::string(argv[1]);
    std::vector<std::string> lines = readLines(inputFile);

    showResult("Part 1: ", measureExecutionTime(handleCase1, lines));
    showResult("Part 2: ", measureExecutionTime(handleCase2, lines));

    return 0;

}
