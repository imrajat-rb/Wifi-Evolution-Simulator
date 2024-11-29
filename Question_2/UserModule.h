#ifndef USER_MODULE_H
#define USER_MODULE_H

#include "ChannelModule.h"

// Constants
const double DATA_RATE = 20e6 * 8 * (5.0 / 6.0); // Data rate calculation
const int PACKET_SIZE = 8192;                    // 1 KB in bits
const int CSI_PACKET_SIZE = 200 * 8;             // 200 bytes in bits
const double TRANSMISSION_TIME = PACKET_SIZE / DATA_RATE;
const double CSI_TIME = CSI_PACKET_SIZE / DATA_RATE;

class User {
private:
    int id;

public:
    explicit User(int id) : id(id) {}

    double sendCSI(ChannelBase& channel) {
        // Simulate CSI time
        return CSI_TIME;
    }

    double transmitPacket(ChannelBase& channel, int users) {
        double latency = 0.0;
        while (true) {
            if (channel.isChannelFree(users)) {
                latency += TRANSMISSION_TIME;
                return latency;
            } else {
                latency += channel.getBackoffTime(users);
            }
        }
    }
};

#endif // USER_MODULE_H
