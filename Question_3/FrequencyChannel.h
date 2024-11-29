#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

#include <random>
#include "Constants.h"

class FrequencyChannel {
public:
    bool isChannelAvailable(int users) {
        double probability = 1.0 / (users + 1);  // More users decrease the probability
        return (rand() / (double)RAND_MAX) < probability;
    }

    double computeBackoffTime(int users) {
        std::default_random_engine generator;
        std::uniform_real_distribution<double> distribution(0, MAX_BACKOFF * users);  // Backoff scales with users
        return distribution(generator);
    }
};

#endif // FREQUENCYCHANNEL_H
