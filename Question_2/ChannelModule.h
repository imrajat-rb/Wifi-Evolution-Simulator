#ifndef CHANNEL_MODULE_H
#define CHANNEL_MODULE_H

#include <random>

// Base Class for Channels
class ChannelBase {
public:
    virtual bool isChannelFree(int users) = 0;
    virtual double getBackoffTime(int users) = 0;
    virtual ~ChannelBase() = default;
};

// Derived Class for Frequency Channel
class FrequencyChannel : public ChannelBase {
public:
    bool isChannelFree(int users) override {
        double probability = 1.0 / (users + 1);
        return (rand() / (double)RAND_MAX) < probability;
    }

    double getBackoffTime(int users) override {
        return (rand() % 10 + 1) * 1e-6 * users;  // Simulated backoff time
    }
};

// Template Channel Class
template <typename T>
class Channel : public ChannelBase {
private:
    T channelLogic;

public:
    bool isChannelFree(int users) override {
        return channelLogic.isChannelFree(users);
    }

    double getBackoffTime(int users) override {
        return channelLogic.getBackoffTime(users);
    }
};

#endif // CHANNEL_MODULE_H
