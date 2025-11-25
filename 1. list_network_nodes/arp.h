#ifndef __1_LNN_ARP_H__
#define __1_LNN_ARP_H__

#include <net/if.h>
#include <net/ethernet.h>

#include <stdint.h>

#pragma pack(push, 1)
struct ARP_Packet
{
    struct ether_header ethernet_header;
    
    uint16_t hw_type;
    uint16_t prtcl_type;
    
    uint8_t hw_length;
    uint8_t prtcl_length;
    uint16_t operation;
    
    uint8_t sender_hw_addr[6];
    uint8_t sender_prtcl_addr[4];
    uint8_t target_hw_addr[6];
    uint8_t target_prtcl_addr[4];
};
#pragma pack(pop)

#endif
