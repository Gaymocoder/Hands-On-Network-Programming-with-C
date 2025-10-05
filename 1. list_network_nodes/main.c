#include <netdb.h>
#include <ifaddrs.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>

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

void print_inet_interfaces(struct ifaddrs* addresses)
{
    uint8_t index = 1;
    for(struct ifaddrs* address = addresses; address != NULL; address = address->ifa_next)
    {
        int addr_family = address->ifa_addr->sa_family;
        if (addr_family != AF_INET && addr_family != AF_INET6)
            continue;
            
        print_ifaddr_info(address, index);
        ++index;
    }
}

int main(int argc, char** argv)
{
    struct ifaddrs* addresses;
    if (getifaddrs(&addresses) == -1)
    {
        fprintf(stderr, "Error\nmain.c:12 — getifaddrs returned -1\n");
        return 1;
    }
    
    printf("IPv4 and IPv6 interfaces:\n\n");
    print_inet_interfaces(addresses);
}
