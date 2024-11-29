#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

const double TOTAL_BANDWIDTH = 20.0; // MHz
const double MODULATION_RATE = 8.0; // 256-QAM, 8 bits/symbol
const double CODING_RATE = 5.0 / 6.0;
const int PACKET_SIZE = 1024;        // 1 KB in bytes
const int BACKOFF_MAX = 10;         // Max backoff time in ms
const int SIMULATION_TIME = 1000;   // Simulation duration in ms
const int NUM_USERS[] = {1, 10, 100}; // Number of users to simulate

struct User {
    double latency;       // Total latency for the user
    int packets_sent;     // Number of packets successfully sent
};

// Function to simulate WiFi communication
void simulate_wifi(int num_users) {
    std::vector<User> users(num_users, {0.0, 0});
    double throughput = 0.0, avg_latency = 0.0, max_latency = 0.0;
    double bandwidth_per_user = TOTAL_BANDWIDTH / num_users;

    // Random number generator for backoff times
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> backoff_dist(1, BACKOFF_MAX);

    for (int t = 0; t < SIMULATION_TIME; t++) {
        for (auto &user : users) {
            // Data rate for the user
            double data_rate = bandwidth_per_user * MODULATION_RATE * CODING_RATE; // Mbps
            double transmission_time = (PACKET_SIZE * 8) / data_rate; // Time to send one packet in ms

            // Simulate collision and backoff
            bool collision = (num_users > 1 && gen() % num_users == 0); // Random collision
            if (collision) {
                user.latency += backoff_dist(gen); // Add random backoff time
            }
            user.latency += transmission_time; // Add transmission time
            user.packets_sent++;
        }
    }

    // Calculate throughput and latencies
    throughput = std::accumulate(users.begin(), users.end(), 0.0, [](double sum, const User &u) {
        return sum + u.packets_sent * PACKET_SIZE * 8 / 1000.0; // Mbps
    });
    avg_latency = std::accumulate(users.begin(), users.end(), 0.0, [](double sum, const User &u) {
        return sum + u.latency;
    }) / num_users;
    max_latency = std::max_element(users.begin(), users.end(), [](const User &a, const User &b) {
        return a.latency < b.latency;
    })->latency;

    // Print results
    std::cout << "Throughput: " << throughput << " Mbps\n";
    std::cout << "Average Latency: " << avg_latency << " ms\n";
    std::cout << "Maximum Latency: " << max_latency << " ms\n\n";
}

int main() {
    for (int num_users : NUM_USERS) {
        std::cout << "Simulating for " << num_users << " users...\n";
        simulate_wifi(num_users);
    }
    return 0;
}
