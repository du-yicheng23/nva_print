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

/**
 * 默认的格式化状态
 * @note 此处采用结构体实现了 C++ 的“强类型枚举”，可以把它当作强类型枚举使用。
 */
typedef struct nva_DefaultFmtStatus {
    signed char status;

#define NVA_START ((nva_DefaultFmtStatus){-1}) /**< 开始 */
#define NVA_ERROR ((nva_DefaultFmtStatus){-2}) /**< 错误 */
} nva_DefaultFmtStatus;

/**
 * 格式化的每一个选项。参考
 * https://fmt.dev/11.1/syntax/#format-specification-mini-language
 */
typedef struct nva_FormatStyle {
    signed char arg_id;    /**< 使用的参数的 id。为 -1 时表示默认 */

    char filler;           /**< 用于填充空位的字符。默认是空格 */

    signed char width;     /**< 宽度。为 -1 时表示默认 */
    signed char precision; /**< 浮点类型数据保留小数位数。为 -1 时表示默认（6位） */

    char type;             /**< 决定了数据应该如何呈现，不同类型可用的类型不同。'\0' 表示 none，详见 fmt 的文档 */

    /**
     * 标志。
     * @note 这个变量的每一位或两位的值分别用于表示不同的标志，具体如下：
     * |        | align | sign  | prefix | zero | L |
     * |--------|-------|-------|--------|------|---|
     * | bit(s) | [0:1] | [2:3] |   4    |   5  | 6 |
     */
    struct nva_FormatStyleFlag {
        unsigned char align : 2;  /**< 对齐设置 */
        unsigned char sign : 2;   /**< 符号设置 */
        unsigned char prefix : 1; /**< 是否增加进制前缀 */
        unsigned char zero : 1;   /**< 是否用0补全 */
        unsigned char L : 1;      /**< 是否插入数字分隔符 */
    } flag;
} nva_FormatStyle;

/**
 * nva_FormatStyle::nva_FormatStyleFlag::align 的取值
 */
enum nva_FmtStyFlgAlign {
    NVA_FMT_FLG_ALIGN_DEFAULT = 0U, /**< 默认的对齐方式 */
    NVA_FMT_FLG_ALIGN_LEFT = 1U,    /**< 左对齐 */
    NVA_FMT_FLG_ALIGN_RIGHT = 2U,   /**< 右对齐 */
    NVA_FMT_FLG_ALIGN_CENTER = 3U   /**< 居中对齐 */
};

/**
 * nva_FormatStyle::nva_FormatStyleFlag::sign 的取值
 */
enum nva_FmtStyFlgSign {
    NVA_FMT_FLG_SIGN_EXPLICITLY_POSITIVE = 0U, /**< 即使是正数也有 + */
    NVA_FMT_FLG_SIGN_NEGATIVE_ONLY = 1U,       /**< 仅负数有 - ，正数前面不显示符号 */
    NVA_FMT_FLG_SIGN_SPACE_POSITIVE = 2U       /**< 仅负数有 - ，正数前面空一格 */
};

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
