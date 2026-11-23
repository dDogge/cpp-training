#pragma once

struct Packet {
    int arrivalMs;
    int packetId;
    int ueId;
    int priority;
    int sizeBytes;
    int deadlineMs;
};