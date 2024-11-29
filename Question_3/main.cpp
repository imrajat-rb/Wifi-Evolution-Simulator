#include "AccessPoint.h"
#include "Constants.h"
#include "NetworkEntity.h"

int main() {
    int packets = 1000;  // Number of packets per user

    AccessPoint<User> ap(100);  // Access point with max 100 users

    // Add users to the access point
    for (int i = 0; i < 100; ++i) {
        ap.addUser(new User(i));
    }

    // Simulate for different user counts and subchannel bandwidths
    for (int users : {1, 10, 100}) {
        std::cout << "Number of Users: " << users << "\n";

        for (double subchannel_bandwidth : SUBCHANNEL_SIZES) {
            std::cout << "Subchannel Bandwidth: " << subchannel_bandwidth / 1e6 << " MHz\n";

            // Simulate with the first `users` users
            AccessPoint<User> temp_ap(users);
            for (int i = 0; i < users; ++i) {
                temp_ap.addUser(new User(i));
            }

            temp_ap.simulateCommunication(packets, subchannel_bandwidth);
            std::cout << std::endl;
        }
    }

    return 0;
}
