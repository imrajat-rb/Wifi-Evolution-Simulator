#ifndef NETWORK_SIMULATION_H
#define NETWORK_SIMULATION_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <memory>
#include <algorithm>
#include "frequency_channel.h"

// Constants
const double BANDWIDTH = 20e6;  // 20 MHz
const int MODULATION = 8;       // 256-QAM (8 bits per symbol)
const double CODING_RATE = 5.0 / 6.0;
const double DATA_RATE = BANDWIDTH * MODULATION * CODING_RATE;  // bits per second
const int PACKET_SIZE = 8192;   // 1 KB in bits
const double TRANSMISSION_TIME = PACKET_SIZE / DATA_RATE;  // seconds

// Packet Class
template <typename T = int>
class Packet {
public:
    Packet(T size) : size(size) {
        if (size <= 0) {
            throw std::invalid_argument("Packet size must be positive");
        }
    }

    T getSize() const { return size; }

private:
    T size;
};

// User Class
template <typename T = int>
class User {
public:
    User(T id) : id(id) {
        if (id < 0) {
            throw std::invalid_argument("User ID must be non-negative");
        }
    }

    double transmitPacket(FrequencyChannel& channel, int users) {
        double latency = 0.0;
        try {
            while (true) {
                if (channel.isChannelFree(users)) {
                    latency += TRANSMISSION_TIME;
                    return latency;
                } else {
                    double backoff = channel.getBackoffTime();
                    latency += backoff;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error during packet transmission for User " << id << ": " << e.what() << std::endl;
            throw;
        }
    }

private:
    T id;
};

// AccessPoint Class
class AccessPoint {
public:
    AccessPoint(int maxUsers);
    void simulateCommunication(int users, int packets);

private:
    int maxUsers;
    void computeMetrics(std::vector<double>& latencies, double total_time, int packets);
};

#endif  // NETWORK_SIMULATION_H
