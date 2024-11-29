#ifndef FREQUENCY_CHANNEL_H
#define FREQUENCY_CHANNEL_H

#include <random>
#include <stdexcept>

const double MAX_BACKOFF = 10e-6;  // 10 µs

// Frequency Channel Class
class FrequencyChannel {
public:
    bool isChannelFree(int users);
    double getBackoffTime();
};

#endif  // FREQUENCY_CHANNEL_H
