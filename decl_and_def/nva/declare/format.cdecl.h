/**
 * @file format.cdecl.h
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串 声明
 */

#pragma once
#ifndef NVA_FORMAT_CDECL_H
#define NVA_FORMAT_CDECL_H

#include "nva/defines.h"

NVA_EXTERN_C_BEGIN

typedef struct nva_DefaultFmtStatus {
    signed char status;
} nva_DefaultFmtStatus;

#define NVA_START ((nva_DefaultFmtStatus){-1})
#define NVA_ERROR ((nva_DefaultFmtStatus){-2})

typedef struct nva_FormatStyle {
    signed char arg_id;

    char filler;

    signed char width;
    signed char precision;

    unsigned char flag;
} nva_FormatStyle;

nva_DefaultFmtStatus nva_int_default(int value, nva_DefaultFmtStatus status);
nva_DefaultFmtStatus nva_uint_default(unsigned int uvalue, nva_DefaultFmtStatus status);
nva_DefaultFmtStatus nva_char_default(char ch, nva_DefaultFmtStatus status);
nva_DefaultFmtStatus nva_str_default(const char* str, nva_DefaultFmtStatus status);

#if (__STDC_VERSION__ > 201100L)

#define nva_add(value, obj)                                                                    \
    _Generic((value),                                                                          \
        int: _Generic((obj), nva_DefaultFmtStatus: nva_int_default((value), (obj))),           \
        unsigned int: _Generic((obj), nva_DefaultFmtStatus: nva_uint_default((value), (obj))), \
        char: _Generic((obj), nva_DefaultFmtStatus: nva_char_default((value), (obj))),         \
        const char*: _Generic((obj), nva_DefaultFmtStatus: nva_str_default((value), (obj))))

#endif /* (__STDC_VERSION__ > 201100L) */

nva_ErrorCode nva_format_default(char* NVA_RESTRICT dest, const char* NVA_RESTRICT format, nva_DefaultFmtStatus status);

#if (__STDC_VERSION__ > 201100L)

#define nva_format(dest, format, obj) _Generic((obj), nva_DefaultFmtStatus: nva_format_default((dest), (format), (obj)))

#endif /* (__STDC_VERSION__ > 201100L) */

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDECL_H */
