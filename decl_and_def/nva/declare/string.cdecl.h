/**
 * @file string.cdecl.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief nva 字符串相关声明头文件
 */

#pragma once
#ifndef NVA_STRING_CDECL_H
#define NVA_STRING_CDECL_H

#include "nva/defines.h"

NVA_EXTERN_C_BEGIN

NVA_EXTERN_INLINE int nva_strlen(const char* str);
NVA_EXTERN_INLINE char* nva_strcat(char* dest, const char* src);
NVA_EXTERN_INLINE char* nva_strcpy(char* dest, const char* src);
NVA_EXTERN_INLINE int nva_strcmp(const char* str1, const char* str2);

NVA_EXTERN_C_END

#endif  // !NVA_STRING_CDECL_H
