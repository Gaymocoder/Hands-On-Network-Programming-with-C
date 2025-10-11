#include "network.h"
#include "ipv4_convert.h"
#include "bits.h"

#include <netdb.h>

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    struct ifaddrs* addresses;
    if (getifaddrs(&addresses))
    {
        fprintf(stderr, "\nError\nmain.c:12 — getifaddrs() couldn't recieve interface addresses\n");
        return 1;
    }
    
    printf("IPv4 and IPv6 interfaces:\n\n");
    print_inet_interfaces(addresses);
    
    uint8_t chosen_inet_ifaddr_num = 0;
    printf("Choose the interface from printed (number): ");
    scanf("%hhu", &chosen_inet_ifaddr_num);
    
    struct ifaddrs* chosen_ifaddr = get_inet_ifaddr_by_index(addresses, chosen_inet_ifaddr_num);
    if (!chosen_ifaddr)
    {
        fprintf(stderr, "\nError\nmain.c:21 — get_inet_ifaddr_by_index() couldn't find an interface with requested index\n");
        return 2;
    }
    
    int chosen_ifaddr_family = chosen_ifaddr->ifa_addr->sa_family;
    if (chosen_ifaddr_family == AF_INET6)
    {
        fprintf(stderr, "\nError\nmain.c:19 — Can't work with IPv6 yet\n");
        return 3;
    }
    
    char ipv4_str[50];
    const int family_struct_size = sizeof(struct sockaddr_in); // (chosen_ifaddr_family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
    getnameinfo(chosen_ifaddr->ifa_addr, family_struct_size, ipv4_str, sizeof(ipv4_str), 0, 0, NI_NUMERICHOST);
    printf("Chosen IPv4: %s\n", ipv4_str);
    
    uint32_t ipv4_uint = 0;
    if (ipv4_convert_str_to_uint(ipv4_str, strlen(ipv4_str), &ipv4_uint))
    {
        fprintf(stderr, "\nError\nmain.c:46 — ipv4_convert_str_to_int() recieved an str with incorrect IPv4 format\n");
        return 4;
    }
    
    printf("Chosen IPv4 as uint: %u\n", ipv4_uint);
    printf("Chosen IPv4 as bits:\n");
    printBits(&ipv4_uint, sizeof(ipv4_uint));
    
    freeifaddrs(addresses);
    return 0;
}
