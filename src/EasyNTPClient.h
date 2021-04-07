/*
  EasyNTPClient - Arduino library to read time from Network Time Protocol (NTP) servers.
  Created by Harsha Alva, June 29, 2017.
  Released into the public domain.

  Based on work by:
  * Francesco Potortì, 2013
  * https://playground.arduino.cc/Code/NTPclient
  *
  * Sandeep Mistry, 2016
  * https://github.com/arduino-libraries/NTPClient
*/

#ifndef EasyNTPClient_h
#define EasyNTPClient_h

#include "Arduino.h"
#include <Udp.h>

/*
 * NTP packet-related macros.
 * see https://labs.apnic.net/?p=462 for details about the NTP packet structure.
 */
#define NTP_PACKET_SIZE 48 // Size of an NTP packet
#define NTP_TX_TIMESTAMP_OFFSET 40 // offset within the packet for the TX time

#define NTP_HEADER_LI   0b11000000 // leap indicator = 3 (unsynchronized)
#define NTP_HEADER_VN   0b00100000 // version number = 4
#define NTP_HEADER_MODE 0b00000011 // mode = 3 (client)
#define NTP_HEADER_POLL 6 // polling interval as log2 seconds (2^6 = 64s)
#define NTP_HEADER_PRECISION 0xEC // system clock precision, in log2 seconds

#define NTP_SERVER_PORT 123
#define NTP_REQUEST_PORT 1123 // port used for the NTP request socket

/*
 * Error exit codes
 */
#define E_UDP_INIT_FAIL 0
#define E_UDP_REQUEST_FAIL 1
#define E_INVALID_NTP_PACKET 2

class EasyNTPClient
{
  public:
    EasyNTPClient(UDP &udp);
    EasyNTPClient(UDP& udp, const char* serverPool);
    EasyNTPClient(UDP& udp, const char* serverPool, int offset);
    int getTimeOffset();
    void setTimeOffset(int offset);
    unsigned long getUnixTime();

  private:
    UDP *mUdp;
    const char* mServerPool = "pool.ntp.org";
    int mOffset = 0;
    uint32_t mUpdateInterval = 60000;
    unsigned long mLastUpdate = 0;
    long mServerTime = 0;
    unsigned long getServerTime();
};

#endif
