#include "network.h"
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
    
    char broadcast_ip_address[MAX_INADDR_STRUCT_SIZE];
    int chosen_ifaddr_family = chosen_ifaddr->ifa_addr->sa_family;
    error_code = get_netbin_ip_broadcast(chosen_ifaddr, broadcast_ip_address);
    if (error_code)
    {
        fprintf(stderr, "\nError\nmain.c:41 — Failed to calculate broadcast IP of chosen interface (return_code: %i)\n", error_code);
        return 4;
    }
    
    char ip_strbuf[50];
    if (!inet_ntop(chosen_ifaddr_family, broadcast_ip_address, ip_strbuf, sizeof(ip_strbuf)))
    {
        fprintf(stderr, "\nError\nmain.c:50 — Failed to convert ip to string format\n");
        return 5;
    }
    
    struct if_all_addrs all_addrs;
    get_if_all_addrs(addresses, chosen_ifaddr->ifa_name, &all_addrs);
    printf("\nAll addresses of chosen interface:\n");
    print_ifaddr_info(all_addrs.addr_packet, 1);
    print_ifaddr_info(all_addrs.addr_inet, 2);
    print_ifaddr_info(all_addrs.addr_inet6, 3);
    
    printf("IP broadcast: %s\n", ip_strbuf);
    freeifaddrs(addresses);
    return 0;
}
