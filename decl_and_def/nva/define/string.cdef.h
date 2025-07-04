/**
 * @file string.cdef.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief nva 字符串相关定义头文件
 */

#pragma once
#ifndef NVA_STRING_CDEF_H
#define NVA_STRING_CDEF_H

#include "nva/defines.h"
#include "nva/declare/string.cdecl.h"

#ifndef NVA_NO_STRING_H

#include <string.h>

#define NVA_USE_STD_STRING NVA_TRUE

#else /* !NVA_NO_STRING_H */

#define NVA_USE_STD_STRING NVA_FALSE

#endif /* !NVA_NO_STRING_H */

#ifdef NVA_HAVE_GCVT_FUNC

#include <stdlib.h>

#define NVA_USE_GCVT_FUNC NVA_TRUE

#else /* NVA_NO_STDLIB_H */

#define NVA_USE_GCVT_FUNC NVA_FALSE

#endif /* NVA_HAVE_GCVT_FUNC */

NVA_EXTERN_C_BEGIN

/**
 * 获取字符串的长度
 * @param str 字符串
 * @return 长度
 */
NVA_STATIC_INLINE NVA_SIZE_T nva_strlen(const char* str) /* NOLINT */
{
#if (NVA_USE_STD_STRING)
    return strlen(str);
#else
    NVA_SIZE_T len;

    for (len = 0U; str[len] != '\0'; ++len) {
    }

    return len;
#endif
}

/**
 * 字符串拼接
 * @param dest 承接字符串
 * @param src 被拼接的字符串
 * @return 拼接完成后的 dest
 */
NVA_STATIC_INLINE char* nva_strcat(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src) /* NOLINT */
{
#if (NVA_USE_STD_STRING)
    return strcat(dest, src);
#else
    NVA_SIZE_T dest_index, src_index;

    for (dest_index = 0U; dest[dest_index] != '\0'; ++dest_index) {
    }

    for (src_index = 0U; src[src_index] != '\0'; ++dest_index, ++src_index) {
        dest[dest_index] = src[src_index];
    }

    dest[dest_index] = '\0'; /* 确保字符串以 '\0' 结尾 */

    return dest;
#endif
}

/**
 * 字符串复制
 * @param dest 承接的字符串
 * @param src 被复制的字符串
 * @return 复制完成后的 dest
 */
NVA_STATIC_INLINE char* nva_strcpy(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src) /* NOLINT */
{
#if (NVA_USE_STD_STRING)
    return strcpy(dest, src);
#else
    NVA_SIZE_T i;

    for (i = 0U; src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }

    dest[i] = '\0'; /* 确保字符串以 '\0' 结尾 */

    return dest;
#endif
}

/**
 * 字符串比较
 * @param lhs 比较运算左侧的字符串
 * @param rhs 比较运算右侧的字符串
 * @return 如果 lhs < rhs 返回负数，如果 lhs > rhs 返回正数，如果相等返回 0
 */
NVA_STATIC_INLINE int nva_strcmp(const char* lhs, const char* rhs) /* NOLINT */
{
#if (NVA_USE_STD_STRING)
    return strcmp(lhs, rhs);
#else
    NVA_SIZE_T i;

    for (i = 0U; lhs[i] != '\0' && rhs[i] != '\0'; ++i) {
        if (lhs[i] != rhs[i]) {
            return (signed int)lhs[i] - (signed int)rhs[i];
        }
    }

    return (signed int)lhs[i] - (signed int)rhs[i];
#endif
}

/**
 * 内存拷贝
 * @param dest 承接的内存区域
 * @param src 被拷贝的内存区域
 * @param n 要拷贝的字节数
 * @return 拷贝后的 dest
 */
NVA_STATIC_INLINE void* nva_memcpy(void* NVA_RESTRICT dest, const void* NVA_RESTRICT src, NVA_SIZE_T n) /* NOLINT */
{
#if (NVA_USE_STD_STRING)
    return memcpy(dest, src, n);
#else
    NVA_SIZE_T i;

    if (n % sizeof(unsigned NVA_LONG_LONG) == 0) {
        n /= sizeof(unsigned NVA_LONG_LONG);

        for (i = 0U; i < n; ++i) {
            ((unsigned NVA_LONG_LONG*)dest)[i] = ((const unsigned NVA_LONG_LONG*)src)[i];
        }
    }
#if (NVA_LLONG_ENABLED)
    else if (n % sizeof(unsigned long) == 0) {
        n /= sizeof(unsigned long);

        for (i = 0U; i < n; ++i) {
            ((unsigned long*)dest)[i] = ((const unsigned long*)src)[i];
        }
    }
#endif /* (NVA_LLONG_ENABLED) */
    else if (n % sizeof(unsigned int) == 0) {
        n /= sizeof(unsigned int);

        for (i = 0U; i < n; ++i) {
            ((unsigned int*)dest)[i] = ((const unsigned int*)src)[i];
        }
    }
    else if (n % sizeof(unsigned short) == 0) {
        n /= sizeof(unsigned short);

        for (i = 0U; i < n; ++i) {
            ((unsigned short*)dest)[i] = ((const unsigned short*)src)[i];
        }
    }
    else {
        for (i = 0U; i < n; ++i) {
            ((unsigned char*)dest)[i] = ((const unsigned char*)src)[i];
        }
    }

    return dest;
#endif
}

/**
 * 整型转字符串
 * @param value 整型数值
 * @param str 字符串
 * @param base 基数，取值为 2~16
 * @param upper_case 是否为大写字母
 * @return str
 */
NVA_STATIC_INLINE char* nva_itoa(const int value, /* NOLINT */
                                 char* NVA_RESTRICT str,
                                 const unsigned char base,
                                 const NVA_BOOL upper_case)
{
    unsigned int uvalue;
    signed char i = 0, j, k;
    char temp; /* 临时变量，用于最后一步逆序 */

    /* 获取要转换的整数的绝对值 */
    if (value < 0) {
        uvalue = (unsigned int)(-value);
        str[i++] = '-';
    }
    else {
        uvalue = (unsigned int)value;
    }

    /* 转换部分，注意转换后是逆序的 */
    do {
        str[i++] = (upper_case ? nva_itoa_str_table_upper[uvalue % base] : nva_itoa_str_table[uvalue % base]);
        uvalue /= base;
    } while (uvalue != 0U);

    str[i] = '\0';

    /* 将顺序调整过来 */
    if (str[0] == '-') {
        k = 1; /* 如果是负数，符号不用调整，从符号后面开始调整 */
    }
    else {
        k = 0; /* 否则全部都要调整 */
    }

    /* 头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1 */
    for (j = k; j <= (i - 1) / 2; j++) {
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }

    return str;
}

/**
 * 无符号整型转字符串
 * @param uvalue 无符号整型数值
 * @param str 字符串
 * @param base 基数，取值为 2~16
 * @param upper_case 是否为大写字母
 * @return str
 */
NVA_STATIC_INLINE char* nva_uitoa(unsigned int uvalue, /* NOLINT */
                                  char* NVA_RESTRICT str,
                                  const unsigned char base,
                                  const NVA_BOOL upper_case)
{
    signed char i = 0, j, k;
    char temp; /* 临时变量，用于最后一步逆序 */

    /* 转换为字符串，注意转换后是逆序的 */
    do {
        str[i++] = (upper_case ? nva_itoa_str_table_upper[uvalue % base] : nva_itoa_str_table[uvalue % base]);
        uvalue /= base;
    } while (uvalue != 0U);

    str[i] = '\0';

    /* 将顺序调整过来 */
    if (str[0] == '-') {
        k = 1; /* 如果是负数，符号不用调整，从符号后面开始调整 */
    }
    else {
        k = 0; /* 否则全部都要调整 */
    }

    /* 头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1 */
    for (j = k; j <= (i - 1) / 2; j++) {
        temp = str[j];
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = temp;
    }

    return str;
}

/**
 * 浮点值转字符串
 * @param value 浮点类型数值（float 与 double 类型均可）
 * @param precision 精度（保留小数点后的位数，会自动舍入）
 * @param str 字符串
 * @return str
 */
NVA_STATIC_INLINE char* nva_gcvt(double value, const unsigned char precision, char* NVA_RESTRICT str) /* NOLINT */
{
#if (NVA_USE_GCVT_FUNC)
    return gcvt(value, precision, str);
#else
    NVA_SIZE_T integer;
    NVA_SIZE_T decimal;
    unsigned char i = 0U, j, k;
    char roundoff_value;
    NVA_BOOL is_decimal_zero = NVA_FALSE;

    if (value < 0.0) {
        str[i++] = '-';
        value = -value;
    }

    integer = (NVA_SIZE_T)value;

    value -= integer;

    /* 要多乘以一次10，因为要根据保留的下一位决定是舍入 */
    for (j = 0U; j <= precision; ++j) {
        value *= 10.0;
    }

    decimal = (NVA_SIZE_T)value; /* 取小数部分 */

    /* 取出用于判断是否舍入的数字 */
    roundoff_value = decimal % 10U;
    decimal /= 10U;

    if (precision != 0) {
        /* 转换为字符串，注意转换后是逆序的 */
        do {
            str[i++] = decimal % 10U + '0';
            decimal /= 10U;
        } while (decimal != 0U);

        if (str[0] != '-') {
            for (; i < precision; ++i) {
                str[i] = '0';
            }
        }
        else {
            for (; i - 1 < precision; ++i) {
                str[i] = '0';
            }
        }

        str[i++] = '.';

        /* 舍入 */
        if (str[0] == '-') {
            if (roundoff_value > 5) {
                str[1] += 1;
            }
            else if (roundoff_value == 5) {
                if ((str[1] - '0') % 2U != 0U) {
                    str[1] += 1;
                }
            }
        }
        else {
            if (roundoff_value > 5) {
                str[0] += 1;
            }
            else if (roundoff_value == 5) {
                if ((str[0] - '0') % 2U != 0U) {
                    str[0] += 1;
                }
            }
        }
    }
    else {
        is_decimal_zero = NVA_TRUE;
    }

    do {
        str[i++] = integer % 10U + '0';
        integer /= 10U;
    } while (integer != 0U);

    if (is_decimal_zero) {
        /* 舍入 */
        if (str[0] == '-') {
            if (roundoff_value > 5) {
                str[1] += 1;
            }
            else if (roundoff_value == 5) {
                if ((str[1] - '0') % 2U != 0U) {
                    str[1] += 1;
                }
            }
        }
        else {
            if (roundoff_value > 5) {
                str[0] += 1;
            }
            else if (roundoff_value == 5) {
                if ((str[0] - '0') % 2U != 0U) {
                    str[0] += 1;
                }
            }
        }
    }

    str[i] = '\0';

    /* 将顺序调整过来 */
    if (str[0] == '-') {
        k = 1; /* 如果是负数，符号不用调整，从符号后面开始调整 */
    }
    else {
        k = 0; /* 否则全部都要调整 */
    }

    /* 头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1 */
    for (j = k; j <= (i - 1) / 2; j++) {
        roundoff_value = str[j]; /* 由于 roundoff_value 不再需要使用，因此把它当作临时变量 */
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = roundoff_value;
    }

    return str;
#endif
}

NVA_EXTERN_C_END

#endif /* !NVA_STRING_CDEF_H */
