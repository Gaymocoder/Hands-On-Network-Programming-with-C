#ifndef __1_LNN_ARP_H__
#define __1_LNN_ARP_H__

#include <net/if.h>
#include <net/ethernet.h>

#include <stdint.h>

#pragma pack(push, 1)
struct ARP_Packet
{
    struct ether_header ethernet_header;    // Destination MAC + Source MAC + Protocol Type (ARP)
    
    uint16_t hw_type;                       // Ethernet — 0x0001
    uint16_t prtcl_type;                    // ARP      — 0x0800
    
    uint8_t hw_length;                      // For MAC  — 0x06
    uint8_t prtcl_length;                   // For IPv4 — 0x04
    uint16_t operation;                     // Request  — 0x0001
    
    uint8_t sender_hw_addr[6];              // Source MAC (duplicate from ethernet_header)
    uint8_t sender_prtcl_addr[4];           // Source IP
    uint8_t target_hw_addr[6];              // Destination MAC (duplicate from ethernet_header)
    uint8_t target_prtcl_addr[4];           // Destination IP
};
#pragma pack(pop)

#endif
