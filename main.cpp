#include <iostream>
#include <iomanip>
#include <string.h>

#include "sha256.h"

void print_bytes(const unsigned char *data, size_t dataLen, bool format = true) {
    for(size_t i = 0; i < dataLen; ++i) {
        std::cout << std::hex << std::setw(2) << (int)data[i];
        if (format) {
            std::cout << (((i + 1) % 16 == 0) ? "\n" : " ");
        }
    }
    std::cout << std::endl;
}

void print_bytes_reversed(const unsigned char *data, size_t dataLen, bool format = true) {
    for(size_t i = dataLen; i > 0; i--) {
        std::cout << std::hex << std::setw(2) << (int)data[i - 1];
        if (format) {
            std::cout << (((i - 1) % 16 == 0) ? "\n" : " ");
        }
    }
    std::cout << std::endl;
}

uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) <<  8) |
            ((value & 0x00FF0000) >>  8) |
            ((value & 0xFF000000) >> 24));
}

unsigned char* hexstr_to_char(const char* hexstr)
{
    size_t len = strlen(hexstr);
    size_t final_len = len / 2;
    unsigned char* chars = (unsigned char*)malloc((final_len + 1));
    for(size_t i = 0, j = 0; j < final_len; i += 2, j++)
        chars[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i+1] % 32 + 9) % 25;
    chars[final_len] = '\0';
    return chars;
}

void hexstr_to_intarray(const char* hexstr, uint32_t* outputloc)
{
    size_t len = strlen(hexstr);
    size_t intlen = (len + 7) / 8; // +7 ensures that we do a ceiling divide
    unsigned char* bytes = hexstr_to_char(hexstr);

    for(size_t i = 0; i < intlen; i++)
    {
        uint32_t a = (uint32_t)bytes[i * 4 + 3] << 24;
        *(outputloc + i) = ((uint32_t)bytes[i * 4])
            + ((uint32_t)bytes[i * 4 + 1] << 8)
            + ((uint32_t)bytes[i * 4 + 2] << 16)
            + ((uint32_t)bytes[i * 4 + 3] << 24);
    }
}

// Hashes block with given nonce, stores hash in result
void hashblock(uint32_t nonceint, uint32_t* result)
{
    char *version = "01000000";
    char *prevhash = "0000000000000000000000000000000000000000000000000000000000000000";
    char *merkle_root = "3BA3EDFD7A7B12B27AC72C3E67768F617FC81BC3888A51323A9FB8AA4B1E5E4A";
    char *time = "29AB5F49";
    char *nbits = "FFFF001D";

    uint32_t blockheader[20];

    hexstr_to_intarray(version, blockheader);
    hexstr_to_intarray(prevhash, blockheader + 1);
    hexstr_to_intarray(merkle_root, blockheader + 9);
    hexstr_to_intarray(time, blockheader + 17);
    hexstr_to_intarray(nbits, blockheader + 18);
    *(blockheader + 19) = nonceint;

    print_bytes((unsigned char*)blockheader, 80);

    for(int i = 0; i < 20; i++)
        blockheader[i] = Reverse32(blockheader[i]);

    uint32_t hash0[8];
    hash(blockheader, 640, hash0);

    print_bytes((unsigned char*)hash0, 32);

    hash(hash0, 256, result);
}

int main()
{
    uint32_t result[8];
    hashblock((uint32_t)2083236893, result);

    for(int i = 0; i < 8; i++)
        result[i] = Reverse32(result[i]);

    print_bytes_reversed((unsigned char *)result, 32);
    
    return 0;
}