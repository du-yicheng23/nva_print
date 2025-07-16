/**
 * @file format.h
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串
 */

#pragma once
#ifndef NVA_FORMAT_H
#define NVA_FORMAT_H

#include "nva/defines.h"

#if (NVA_INLINE_MODE)

#include "nva/define/format.cdef.h"

#else

#include "nva/declare/format.cdecl.h"

#endif

/**
 * @addtogroup nva_ParamFunctions
 * @{
 */

#ifndef __cplusplus

#if (__STDC_VERSION__ > 201100L)

#define nva_add(value, obj)                         \
    _Generic((value),                               \
        signed char: nva_char((value), (obj)),      \
        unsigned char: nva_uchar((value), (obj)),   \
        short: nva_short((value), (obj)),           \
        unsigned short: nva_ushort((value), (obj)), \
        int: nva_int((value), (obj)),               \
        unsigned int: nva_uint((value), (obj)),     \
        float: nva_float((value), (obj)),           \
        double: nva_double((value), (obj)))

#endif /* (__STDC_VERSION__ > 201100L) */

#else  /* !__cplusplus */

#include "nva/private/cpp_api/cpp_api.hpp"

#endif /* !__cplusplus */

/**
 * @}
 */

#endif /* !NVA_FORMAT_H */
