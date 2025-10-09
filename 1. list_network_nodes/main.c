#include "network.h"

#include <stdio.h>

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
