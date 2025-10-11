#include "network.h"

#include <netdb.h>
#include <sys/socket.h>

#include <stdio.h>

// Printing info for single INET address interface
void print_ifaddr_info(struct ifaddrs* address, uint8_t index)
{
    int addr_family = address->ifa_addr->sa_family;
    
    printf("Interface #%u:\n", index);
    printf("    family:\t%s\n", (addr_family == AF_INET) ? "IPv4" : "IPv6");
    printf("    name:\t%s\n", address->ifa_name);
        
    char text_address[100];
    const int family_struct_size = (addr_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
    
    getnameinfo(address->ifa_addr, family_struct_size, text_address, sizeof(text_address), 0, 0, NI_NUMERICHOST);
    printf("    host:\t%s\n", text_address);
    
    getnameinfo(address->ifa_netmask, family_struct_size, text_address, sizeof(text_address), 0, 0, NI_NUMERICHOST);
    printf("    netmask:\t%s\n", text_address);
}

// Printing info for all INET address interfaces
void print_inet_interfaces(struct ifaddrs* addresses)
{
    uint8_t index = 1;
    for(struct ifaddrs* address = addresses; address != NULL; address = address->ifa_next)
    {
        if (!address->ifa_addr)
            continue;
            
        int addr_family = address->ifa_addr->sa_family;
        if (addr_family != AF_INET && addr_family != AF_INET6)
            continue;
            
        print_ifaddr_info(address, index);
        ++index;
    }
}

struct ifaddrs* get_inet_ifaddr_by_index(struct ifaddrs* addresses, uint8_t req_index)
{
    uint8_t cur_index = 1;
    for(struct ifaddrs* address = addresses; address != NULL; address = address->ifa_next)
    {
        if (!address->ifa_addr)
            continue;
            
        int addr_family = address->ifa_addr->sa_family;
        if (addr_family != AF_INET && addr_family != AF_INET6)
            continue;
            
        if (cur_index == req_index)
            return address;
            
        ++cur_index;
    }
    
    return NULL;
}
