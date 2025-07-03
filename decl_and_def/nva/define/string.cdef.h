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

#ifndef NVA_NO_STRING_H

#include <string.h>

#define NVA_USE_STD_STRING NVA_TRUE

#else /* !NVA_NO_STRING_H */

#define NVA_USE_STD_STRING NVA_FALSE

#endif /* !NVA_NO_STRING_H */

NVA_EXTERN_C_BEGIN

/**
 * 获取字符串的长度
 * @param str 字符串
 * @return 长度
 */
NVA_INLINE NVA_SIZE_T nva_strlen(const char* str) /* NOLINT */
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
NVA_INLINE char* nva_strcat(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src) /* NOLINT */
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
NVA_INLINE char* nva_strcpy(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src) /* NOLINT */
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
NVA_INLINE int nva_strcmp(const char* lhs, const char* rhs) /* NOLINT */
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
NVA_INLINE void* nva_memcpy(void* NVA_RESTRICT dest, const void* NVA_RESTRICT src, NVA_SIZE_T n) /* NOLINT */
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

NVA_EXTERN_C_END

#endif /* !NVA_STRING_CDEF_H */
