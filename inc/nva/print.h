/**
 * @file print.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief 打印相关功能实现
 */

#ifndef NVA_PRINT_H
#define NVA_PRINT_H

#include "nva/defines.h"
#include "nva/format.h"

NVA_EXTERN_C_BEGIN

/**
 * 用户自行实现的字符打印函数
 * @param c 待打印的字符
 * @retval 1 成功打印一个字符
 * @retval 其他 打印失败
 */
int nva_putchar(char c);

nva_ErrorCode nva_print(const char* NVA_RESTRICT format, nva_FmtStatus status);

NVA_EXTERN_C_END

/**
 * @addtogroup nva_ParamFunctions
 * @{
 */

#ifndef __cplusplus

#if (__STDC_VERSION__ > 201100L)

#define nva_add(value, obj)                         \
    _Generic((value),                               \
        signed char: nva_char((value), (obj)),      \
        unsigned char: nva_uchar((value), (obj)),   \
        short: nva_short((value), (obj)),           \
        unsigned short: nva_ushort((value), (obj)), \
        int: nva_int((value), (obj)),               \
        unsigned int: nva_uint((value), (obj)),     \
        float: nva_float((value), (obj)),           \
        double: nva_double((value), (obj)))

#endif /* (__STDC_VERSION__ > 201100L) */

#else  /* !__cplusplus */

#include "nva/private/cpp_api/cpp_api.hpp"

#endif /* !__cplusplus */

/**
 * @}
 */

#endif  // !NVA_PRINT_H
