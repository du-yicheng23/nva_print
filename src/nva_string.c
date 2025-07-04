/**
 * @file nva_string.c
 * @author DuYicheng
 * @date 2025-06-28
 * @brief nva 字符串相关
 */

#include "nva/defines.h"

#if (!NVA_INLINE_MODE)

#include "nva/define/string.cdef.h"

#endif

const char nva_itoa_str_table[17] = "0123456789abcdef";       /**< 数字转字符的索引表 */
const char nva_itoa_str_table_upper[17] = "0123456789ABCDEF"; /**< 数字转字符的大写索引表 */
