#include "RadioMonitor.hpp"
#include <iostream>

int main() {
    RadioMonitor monitor;

    std::cout << "Testing readMeasurementFile with wrong file: " << '\n';
    monitor.readMeasurementFile("wrong.txt");

    std::cout << '\n';

    std::cout << "Testing saveMeasurementFile with wrong file: " << '\n';
    monitor.saveMeasurementFile("wrong.txt");

    std::cout << '\n';

    std::cout << "Testing getBestCell with wrong file: " << '\n';
    monitor.getBestCell();

    std::cout << '\n';

    std::cout << "Testing readMeasurementFile with right file: " << '\n';
    monitor.readMeasurementFile("measurements.txt");

    std::cout << '\n';

    std::cout << "Testing saveMeasurementFile with right file: " << '\n';
    monitor.saveMeasurementFile("measurements.txt");

    std::cout << '\n';

    std::cout << "Testing getBestCell with right file: " << '\n';
    monitor.getBestCell();

    std::cout << '\n';
}