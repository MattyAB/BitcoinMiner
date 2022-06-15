#include <stdint.h>

uint32_t mineblock(uint32_t noncestart, char* version, char* prevhash, char* merkle_root, char* time, char* nbits);
void hashblock(uint32_t nonce, char* version, char* prevhash, 
    char* merkle_root, char* time, char* nbits, uint32_t* result);
void bits_to_difficulty(uint32_t bits, uint32_t* difficulty);