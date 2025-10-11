#ifndef __1_LNN_NETWORK_H__
#define __1_LNN_NETWORK_H__

#include <ifaddrs.h>

#include <stdint.h>

void print_ifaddr_info(struct ifaddrs* address, uint8_t index);

void print_inet_interfaces(struct ifaddrs* addresses);

struct ifaddrs* get_inet_ifaddr_by_index(struct ifaddrs* addresses, uint8_t req_index);

int get_ipv4_broadcast_uint(struct ifaddrs* address, uint32_t* ipv4_uint);

#endif
