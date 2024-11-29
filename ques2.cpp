#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>

// Constants for Wi-Fi 5 (802.11ac)
const double BANDWIDTH = 20e6;  // 20 MHz for simplicity (Wi-Fi 5 supports up to 160 MHz) 

const int MODULATION = 8;       // 256-QAM (8 bits per symbol)
const double CODING_RATE = 5.0 / 6.0;
const double DATA_RATE = BANDWIDTH * MODULATION * CODING_RATE;  // bits per second
const int PACKET_SIZE = 8192;   // 1 KB in bits
const int CSI_PACKET_SIZE = 200 * 8; // 200 bytes in bits for CSI
const double TRANSMISSION_TIME = PACKET_SIZE / DATA_RATE;  // time for one packet transmission in seconds
const double CSI_TIME = CSI_PACKET_SIZE / DATA_RATE;  // time for one CSI packet transmission
const double MAX_BACKOFF = 10e-6;  // 10 µs backoff
const double PARALLEL_COMMUNICATION_TIME = 0.015;  // 15 ms of parallel communication

// Frequency Channel Class
class FrequencyChannel {
public:
    bool isChannelFree(int users) {
        // Simulate channel contention: The more users, the lower the chance the channel is free
        double probability = 1.0 / (users + 1);  // The more users, the less likely the channel is free
        return (rand() / (double)RAND_MAX) < probability;
    }

    double getBackoffTime(int users) {
        // Simulate increasing backoff with more users
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0, MAX_BACKOFF * users);  // Increase backoff with users
        return distribution(generator);
    }
};

// Packet Class
class Packet {
public:
    Packet(int size) : size(size) {}
    int getSize() const { return size; }

private:
    int size;
};

// User Class
class User {
public:
    User(int id) : id(id) {}

    double sendCSI(FrequencyChannel& channel) {
        // Sending CSI takes time, equivalent to the CSI packet size transmission
        double latency = CSI_TIME;
        return latency;
    }

    double transmitPacket(FrequencyChannel& channel, int users) {
        double latency = 0.0;
        while (true) {
            if (channel.isChannelFree(users)) {
                latency += TRANSMISSION_TIME;
                return latency;
            } else {
                double backoff = channel.getBackoffTime(users);  // Increased backoff with more users
                latency += backoff;
            }
        }
    }

private:
    int id;
};

// AccessPoint Class
class AccessPoint {
public:
    AccessPoint(int maxUsers) : maxUsers(maxUsers) {}

    void simulateCommunication(int users, int packets) {
        std::vector<double> latencies;
        double total_time = 0.0;
        FrequencyChannel channel;

        // Mutex for thread safety
        std::mutex latencies_mutex;

        // Phase 1: Broadcast Packet from AP (1-time broadcast)
        double broadcast_time = TRANSMISSION_TIME;
        total_time += broadcast_time;

        // Phase 2: Collect CSI from all users
        double csi_time = 0.0;
        for (int j = 0; j < users; ++j) {
            User user(j);
            csi_time += user.sendCSI(channel);  // Collect CSI for each user
        }
        total_time += csi_time;

        // Phase 3: Parallel Communication (Round-Robin Scheduling)
        double round_robin_time = 0.0;
        std::vector<std::thread> threads;
        for (int i = 0; i < packets; ++i) {
            for (int j = 0; j < users; ++j) {
                threads.push_back(std::thread([&, j]() {
                    User user(j);
                    double packet_time = user.transmitPacket(channel, users);
                    
                    // Lock the mutex when updating the shared resource
                    std::lock_guard<std::mutex> lock(latencies_mutex);
                    latencies.push_back(packet_time);
                    round_robin_time += packet_time;
                }));
            }
            // Wait for all threads to finish before continuing to the next packet
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }

        // Total communication time = Broadcast + CSI + parallel communication
        total_time += round_robin_time;

        computeMetrics(latencies, total_time, packets);
    }

private:
    int maxUsers;

    void computeMetrics(std::vector<double>& latencies, double total_time, int packets) {
        // Total data transmitted in bits
        double total_data_bits = packets * PACKET_SIZE;  // total bits transmitted

        // Throughput in bits per second
        double throughput = total_data_bits / total_time;

        // Convert to Mbps for easier reading
        throughput /= 1e6;

        double avg_latency = 0.0;
        double max_latency = 0.0;

        for (double l : latencies) {
            avg_latency += l;
            if (l > max_latency) {
                max_latency = l;
            }
        }
        avg_latency /= latencies.size();

        // Output the results
        std::cout << "Throughput: " << std::fixed << std::setprecision(2) << throughput << " Mbps\n";
        std::cout << "Average Latency: " << std::fixed << std::setprecision(6) << (avg_latency * 1e3) << " ms\n";
        std::cout << "Maximum Latency: " << std::fixed << std::setprecision(6) << (max_latency * 1e3) << " ms\n";
    }
};

int main() {
    int packets = 1000;  // Number of packets per user
    AccessPoint ap(100);  // Maximum number of users in the system

    // Simulate for different number of users: 1, 10, 100
    for (int users : {1, 10, 100}) {
        std::cout << "Number of users: " << users << "\n";
        ap.simulateCommunication(users, packets);
        std::cout << std::endl;
    }

    return 0;
}