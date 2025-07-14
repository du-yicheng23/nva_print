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

/**
 * 数字转字符串的属性
 */
typedef struct nva_NumToStringAttr {
    unsigned char base;  /**< 基数 */
    NVA_BOOL upper_case; /**< 是否为大写 */
} nva_NumToStringAttr;

extern const char nva_itoa_str_table[17];
extern const char nva_itoa_str_table_upper[17];

#if (!NVA_INLINE_MODE)

NVA_SIZE_T nva_strlen(const char* str);
char* nva_strcat(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src);
char* nva_strcpy(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src);
int nva_strcmp(const char* lhs, const char* rhs);

void* nva_memcpy(void* NVA_RESTRICT dest, const void* NVA_RESTRICT src, NVA_SIZE_T n);
void* nva_memmove(void* dest, const void* src, NVA_SIZE_T n);

int nva_atoi(const char* NVA_RESTRICT str, unsigned int* width_of_num);

/**
 * 声明 整型转字符串的函数
 * @tparam Type 整型的类型
 * @param value 待转换的整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__DECL_INT_TO_STR(Type)                                         \
    char* nva__itostr_##Type(Type value, /* NOLINT */                      \
                             char* NVA_RESTRICT str,                       \
                             const nva_NumToStringAttr* NVA_RESTRICT attr, \
                             unsigned int* width_of_num)

/**
 * 定义 整型转字符串的函数
 * @tparam Type 整型的类型
 * @param value 待转换的整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__DEF_INT_TO_STR(Type)                                                                    \
    char* nva__itostr_##Type(const Type value, /* NOLINT */                                          \
                             char* const NVA_RESTRICT str,                                           \
                             const nva_NumToStringAttr* const NVA_RESTRICT attr,                     \
                             unsigned int* const width_of_num)                                       \
    {                                                                                                \
        unsigned Type uvalue;                                                                        \
        signed char i = 0, j, k;                                                                     \
        char temp; /* 临时变量，用于最后一步逆序 */                                                  \
                                                                                                     \
        /* 获取要转换的整数的绝对值 */                                                               \
        if (value < 0) {                                                                             \
            uvalue = (unsigned Type)(-value);                                                        \
            str[i++] = '-';                                                                          \
        }                                                                                            \
        else {                                                                                       \
            uvalue = (unsigned Type)value;                                                           \
        }                                                                                            \
                                                                                                     \
        /* 转换部分，注意转换后是逆序的 */                                                           \
        do {                                                                                         \
            str[i++] = (attr->upper_case ? nva_itoa_str_table_upper[uvalue % attr->base]             \
                                         : nva_itoa_str_table[uvalue % attr->base]);                 \
            uvalue /= attr->base;                                                                    \
        } while (uvalue != 0U);                                                                      \
                                                                                                     \
        *width_of_num = (unsigned int)i;                                                             \
        str[i] = '\0';                                                                               \
                                                                                                     \
        /* 将顺序调整过来 */                                                                         \
        if (str[0] == '-') {                                                                         \
            k = 1; /* 如果是负数，符号不用调整，从符号后面开始调整 */                                \
        }                                                                                            \
        else {                                                                                       \
            k = 0; /* 否则全部都要调整 */                                                            \
        }                                                                                            \
                                                                                                     \
        /* 头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1 */                           \
        for (j = k; j <= (i - 1) / 2; j++) { /* NOLINT: the value of j would not be out of range. */ \
            temp = str[j];                                                                           \
            str[j] = str[i - 1 + k - j];                                                             \
            str[i - 1 + k - j] = temp;                                                               \
        }                                                                                            \
                                                                                                     \
        return str;                                                                                  \
    }

/**
 * 调用 整型转字符串的函数
 * @tparam Type 整型的类型
 * @param value 待转换的整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__CALL_INT_TO_STR(Type) nva__itostr_##Type

/**
 * 声明 无符号整型转字符串的函数
 * @tparam UType 无符号整型的类型
 * @param uvalue 待转换的无符号整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__DECL_UINT_TO_STR(UType)                                         \
    char* nva__uitostr_##UType(UType uvalue, /* NOLINT */                    \
                               char* NVA_RESTRICT str,                       \
                               const nva_NumToStringAttr* NVA_RESTRICT attr, \
                               unsigned int* width_of_num)

/**
 * 定义 无符号整型转字符串的函数
 * @tparam UType 无符号整型的类型
 * @param uvalue 待转换的无符号整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__DEF_UINT_TO_STR(UType)                                                                  \
    char* nva__uitostr_##UType(UType uvalue,                                                         \
                               char* const NVA_RESTRICT str,                                         \
                               const nva_NumToStringAttr* const NVA_RESTRICT attr,                   \
                               unsigned int* const width_of_num)                                     \
    {                                                                                                \
        signed char i = 0, j, k;                                                                     \
        char temp; /* 临时变量，用于最后一步逆序 */                                                  \
                                                                                                     \
        /* 转换为字符串，注意转换后是逆序的 */                                                       \
        do {                                                                                         \
            str[i++] = (attr->upper_case ? nva_itoa_str_table_upper[uvalue % attr->base]             \
                                         : nva_itoa_str_table[uvalue % attr->base]);                 \
            uvalue /= attr->base;                                                                    \
        } while (uvalue != 0U);                                                                      \
                                                                                                     \
        *width_of_num = (unsigned int)i;                                                             \
        str[i] = '\0';                                                                               \
                                                                                                     \
        /* 将顺序调整过来 */                                                                         \
        if (str[0] == '-') {                                                                         \
            k = 1; /* 如果是负数，符号不用调整，从符号后面开始调整 */                                \
        }                                                                                            \
        else {                                                                                       \
            k = 0; /* 否则全部都要调整 */                                                            \
        }                                                                                            \
                                                                                                     \
        /* 头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1 */                           \
        for (j = k; j <= (i - 1) / 2; j++) { /* NOLINT: the value of j would not be out of range. */ \
            temp = str[j];                                                                           \
            str[j] = str[i - 1 + k - j];                                                             \
            str[i - 1 + k - j] = temp;                                                               \
        }                                                                                            \
                                                                                                     \
        return str;                                                                                  \
    }

/**
 * 调用 无符号整型转字符串的函数
 * @tparam UType 无符号整型的类型
 * @param uvalue 待转换的无符号整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__CALL_UINT_TO_STR(UType) nva__uitostr_##UType

typedef unsigned int nva__uint_type;
typedef NVA_SIZE_T nva__size_type;

char* nva_itoa(int value,
               char* NVA_RESTRICT str,
               const nva_NumToStringAttr* NVA_RESTRICT attr,
               unsigned int* width_of_num);
char* nva_uitoa(unsigned int uvalue,
                char* NVA_RESTRICT str,
                const nva_NumToStringAttr* NVA_RESTRICT attr,
                unsigned int* width_of_num);

char* nva_sizetoa(NVA_SIZE_T uvalue,
                  char* NVA_RESTRICT str,
                  const nva_NumToStringAttr* NVA_RESTRICT attr,
                  unsigned int* width_of_num);

char* nva_gcvt(double value, unsigned char precision, char* NVA_RESTRICT str);

#endif /* (!NVA_INLINE_MODE) */

NVA_EXTERN_C_END

#endif  // !NVA_STRING_CDECL_H
