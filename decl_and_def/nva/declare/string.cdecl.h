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

extern const char nva_itoa_str_table[17];
extern const char nva_itoa_str_table_upper[17];

#if (!NVA_INLINE_MODE)

NVA_SIZE_T nva_strlen(const char* str);
char* nva_strcat(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src);
char* nva_strcpy(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src);
int nva_strcmp(const char* lhs, const char* rhs);

void* nva_memcpy(void* NVA_RESTRICT dest, const void* NVA_RESTRICT src, NVA_SIZE_T n);

int nva_atoi(const char* NVA_RESTRICT str, unsigned int* width_of_num);

char* nva_itoa(int value, char* NVA_RESTRICT str, unsigned char base, NVA_BOOL upper_case);
char* nva_uitoa(unsigned int uvalue, char* NVA_RESTRICT str, unsigned char base, NVA_BOOL upper_case);

char* nva_gcvt(double value, unsigned char precision, char* NVA_RESTRICT str);

#endif /* (!NVA_INLINE_MODE) */

NVA_EXTERN_C_END

#endif  // !NVA_STRING_CDECL_H
