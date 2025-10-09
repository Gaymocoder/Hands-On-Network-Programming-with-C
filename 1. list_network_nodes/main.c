#include "network.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    struct ifaddrs* addresses;
    if (getifaddrs(&addresses) == -1)
    {
        fprintf(stderr, "\nError\nmain.c:12 — getifaddrs() returned -1\n");
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
        fprintf(stderr, "\nError\nmain.c:21 — get_inet_ifaddr_by_index() returned NULL\n");
        return 2;
    }
    
    printf("\nChosen interface:\n");
    print_ifaddr_info(chosen_ifaddr, chosen_inet_ifaddr_num);
}
