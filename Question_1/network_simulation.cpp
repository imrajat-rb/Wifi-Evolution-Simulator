#include "network_simulation.h"

// FrequencyChannel Class
bool FrequencyChannel::isChannelFree(int users) {
    return (rand() / (double)RAND_MAX) < (1.0 / users);  // Probability the channel is free
}

double FrequencyChannel::getBackoffTime() {
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, MAX_BACKOFF);
    return distribution(generator);
}

// AccessPoint Class
AccessPoint::AccessPoint(int maxUsers) : maxUsers(maxUsers) {
    if (maxUsers <= 0) {
        throw std::invalid_argument("Max users must be positive");
    }
}

void AccessPoint::simulateCommunication(int users, int packets) {
    if (users <= 0 || packets <= 0) {
        throw std::invalid_argument("Number of users and packets must be positive");
    }

    std::vector<double> latencies;
    double total_time = 0.0;
    FrequencyChannel channel;

    try {
        for (int i = 0; i < packets; ++i) {
            for (int j = 0; j < users; ++j) {
                User<> user(j);
                double packet_time = user.transmitPacket(channel, users);
                latencies.push_back(packet_time);
                total_time += packet_time;
            }
        }

        computeMetrics(latencies, total_time, packets);
    } catch (const std::exception& e) {
        std::cerr << "Simulation error: " << e.what() << std::endl;
    }
}

void AccessPoint::computeMetrics(std::vector<double>& latencies, double total_time, int packets) {
    try {
        double total_data_bits = packets * PACKET_SIZE;

        double throughput = total_data_bits / total_time;
        throughput /= 1e6;  // Convert to Mbps

        double avg_latency = 0.0;
        double max_latency = 0.0;

        for (double l : latencies) {
            avg_latency += l;
            if (l > max_latency) {
                max_latency = l;
            }
        }
        avg_latency /= latencies.size();

        std::cout << "Throughput: " << std::fixed << std::setprecision(2) << throughput << " Mbps\n";
        std::cout << "Average Latency: " << std::fixed << std::setprecision(6) << (avg_latency * 1e3) << " ms\n";
        std::cout << "Maximum Latency: " << std::fixed << std::setprecision(6) << (max_latency * 1e3) << " ms\n";
    } catch (const std::exception& e) {
        std::cerr << "Error computing metrics: " << e.what() << std::endl;
        throw;
    }
}
