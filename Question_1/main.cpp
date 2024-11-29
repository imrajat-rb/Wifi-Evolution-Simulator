#include <iostream>           // For std::cout, std::endl
#include <initializer_list>   // For brace-enclosed initializer lists
#include "network_simulation.h"  // Include header for AccessPoint

int main() {
    int packets = 1000;

    try {
        AccessPoint ap(100);

        for (int users : {1, 10, 100}) {
            std::cout << "Total number of users: " << users << "\n";
            ap.simulateCommunication(users, packets);
            std::cout << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Unhandled exception in main: " << e.what() << std::endl;
    }

    return 0;
}
