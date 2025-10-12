#include "network.h"
#include "ipv4_convert.h"

#include <netdb.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

const uint16_t MAX_INADDR_STRUCT_SIZE = (uint16_t) fmax((double) sizeof(struct in_addr), (double) sizeof(struct in6_addr));

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

int get_ip_broadcast(struct ifaddrs* address, void* bc_ip_addr)
{
    if (!address->ifa_addr)
        return 1;
    
    int addr_family = address->ifa_addr->sa_family;
    if (addr_family != AF_INET && addr_family != AF_INET6)
        return 2;
        
    char ip_strbuf[50];
    const int family_struct_size = sizeof(struct sockaddr_in);
    char ip_addr[MAX_INADDR_STRUCT_SIZE],
         ip_mask[MAX_INADDR_STRUCT_SIZE];
    
    getnameinfo(address->ifa_addr, family_struct_size, ip_strbuf, sizeof(ip_strbuf), 0, 0, NI_NUMERICHOST);
    if (inet_pton(addr_family, ip_strbuf, ip_addr) != 1)
        return 3;
        
    getnameinfo(address->ifa_netmask, family_struct_size, ip_strbuf, sizeof(ip_strbuf), 0, 0, NI_NUMERICHOST);
    if (inet_pton(addr_family, ip_strbuf, ip_mask) != 1)
        return 4;
        
    if (addr_family == AF_INET)
    {
        struct in_addr* ipv4_addr = (struct in_addr*) ip_addr;
        struct in_addr* ipv4_mask = (struct in_addr*) ip_mask;
        struct in_addr* bc_ipv4_addr = (struct in_addr*) bc_ip_addr;
        bc_ipv4_addr->s_addr = ntohl(ipv4_addr->s_addr) | ~ntohl(ipv4_mask->s_addr);
    }
    else
    {
        struct in6_addr* ipv6_addr = (struct in6_addr*) ip_addr;
        struct in6_addr* ipv6_mask = (struct in6_addr*) ip_mask;
        struct in6_addr* bc_ipv6_addr = (struct in6_addr*) bc_ip_addr;
        for(int i = 0; i < 16; ++i)
            bc_ipv6_addr->s6_addr[i] = ipv6_addr->s6_addr[i] | ~ipv6_mask->s6_addr[i];
    }
    
    return 0;
}
