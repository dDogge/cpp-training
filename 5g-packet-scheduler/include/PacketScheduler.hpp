#pragma once

#include <vector>
#include "Packet.hpp"

class PacketScheduler {
public:
    PacketScheduler();
    ~PacketScheduler();
    void loadPackets();
    void processPackets();
    void printCurrentResults() const;

private:
    int totalInputLines = 0;
    int invalidInputLines = 0;
    int oversizedPacketsRejected = 0;
    int packetsTransmitted = 0;
    int packetsDropped = 0;
    int bytesTransmitted = 0;
    int currentTimeM_ = 0;
    std::vector<Packet> packets_; 
};