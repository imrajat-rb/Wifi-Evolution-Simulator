#ifndef NETWORKENTITY_H
#define NETWORKENTITY_H

#include "FrequencyChannel.h"
#include "Constants.h"

class NetworkEntity {
protected:
    int id;

public:
    explicit NetworkEntity(int id) : id(id) {}
    virtual ~NetworkEntity() = default;

    virtual double sendCSI(FrequencyChannel& channel) const {
        return CSI_TIME;  // Default CSI time
    }

    virtual double transmitPacket(FrequencyChannel& channel, int users, double subchannel_bandwidth) const = 0; // Pure virtual
};

class User : public NetworkEntity {
public:
    explicit User(int id) : NetworkEntity(id) {}

    double transmitPacket(FrequencyChannel& channel, int users, double subchannel_bandwidth) const override {
        double latency = 0.0;
        while (true) {
            if (channel.isChannelAvailable(users)) {
                double user_data_rate = subchannel_bandwidth * MODULATION_SCHEME * CODING_RATE;
                double packet_time = PACKET_SIZE / user_data_rate;
                latency += packet_time;
                return latency;
            } else {
                latency += channel.computeBackoffTime(users);
            }
        }
    }
};

#endif // NETWORKENTITY_H
