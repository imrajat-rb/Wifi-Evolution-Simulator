


# WiFi Evolution Simulator

A detailed simulation framework designed to analyze the evolution of WiFi protocols (WiFi 4, 5, and 6), with a focus on throughput, latency, and multi-user capabilities.


## Features

### WiFi 4 (802.11n) Implementation
- Basic CSMA/CA mechanism
- 20 MHz bandwidth utilization
- 256-QAM modulation (8 bits per symbol)
- Single-user communication
- Random backoff mechanism for collision avoidance

### WiFi 5 (802.11ac) Implementation
- Enhanced MU-MIMO support (up to 4 spatial streams)
- CSI (Channel State Information) collection
- Parallel communication capabilities
- Thread-safe operations with mutex locks
- Round-robin scheduling with MU-MIMO grouping

### WiFi 6 (802.11ax) Implementation
- OFDMA (Orthogonal Frequency Division Multiple Access)
- Dynamic subchannel allocation (2 MHz, 4 MHz, 10 MHz)
- Enhanced parallel transmission capabilities
- Improved CSI feedback mechanism
- Adaptive scheduling based on bandwidth requirements

## Getting Started

### Prerequisites
- C++ compiler with C++11 support
- pthread library for multi-threading
- Make build system

### Installation

1. Clone the repository:
bash
git clone <repository-url>
cd wifi-simulator






## Simulation Parameters

### Common Parameters
- Bandwidth: 20 MHz
- Modulation: 256-QAM (8 bits per symbol)
- Coding Rate: 5/6
- Packet Size: 8192 bits (1 KB)
- CSI Packet Size: 1600 bits (200 bytes)

### Specific Features
- *WiFi 4*: Basic CSMA/CA with random backoff
- *WiFi 5*: MU-MIMO with 4 spatial streams
- *WiFi 6*: OFDMA with variable subchannel sizes

## Output Metrics

Each simulation provides:
- Throughput (Mbps)
- Average Latency (ms)
- Maximum Latency (ms)


## Testing

The simulations test various scenarios:
- Single user (1 user)
- Medium load (10 users)
- Heavy load (100 users)

For WiFi 6, additional tests with different subchannel bandwidths:
- 2 MHz subchannels
- 4 MHz subchannels
- 10 MHz subchannels

## Performance Analysis

Each protocol demonstrates different characteristics:
- *Question_1*: Baseline performance with traditional CSMA/CA
- *Question_2: Improved throughput with MU-MIMO capabilities
- *Question_3: Enhanced efficiency with OFDMA and dynamic subchannel allocation

## Contributing

Feel free to submit issues, fork the repository, and create pull requests for any improvements.

## sources used:

chat gpt, and other online resources
## License

This project is licensed under the MIT License - see the LICENSE file for details.
