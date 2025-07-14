/**
 * @file nva_string.c
 * @author DuYicheng
 * @date 2025-06-28
 * @brief nva 字符串相关
 */

#include "nva/defines.h"

#if (!NVA_INLINE_MODE)

#include "nva/define/string.cdef.h"

#else

#include "nva/declare/string.cdecl.h"

#endif

const char nva_itoa_str_table[17] = "0123456789abcdef";       /**< 数字转字符的索引表 */
const char nva_itoa_str_table_upper[17] = "0123456789ABCDEF"; /**< 数字转字符的大写索引表 */

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
 * @tparam UType 这个整型对应的无符号整型的类型
 * @param value 待转换的整数
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
#define NVA__DEF_INT_TO_STR(Type, UType)                                                             \
    char* nva__itostr_##Type(const Type value, /* NOLINT */                                          \
                             char* const NVA_RESTRICT str,                                           \
                             const nva_NumToStringAttr* const NVA_RESTRICT attr,                     \
                             unsigned int* const width_of_num)                                       \
    {                                                                                                \
        UType uvalue;                                                                                \
        signed char i = 0, j, k;                                                                     \
        char temp; /* 临时变量，用于最后一步逆序 */                                                  \
                                                                                                     \
        /* 获取要转换的整数的绝对值 */                                                               \
        if (value < 0) {                                                                             \
            uvalue = (UType)(-value);                                                                \
            str[i++] = '-';                                                                          \
        }                                                                                            \
        else {                                                                                       \
            uvalue = (UType)value;                                                                   \
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

typedef NVA_LONG_LONG nva__llong_type;

typedef unsigned int nva__uint_type;
typedef unsigned long nva__ulong_type;
typedef unsigned NVA_LONG_LONG nva__ullong_type;
typedef NVA_SIZE_T nva__size_type;

static NVA__DECL_INT_TO_STR(int);
static NVA__DECL_INT_TO_STR(long);
static NVA__DECL_INT_TO_STR(nva__llong_type);

static NVA__DECL_UINT_TO_STR(nva__uint_type);
static NVA__DECL_UINT_TO_STR(nva__ulong_type);
static NVA__DECL_UINT_TO_STR(nva__ullong_type);
static NVA__DECL_UINT_TO_STR(nva__size_type);

#if (!(NVA__USE_STD_STRING && NVA_INLINE_MODE))

/**
 * 内存拷贝
 * @param dest 承接的内存区域
 * @param src 被拷贝的内存区域
 * @param n 要拷贝的字节数
 * @return 拷贝后的 dest
 */
void* nva_memcpy(void* NVA_RESTRICT dest, const void* NVA_RESTRICT src, NVA_SIZE_T n)
{
#if (NVA__USE_STD_STRING)
    return memcpy(dest, src, n);
#else
    void* const dest_store = dest;

    if (n % sizeof(unsigned NVA_LONG_LONG) == 0) {
        n /= sizeof(unsigned NVA_LONG_LONG);

        for (; n > 0; --n) {
            (*(unsigned NVA_LONG_LONG*)dest) = (*(const unsigned NVA_LONG_LONG*)src);
            ++(*((unsigned NVA_LONG_LONG**)&dest));
            ++(*((const unsigned NVA_LONG_LONG**)&src));
        }
    }
#if (NVA_LLONG_ENABLED)
    else if (n % sizeof(unsigned long) == 0) {
        n /= sizeof(unsigned long);

        for (; n > 0; --n) {
            (*(unsigned long*)dest) = (*(const unsigned long*)src);
            ++(*((unsigned long**)&dest));
            ++(*((const unsigned long**)&src));
        }
    }
#endif /* (NVA_LLONG_ENABLED) */
    else if (n % sizeof(unsigned int) == 0) {
        n /= sizeof(unsigned int);

        for (; n > 0; --n) {
            (*(unsigned int*)dest) = (*(const unsigned int*)src);
            ++(*((unsigned int**)&dest));
            ++(*((const unsigned int**)&src));
        }
    }
    else if (n % sizeof(unsigned short) == 0) {
        n /= sizeof(unsigned short);

        for (; n > 0; --n) {
            (*(unsigned short*)dest) = (*(const unsigned short*)src);
            ++(*((unsigned short**)&dest));
            ++(*((const unsigned short**)&src));
        }
    }
    else {
        for (; n > 0; --n) {
            (*(unsigned char*)dest) = (*(const unsigned char*)src);
            ++(*((unsigned char**)&dest));
            ++(*((const unsigned char**)&src));
        }
    }

    return dest_store;
#endif
}

/**
 * 内存移动
 * @param dest 承接的内存区域
 * @param src 被拷贝的内存区域
 * @param n 要拷贝的字节数
 * @return 移动后的 dest
 */
void* nva_memmove(void* dest, const void* src, NVA_SIZE_T n) /* NOLINT */
{
#if (NVA__USE_STD_STRING)
    return memmove(dest, src, n);
#else
    void* const dest_store = dest;

    if (src == dest) {
        return dest;
    }

    if (src > dest) {
        if (n % sizeof(unsigned NVA_LONG_LONG) == 0) {
            n /= sizeof(unsigned NVA_LONG_LONG);

            for (; n > 0; --n) {
                (*(unsigned NVA_LONG_LONG*)dest) = (*(const unsigned NVA_LONG_LONG*)src);
                ++(*((unsigned NVA_LONG_LONG**)&dest));
                ++(*((const unsigned NVA_LONG_LONG**)&src));
            }
        }
#if (NVA_LLONG_ENABLED)
        else if (n % sizeof(unsigned long) == 0) {
            n /= sizeof(unsigned long);

            for (; n > 0; --n) {
                (*(unsigned long*)dest) = (*(const unsigned long*)src);
                ++(*((unsigned long**)&dest));
                ++(*((const unsigned long**)&src));
            }
        }
#endif /* (NVA_LLONG_ENABLED) */
        else if (n % sizeof(unsigned int) == 0) {
            n /= sizeof(unsigned int);

            for (; n > 0; --n) {
                (*(unsigned int*)dest) = (*(const unsigned int*)src);
                ++(*((unsigned int**)&dest));
                ++(*((const unsigned int**)&src));
            }
        }
        else if (n % sizeof(unsigned short) == 0) {
            n /= sizeof(unsigned short);

            for (; n > 0; --n) {
                (*(unsigned short*)dest) = (*(const unsigned short*)src);
                ++(*((unsigned short**)&dest));
                ++(*((const unsigned short**)&src));
            }
        }
        else {
            for (; n > 0; --n) {
                (*(unsigned char*)dest) = (*(const unsigned char*)src);
                ++(*((unsigned char**)&dest));
                ++(*((const unsigned char**)&src));
            }
        }
    }
    else {
        if (n % sizeof(unsigned NVA_LONG_LONG) == 0) {
            n /= sizeof(unsigned NVA_LONG_LONG);

            for (; n > 0; --n) {
                ((unsigned NVA_LONG_LONG*)dest)[n - 1] = ((const unsigned NVA_LONG_LONG*)src)[n - 1];
            }
        }
#if (NVA_LLONG_ENABLED)
        else if (n % sizeof(unsigned long) == 0) {
            n /= sizeof(unsigned long);

            for (; n > 0; --n) {
                ((unsigned long*)dest)[n - 1] = ((const unsigned long*)src)[n - 1];
            }
        }
#endif /* (NVA_LLONG_ENABLED) */
        else if (n % sizeof(unsigned int) == 0) {
            n /= sizeof(unsigned int);

            for (; n > 0; --n) {
                ((unsigned int*)dest)[n - 1] = ((const unsigned int*)src)[n - 1];
            }
        }
        else if (n % sizeof(unsigned short) == 0) {
            n /= sizeof(unsigned short);

            for (; n > 0; --n) {
                ((unsigned short*)dest)[n - 1] = ((const unsigned short*)src)[n - 1];
            }
        }
        else {
            for (; n > 0; --n) {
                ((unsigned char*)dest)[n - 1] = ((const unsigned char*)src)[n - 1];
            }
        }
    }

    return dest_store;
#endif
}

#endif /* (!(NVA__USE_STD_STRING && NVA_INLINE_MODE)) */

/**
 * 整数字符串转整数
 * @note 这个函数遇到非数字字符（第一个 '-' 除外）之后就会立刻停止。例如 "-123a" 转化后为 -123
 * @param str 整数字符串
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return 整数
 */
int nva_atoi(const char* const NVA_RESTRICT str, unsigned int* const width_of_num) /* NOLINT */
{
    int value = 0;
    int i;
    int order = 1U;
    const NVA_BOOL is_negative = (str[0] == '-' ? NVA_TRUE : NVA_FALSE);

    for (i = (is_negative ? 1 : 0); str[i] >= '0' && str[i] <= '9'; ++i) {
    }

    if (is_negative && i == 1) {
        *width_of_num = 0;
    }
    else {
        *width_of_num = i;
    }

    --i;

    if (is_negative) {
        for (; i >= 1; --i) {
            value -= (str[i] - '0') * order;
            order *= 10;
        }
    }
    else {
        for (; i >= 0; --i) {
            value += (str[i] - '0') * order;
            order *= 10;
        }
    }

    return value;
}

static NVA__DEF_INT_TO_STR(int, nva__uint_type);
static NVA__DEF_INT_TO_STR(long, nva__ulong_type);
static NVA__DEF_INT_TO_STR(nva__llong_type, nva__ullong_type);

static NVA__DEF_UINT_TO_STR(nva__uint_type);
static NVA__DEF_UINT_TO_STR(nva__ulong_type);
static NVA__DEF_UINT_TO_STR(nva__ullong_type);
static NVA__DEF_UINT_TO_STR(nva__size_type);

/**
 * 整型转字符串
 * @param value 整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_itoa(const int value,
               char* const NVA_RESTRICT str,
               const nva_NumToStringAttr* const NVA_RESTRICT attr,
               unsigned int* const width_of_num)
{
    return NVA__CALL_INT_TO_STR(int)(value, str, attr, width_of_num);
}

/**
 * 无符号整型转字符串
 * @param uvalue 无符号整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_uitoa(unsigned int uvalue,
                char* const NVA_RESTRICT str,
                const nva_NumToStringAttr* const NVA_RESTRICT attr,
                unsigned int* const width_of_num)
{
    return NVA__CALL_UINT_TO_STR(nva__uint_type)(uvalue, str, attr, width_of_num);
}

/**
 * 长整型转字符串
 * @param value 长整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_ltoa(const long value,
               char* const NVA_RESTRICT str,
               const nva_NumToStringAttr* const NVA_RESTRICT attr,
               unsigned int* const width_of_num)
{
    return NVA__CALL_INT_TO_STR(long)(value, str, attr, width_of_num);
}

/**
 * 无符号长整型转字符串
 * @param uvalue 无符号长整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_ultoa(const unsigned long uvalue,
                char* const NVA_RESTRICT str,
                const nva_NumToStringAttr* const NVA_RESTRICT attr,
                unsigned int* const width_of_num)
{
    return NVA__CALL_UINT_TO_STR(nva__ulong_type)(uvalue, str, attr, width_of_num);
}

/**
 * 超长整型转字符串
 * @param value 超长整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_lltoa(const NVA_LONG_LONG value,
                char* const NVA_RESTRICT str,
                const nva_NumToStringAttr* const NVA_RESTRICT attr,
                unsigned int* const width_of_num)
{
    return NVA__CALL_INT_TO_STR(nva__llong_type)(value, str, attr, width_of_num);
}

/**
 * 无符号超长整型转字符串
 * @param uvalue 无符号超长整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_ulltoa(const unsigned NVA_LONG_LONG uvalue,
                 char* const NVA_RESTRICT str,
                 const nva_NumToStringAttr* const NVA_RESTRICT attr,
                 unsigned int* const width_of_num)
{
    return NVA__CALL_UINT_TO_STR(nva__ullong_type)(uvalue, str, attr, width_of_num);
}

/**
 * NVA_SIZE_T 类型整数转字符串
 * @param uvalue 无符号整型数值
 * @param str 字符串
 * @param attr 转化属性
 * @param[out] width_of_num 转化后的数字的位数（如果是负数，负号也包含在宽度内）
 * @return str
 */
char* nva_sizetoa(const NVA_SIZE_T uvalue,
                  char* const NVA_RESTRICT str,
                  const nva_NumToStringAttr* const NVA_RESTRICT attr,
                  unsigned int* const width_of_num)
{
    return NVA__CALL_UINT_TO_STR(nva__size_type)(uvalue, str, attr, width_of_num);
}

/**
 * 浮点值转字符串
 * @param value 浮点类型数值（float 与 double 类型均可）
 * @param precision 精度（保留小数点后的位数，会自动舍入）
 * @param str 字符串
 * @return str
 */
char* nva_gcvt(double value, const unsigned char precision, char* const NVA_RESTRICT str)
{
#if (NVA__USE_GCVT_FUNC)
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

    value -= (double)integer;

    /* 要多乘以一次10，因为要根据保留的下一位决定是舍入 */
    for (j = 0U; j <= precision; ++j) {
        value *= 10.0;
    }

    decimal = (NVA_SIZE_T)value; /* 取小数部分 */

    /* 取出用于判断是否舍入的数字 */
    roundoff_value = (char)(decimal % 10U);
    decimal /= 10U;

    if (precision != 0) {
        /* 转换为字符串，注意转换后是逆序的 */
        do {
            str[i++] = decimal % 10U + '0'; /* NOLINT: we can confim that (decimal % 10U) is in range [0, 9]. */
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
        str[i++] = integer % 10U + '0'; /* NOLINT: we can confim that (decimal % 10U) is in range [0, 9]. */
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
    for (j = k; j <= (i - 1) / 2; j++) { /* NOLINT: the value of j would not be out of range. */
        roundoff_value = str[j];         /* 由于 roundoff_value 不再需要使用，因此把它当作临时变量 */
        str[j] = str[i - 1 + k - j];
        str[i - 1 + k - j] = roundoff_value;
    }

    return str;
#endif
}
