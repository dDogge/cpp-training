#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <tuple>
#include "RadioMonitor.hpp"

RadioMonitor::RadioMonitor() {
    std::cout << "RadioMonitor created" << '\n';
}

RadioMonitor::~RadioMonitor() {
    std::cout << "RadioMonitor destroyed" << '\n';
}

void RadioMonitor::readMeasurementFile(const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] opening file: " << filename << '\n';
        return;
    }

    std::cout << "Reading file..." << '\n';
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    std::cout << "Done!" << '\n';
}

void RadioMonitor::saveMeasurementFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] opening file: " << filename << '\n';
        return;
    }

    measurements_.clear();

    int initial_cells = 0;
    int non_NR = 0;
    int invalid_cells = 0;
    int removed_duplicates = 0;
    int unqiue_valid_cells = 0;

    std::cout << "Saving file contents..." << '\n';
    std::string line;
    while (std::getline(file, line)) {
        initial_cells++;
        std::stringstream ss(line);
        std::string tag, str_cellId, str_frequencyMHz, str_rsrpDbm, str_sinrDb, str_scsKHz;

        std::getline(ss, tag, ',');
        if (tag != "NR") {
            non_NR++;
            continue;
        }

        std::getline(ss, str_cellId, ',');
        std::getline(ss, str_frequencyMHz, ',');
        std::getline(ss, str_rsrpDbm, ',');
        std::getline(ss, str_sinrDb, ',');
        std::getline(ss, str_scsKHz, ',');

        try {
            Measurement entry;
            entry.cellId = std::stoi(str_cellId);
            entry.frequencyMHz = std::stod(str_frequencyMHz);
            entry.rsrpDbm = std::stod(str_rsrpDbm);
            entry.sinrDb = std::stod(str_sinrDb);
            entry.scsKHz = std::stoi(str_scsKHz);

            bool validSCS =
                entry.scsKHz == 15 ||
                entry.scsKHz == 30 ||
                entry.scsKHz == 60 ||
                entry.scsKHz == 120;

            if (entry.frequencyMHz <= 0 || !validSCS) {
                invalid_cells++;
                continue;
            }

            measurements_.push_back(entry);
        } catch (const std::exception& e) {
            invalid_cells++;
        }
    }
    std::cout << "File contents saved!" << '\n';
    int before = measurements_.size();

    std::cout << "Removing duplicates..." << '\n';
    std::sort(measurements_.begin(), measurements_.end());
    auto new_end = std::unique(measurements_.begin(), measurements_.end());
    measurements_.erase(new_end, measurements_.end());

    unqiue_valid_cells = measurements_.size();
    removed_duplicates = before - unqiue_valid_cells;

    std::cout << "Done!" << '\n';
    std::cout << "Content saved:" << '\n';
    this->printContent();

    std::cout << "Info: " << '\n'
        << "Total lines:" << initial_cells << '\n'
        << "Ignored non-NR lines:" << non_NR << '\n'
        << "Invalid measurements:" << invalid_cells << '\n'
        << "Duplicates removed:" << removed_duplicates << '\n'
        << "Unique valid measurements:" << unqiue_valid_cells << '\n';
}

void RadioMonitor::printContent() const {
    for (const auto& measurement : measurements_) {
        std::cout << "[" 
            << measurement.cellId 
            << "," 
            << measurement.frequencyMHz 
            << ","
            << measurement.rsrpDbm 
            << "," 
            << measurement.sinrDb
            << "," 
            << measurement.scsKHz 
            << "]"
            << '\n';  
    }
}

std::vector<Measurement> RadioMonitor::getUsableCells() const {
    std::vector<Measurement> usableCells;
    int eligible_cells = 0;

    for (const auto& cell : measurements_) {
        if (cell.rsrpDbm >= minimalRSRP_ && cell.sinrDb >= minimalSINR_) {
            usableCells.push_back(cell);
            eligible_cells++;
        }
    }

    std::cout << "Eligible measurements: " << eligible_cells << '\n';

    return usableCells;
 }

 Measurement RadioMonitor::getBestCell() const {
    std::vector<Measurement> candidates = this->getUsableCells();
    Measurement bestCell;

    if (candidates.empty()) {
        return bestCell;
    }

    std::sort(candidates.begin(), candidates.end(), 
        [](Measurement a, Measurement b) {
            return std::tie(a.sinrDb, a.rsrpDbm, b.cellId) >
                   std::tie(b.sinrDb, b.rsrpDbm, a.cellId); 
        });

    bestCell = candidates.at(0);

    std::cout << "Best Cell:" << '\n'
        << "Cell ID: " << bestCell.cellId << '\n'
        << "Frequency: " << bestCell.frequencyMHz << '\n'
        << "RSRP: " << bestCell.rsrpDbm << '\n'
        << "SINR: " << bestCell.sinrDb << '\n'
        << "SCS: " << bestCell.scsKHz << '\n'
        << "Wavelength: " << (299792458/(bestCell.frequencyMHz*1000000))*100 << "cm" << '\n';

    return bestCell;
 }