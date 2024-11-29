#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants for Wi-Fi 6 (OFDMA)
const double BANDWIDTH = 20e6;  // Simplified to 20 MHz
const double SUBCHANNEL_SIZES[] = {2e6, 4e6, 10e6};  // Subchannel sizes: 2 MHz, 4 MHz, 10 MHz
const int MODULATION_SCHEME = 8;  // 256-QAM (8 bits per symbol)
const double CODING_RATE = 5.0 / 6.0;
const double DATA_RATE = BANDWIDTH * MODULATION_SCHEME * CODING_RATE;  // Data rate in bps
const int PACKET_SIZE = 8192;  // Packet size in bits (1 KB)
const int CSI_PACKET_SIZE = 200 * 8;  // CSI packet size in bits (200 bytes)
const double TRANSMISSION_TIME = PACKET_SIZE / DATA_RATE;  // Time to transmit one packet
const double CSI_TIME = CSI_PACKET_SIZE / DATA_RATE;  // Time to transmit one CSI packet
const double MAX_BACKOFF = 10e-6;  // Maximum backoff time (10 µs)

#endif // CONSTANTS_H
