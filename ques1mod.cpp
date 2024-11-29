#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <algorithm>

// Constants
const double BANDWIDTH = 20e6;  // 20 MHz
const int MODULATION = 8;       // 256-QAM (8 bits per symbol)
const double CODING_RATE = 5.0 / 6.0;
const double DATA_RATE = BANDWIDTH * MODULATION * CODING_RATE;  // bits per second
const int PACKET_SIZE = 8192;   // 1 KB in bits
const double TRANSMISSION_TIME = PACKET_SIZE / DATA_RATE;  // seconds
const double MAX_BACKOFF = 10e-6;  // 10 µs

// Frequency Channel Class
class FrequencyChannel {
public:
    bool isChannelFree(int users) {
        return (rand() / (double)RAND_MAX) < (1.0 / users);  // Probability the channel is free
    }

    double getBackoffTime() {
        try {
            // Random backoff time up to the maximum backoff limit
            std::default_random_engine generator;
            std::uniform_real_distribution<double> distribution(0, MAX_BACKOFF);
            return distribution(generator);
        } catch (const std::exception& e) {
            std::cerr << "Error generating backoff time: " << e.what() << std::endl;
            throw; // Re-throw the exception to notify caller
        }
    }
};

// Packet Class
template<typename T = int>
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
template<typename T = int>
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
    AccessPoint(int maxUsers) : maxUsers(maxUsers) {
        if (maxUsers <= 0) {
            throw std::invalid_argument("Max users must be positive");
        }
    }

    void simulateCommunication(int users, int packets) {
        if (users <= 0 || packets <= 0) {
            throw std::invalid_argument("Number of users and packets must be positive");
        }

        std::vector<double> latencies;
        double total_time = 0.0;
        FrequencyChannel channel;

        try {
            // Simulate communication for each user and packet
            for (int i = 0; i < packets; ++i) {
                for (int j = 0; j < users; ++j) {
                    User<> user(j);
                    double packet_time = user.transmitPacket(channel, users);
                    latencies.push_back(packet_time);
                    total_time += packet_time;  // Add the time taken for this packet to total time
                }
            }

            computeMetrics(latencies, total_time, packets);
        } catch (const std::exception& e) {
            std::cerr << "Simulation error: " << e.what() << std::endl;
        }
    }

private:
    int maxUsers;

    void computeMetrics(std::vector<double>& latencies, double total_time, int packets) {
        try {
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
        } catch (const std::exception& e) {
            std::cerr << "Error computing metrics: " << e.what() << std::endl;
            throw;
        }
    }
};

int main() {
    int packets = 1000;

    try {
        AccessPoint ap(100);

        for (int users : {1, 10, 100}) {
            std::cout << "Total number of users: " << users << "\n";
            ap.simulateCommunication(users, packets);
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception in main: " << e.what() << std::endl;
    }

    return 0;
}
