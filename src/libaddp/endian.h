#include <stdint.h>
#include <iostream>

template<typename T>
void little_endian(T value, const void* data)
{
    for(int i=0; i<sizeof(T); ++i)
        ((uint8_t*)data)[i] = (value >> (i*8));
}

template<typename T>
void big_endian(T value, const void* data)
{
    for(int i=0; i<sizeof(T); ++i)
        ((uint8_t*)data)[sizeof(T)-i-1] = (value >> (i*8));
}

template<typename T>
T little_endian(const void* data)
{
    T value = 0;

    for(int i=0; i<sizeof(T); ++i)
        value |= ((uint8_t*)data)[i] << (i*8);
}

template<typename T>
T big_endian(const void* data)
{
    T value = 0;

    for(int i=0; i<sizeof(T); ++i)
        value |= ((uint8_t*)data)[sizeof(T)-i-1] << (i*8);
}
