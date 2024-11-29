#include "AccessPointModule.h"

int main() {
    int packets = 1000;  // Number of packets per user
    AccessPoint ap(100);  // Access point with 100 max users

    for (int users : {1, 10, 100}) {
        std::cout << "Number of users: " << users << "\n";
        ap.simulateCommunication(users, packets);
        std::cout << std::endl;
    }

    return 0;
}
