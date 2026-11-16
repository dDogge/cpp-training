#pragma once

#include <tuple>

struct Measurement {
    int cellId = -1;
    double frequencyMHz = 0.0;
    double rsrpDbm = 0.0;
    double sinrDb = 0.0;
    int scsKHz = 0;

    friend bool operator<(const Measurement& lhs, const Measurement& rhs) {
        return std::tie(lhs.cellId, lhs.frequencyMHz, lhs.rsrpDbm, lhs.sinrDb, lhs.scsKHz) <
               std::tie(rhs.cellId, rhs.frequencyMHz, rhs.rsrpDbm, rhs.sinrDb, rhs.scsKHz);
    }

    friend bool operator==(const Measurement& lhs, const Measurement& rhs) {
        return std::tie(lhs.cellId, lhs.frequencyMHz, lhs.rsrpDbm, lhs.sinrDb, lhs.scsKHz) ==
               std::tie(rhs.cellId, rhs.frequencyMHz, rhs.rsrpDbm, rhs.sinrDb, rhs.scsKHz);
    }
};