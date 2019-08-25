//
// Created by root on 29.05.2019.
//

#ifndef RAYTRACING_DEFINES_H
#define RAYTRACING_DEFINES_H

#include <cstdint>

#define LIKELY(x)       __builtin_expect(static_cast<bool>(x),1)
#define UNLIKELY(x)     __builtin_expect(static_cast<bool>(x),0)

typedef uint16_t imageDimension_t;

typedef uint8_t  byte_t;

#endif //RAYTRACING_DEFINES_H
