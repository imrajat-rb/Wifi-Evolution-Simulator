#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <iomanip>
#include "NetworkEntity.h"

template <typename T>
class AccessPoint {
private:
    int maxUsers;
    std::vector<T*> users;

    void calculateMetrics(std::vector<double>& latencies, double total_time, int packets) const {
        double total_data_bits = packets * PACKET_SIZE;  // Total bits transmitted across all packets
        double throughput = total_data_bits / total_time / 1e6;  // Convert throughput to Mbps

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
    }

public:
    explicit AccessPoint(int maxUsers) : maxUsers(maxUsers) {}

    void addUser(T* user) {
        if (users.size() < maxUsers) {
            users.push_back(user);
        }
    }

    void simulateCommunication(int packets, double subchannel_bandwidth) {
        std::vector<double> latencies;
        FrequencyChannel channel;
        std::mutex latencies_mutex;

        // Phase 1: Broadcast packet
        double total_time = TRANSMISSION_TIME;

        // Phase 2: Collect CSI
        double csi_time = 0.0;
        for (auto* user : users) {
            csi_time += user->sendCSI(channel);
        }
        total_time += csi_time;

        // Phase 3: Parallel Communication
        double round_robin_time = 0.0;
        std::vector<std::thread> threads;

        for (int i = 0; i < packets; ++i) {
            for (auto* user : users) {
                threads.emplace_back([&, user]() {
                    double packet_time = user->transmitPacket(channel, users.size(), subchannel_bandwidth);

                    std::lock_guard<std::mutex> lock(latencies_mutex);
                    latencies.push_back(packet_time);
                    round_robin_time += packet_time;
                });
            }
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }
        total_time += round_robin_time;

        calculateMetrics(latencies, total_time, packets);
    }
};

#endif // ACCESSPOINT_H
