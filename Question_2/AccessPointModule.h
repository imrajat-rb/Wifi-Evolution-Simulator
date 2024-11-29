#ifndef ACCESS_POINT_MODULE_H
#define ACCESS_POINT_MODULE_H

#include "ChannelModule.h"
#include "UserModule.h"
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <iomanip>

const int NUM_SPATIAL_STREAMS = 4; // Maximum spatial streams (MU-MIMO)

class AccessPoint {
private:
    int maxUsers;

    void computeMetrics(std::vector<double>& latencies, double total_time, int packets) {
        double total_data_bits = packets * PACKET_SIZE;  // Total bits transmitted
        double throughput = total_data_bits / total_time / 1e6;  // Mbps
        double avg_latency = 0.0;
        double max_latency = 0.0;

        for (double l : latencies) {
            avg_latency += l;
            if (l > max_latency) max_latency = l;
        }
        avg_latency /= latencies.size();

        std::cout << "Throughput: " << std::fixed << std::setprecision(2) << throughput << " Mbps\n";
        std::cout << "Average Latency: " << std::fixed << std::setprecision(6) << (avg_latency * 1e3) << " ms\n";
        std::cout << "Maximum Latency: " << std::fixed << std::setprecision(6) << (max_latency * 1e3) << " ms\n";
    }

public:
    explicit AccessPoint(int maxUsers) : maxUsers(maxUsers) {}

    void simulateCommunication(int users, int packets) {
        std::vector<double> latencies;
        double total_time = 0.0;

        auto channel = std::make_unique<Channel<FrequencyChannel>>();
        std::mutex latencies_mutex;

        // Phase 1: Broadcast from AP
        total_time += TRANSMISSION_TIME;

        // Phase 2: Collect CSI
        double csi_time = 0.0;
        for (int i = 0; i < users; ++i) {
            User user(i);
            csi_time += user.sendCSI(*channel);
        }
        total_time += csi_time;

        // Phase 3: Parallel Communication using Round-Robin Scheduling
        double round_robin_time = 0.0;
        int groups = (users + NUM_SPATIAL_STREAMS - 1) / NUM_SPATIAL_STREAMS;

        for (int i = 0; i < packets; ++i) {
            for (int g = 0; g < groups; ++g) {
                std::vector<std::thread> threads;

                for (int j = 0; j < NUM_SPATIAL_STREAMS; ++j) {
                    int user_id = g * NUM_SPATIAL_STREAMS + j;
                    if (user_id >= users) break;

                    threads.emplace_back([&, user_id]() {
                        try {
                            User user(user_id);
                            double packet_time = user.transmitPacket(*channel, users);

                            std::lock_guard<std::mutex> lock(latencies_mutex);
                            latencies.push_back(packet_time);
                            round_robin_time += packet_time;
                        } catch (const std::exception& e) {
                            std::cerr << "Error: " << e.what() << "\n";
                        }
                    });
                }

                for (auto& t : threads) {
                    if (t.joinable()) t.join();
                }
            }
        }

        total_time += round_robin_time;

        // Compute metrics
        computeMetrics(latencies, total_time, packets);
    }
};

#endif // ACCESS_POINT_MODULE_H
