#ifndef __1_LNN_NETWORK_H__
#define __1_LNN_NETWORK_H__

#include <ifaddrs.h>

#include <stdint.h>

void print_ifaddr_info(struct ifaddrs* address, uint8_t index);

void print_inet_interfaces(struct ifaddrs* addresses);

#endif
