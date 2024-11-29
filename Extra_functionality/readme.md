WiFi 7 Communication (New Functionality)
WiFi 7 introduces Extremely High Throughput (EHT) capabilities by utilizing a 320 MHz channel width and 16 spatial streams, alongside improved multi-user OFDMA and multi-user MIMO techniques. The simulation will include:

Dynamic Bandwidth Allocation:
Users will dynamically allocate bandwidth among channels of 20 MHz, 40 MHz, 80 MHz, 160 MHz, and 320 MHz based on traffic load and number of active users. Bandwidth reallocation will occur every 5ms.

Improved Latency Optimization:
By using enhanced scheduling algorithms, the maximum latency will be reduced further. We will simulate a process where users are scheduled for transmissions based on priority, traffic load, and channel availability.

Simulation Details:

Use adaptive QAM modulation (e.g., 1024-QAM or 4096-QAM based on channel conditions).
Assume a coding rate of 3/4.
Each user sends a mix of large packets (1 MB) and small packets (512 KB), simulating real-world traffic patterns.
Each round of communication will include both uplink and downlink transmissions for 15ms, followed by 5ms for reallocation and synchronization.
Performance Metrics:
Compute and compare:

Throughput for various channel widths and spatial streams.
Average and maximum latency for (i) 1 user and 1 AP, (ii) 10 users and 1 AP, and (iii) 100 users and 1 AP.


resources:
chat gpt