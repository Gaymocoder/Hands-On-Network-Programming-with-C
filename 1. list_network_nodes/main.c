#include "network.h"
#include "ipv4_convert.h"
#include "bits.h"

#include <netdb.h>

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    int error_code = 0;
    struct ifaddrs* addresses;
    if (getifaddrs(&addresses))
    {
        fprintf(stderr, "\nError\nmain.c:12 — getifaddrs() couldn't recieve interface addresses\n");
        return 1;
    }
    
    printf("IPv4 and IPv6 interfaces:\n\n");
    print_inet_interfaces(addresses);
    
    uint8_t chosen_inet_ifaddr_num = 0;
    printf("\nChoose the interface from printed (number): ");
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
    
    char broadcast_ip_address[MAX_INADDR_STRUCT_SIZE];
    error_code = get_ip_broadcast(chosen_ifaddr, broadcast_ip_address);
    if (error_code)
    {
        fprintf(stderr, "\nError\nmain.c:41 — Failed to calculate broadcast IPv4 of chosen interface (return_code: %i)\n", error_code);
        return 4;
    }
    
    char ipv4_strbuf[50];
    error_code = ipv4_convert_uint_to_str(((struct in_addr*) broadcast_ip_address)->s_addr, ipv4_strbuf, sizeof(ipv4_strbuf));
    if (error_code)
    {
        fprintf(stderr, "\nError\nmain.c:46 — ipv4_convert_uint_to_str() recieved an incorrect length\n");
        return 5;
    }
    
    printf("IPv4 broadcast: %s\n", ipv4_strbuf);
    freeifaddrs(addresses);
    return 0;
}
