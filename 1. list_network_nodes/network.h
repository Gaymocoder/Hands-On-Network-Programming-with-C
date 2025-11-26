#ifndef __1_LNN_NETWORK_H__
#define __1_LNN_NETWORK_H__

#include <ifaddrs.h>
#include <arpa/inet.h>

#include <math.h>
#include <stdint.h>

struct if_all_addrs
{
    struct ifaddrs* mac;
    struct ifaddrs* inet;
    struct ifaddrs* inet6;
};

extern const uint16_t MAX_INADDR_STRUCT_SIZE;

void clear_ipv6_iface_str(char* str, int len);

void print_ifaddr_info(struct ifaddrs* address, uint8_t index);

void print_inet_interfaces(struct ifaddrs* addresses);

struct ifaddrs* get_inet_ifaddr_by_index(struct ifaddrs* addresses, uint8_t req_index);

int get_netbin_ip_broadcast(struct ifaddrs* address, void* bc_ip_addr);

#endif
