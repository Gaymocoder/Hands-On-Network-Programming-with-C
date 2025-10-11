#ifndef __1_LNN_IPV4_CONVERT_H__
#define __1_LNN_IPV4_CONVERT_H__

#include <ifaddrs.h>

#include <stdint.h>

int ipv4_convert_str_to_bytes(char* str, int len, char (*bytes)[4]);

uint32_t ipv4_convert_bytes_to_uint(char (*ip_bytes)[4]);

int ipv4_convert_uint_to_str(uint32_t ip_uint, char* str, int len);

#endif
