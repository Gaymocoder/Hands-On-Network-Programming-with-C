#include "ipv4_convert.h"
#include "endianness.h"

#include <math.h>

int ipv4_convert_str_to_bytes(char* str, int len, char (*bytes)[4])
{    
    char buf = 0;
    uint8_t byte_index = 0;
    for(int i = 0; i <= len; ++i)
    {
        if (str[i] != '.' && i != len)
            continue;
        
        if (byte_index > 3)
            return -1;
            
        int j = i;
        while (j-1 != -1 && str[j-1] != '.')
        {
            uint16_t new_buf = (str[j-1] - '0') * pow(10, i-j);
            if (new_buf > 255)
                return -1;
            
            buf += (char) new_buf;
            --j;
        }
        
        (*bytes)[byte_index] = buf;
        ++byte_index;
        buf = 0;
    }
    
    if (byte_index != 4)
        return -1;
    
    return 0;
}

uint32_t ipv4_convert_bytes_to_uint(char (*ip_bytes)[4])
{
    uint32_t _return = 0;
    char* ptr;
    int incr;
    if (GCS_LITTLE_ENDIAN)
    {
        ptr = ((char*) &_return) + 3;
        incr = -1;
    }
    else
    {
        ptr = ((char*) &_return);
        incr = 1;
    }
    
    for(int i = 0; i < 4; ++i)
    {
        *ptr = (*ip_bytes)[i];
        ptr += incr;
    }
    
    return _return;
}
