#include <stdint.h>

void print_bytes(const unsigned char *data, size_t dataLen, bool format = true);
void print_bytes_reversed(const unsigned char *data, size_t dataLen, bool format = true);
uint32_t Reverse32(uint32_t value);
unsigned char* hexstr_to_char(const char* hexstr);
void hexstr_to_intarray(const char* hexstr, uint32_t* outputloc);