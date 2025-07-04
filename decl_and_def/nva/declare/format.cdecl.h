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

nva_DefaultFmtStatus nva_int_default(int value, nva_DefaultFmtStatus status);
nva_DefaultFmtStatus nva_uint_default(unsigned int uvalue, nva_DefaultFmtStatus status);
nva_DefaultFmtStatus nva_char_default(char ch, nva_DefaultFmtStatus status);
nva_DefaultFmtStatus nva_str_default(const char* str, nva_DefaultFmtStatus status);

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDECL_H */
