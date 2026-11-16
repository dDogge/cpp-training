#pragma once

#include <vector>
#include <iostream>
#include "Measurement.hpp"

class RadioMonitor {
public:
    RadioMonitor();
    ~RadioMonitor();
    void readMeasurementFile(const std::string& filename) const;
    void saveMeasurementFile(const std::string& filename);
    void printContent() const;
    std::vector<Measurement> getUsableCells() const;
    Measurement getBestCell() const;

private:
    std::vector<Measurement> measurements_;
    int minimalRSRP_ = -100;
    int minimalSINR_ = 5;
};