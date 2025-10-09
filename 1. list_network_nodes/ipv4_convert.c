#include "ipv4_convert.h"

#include <math.h>
#include <stdint.h>

int ipv4_convert_str_to_bytes(char* str, int len, char* bytes)
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
        
        bytes[byte_index] = buf;
        ++byte_index;
        buf = 0;
    }
    
    if (byte_index != 4)
        return -1;
    
    return 0;
}
