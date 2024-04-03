#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdint>

#include "sha256.h"
#include "miner.h"
#include "util.h"

int main()
{
    // Genesis Block info
    char version[] = "01000000";
    char prevhash[] = "0000000000000000000000000000000000000000000000000000000000000000";
    char merkle_root[] = "3BA3EDFD7A7B12B27AC72C3E67768F617FC81BC3888A51323A9FB8AA4B1E5E4A";
    char time[] = "29AB5F49";
    char nbits[] = "FFFF001D";

    uint32_t result[8];
    //uint32_t nonce = mineblock(2083236890, version, prevhash, merkle_root, time, nbits);
    uint32_t nonce = mineblock(10, version, prevhash, merkle_root, time, nbits);
    
    std::cout << "Block solved ! Nonce: " << nonce << std::endl;
    std::cout << "Block hash:" << std::endl;
    
    //hashblock((uint32_t)2083236893, result);
    hashblock(nonce, version, prevhash, merkle_root, time, nbits, result);

    for(int i = 0; i < 8; i++)
        result[i] = Reverse32(result[i]);

    print_bytes_reversed((unsigned char *)result, 32);
    
    return 0;
}
