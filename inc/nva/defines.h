/**
 * @file defines.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief 工程宏定义
 */

#pragma once
#ifndef NVA_DEFINES_H
#define NVA_DEFINES_H

#ifdef NVA_ADD_USER_OPTIONS
#include "nva_user_options.h"
#endif

#ifdef __cplusplus
#define NVA_EXTERN_C       extern "C"
#define NVA_EXTERN_C_BEGIN extern "C" {
#define NVA_EXTERN_C_END   }
#else
#define NVA_EXTERN_C
#define NVA_EXTERN_C_BEGIN
#define NVA_EXTERN_C_END
#endif

#ifndef NVA_NO_STDDEF_H

#include <stddef.h>

typedef size_t NVA_SIZE_T;
#define NVA_NULL NULL

#else /* !NVA_NO_STDDEF_H */

#ifndef NVA_SIZE_T
#define NVA_SIZE_T unsigned int
#warning "NVA_SIZE_T is not defined, using unsigned int as default"
#endif

#ifdef __cplusplus
#define NVA_NULL nullptr
#else
#define NVA_NULL ((void*)0)
#endif

#endif /* !NVA_NO_STDDEF_H */

#if (!defined(NVA_NO_STDBOOL_H) || defined(__cplusplus))

#ifndef __cplusplus
#include <stdbool.h>
#endif

#define NVA_BOOL  bool
#define NVA_TRUE  true
#define NVA_FALSE false

#else /* (!defined(NVA_NO_STDBOOL_H) || !defined(__cplusplus) */

#define NVA_BOOL  unsigned char
#define NVA_FALSE (0)
#define NVA_TRUE  (!NVA_FALSE)

#endif /* (!defined(NVA_NO_STDBOOL_H) || !defined(__cplusplus) */

#ifdef NVA_NO_LONG_LONG_TYPE
#define NVA_LONG_LONG     long
#define NVA_LLONG_ENABLED NVA_FALSE
#else /* NVA_NO_LONG_LONG_TYPE */
#define NVA_LONG_LONG     long long
#define NVA_LLONG_ENABLED NVA_TRUE
#endif /* NVA_NO_LONG_LONG_TYPE */

/* clang-format off */

#ifndef NVA_NO_RESTRICT
    #ifdef __cplusplus
        #define NVA_RESTRICT
    #else
        #define NVA_RESTRICT restrict
    #endif
#else
    #define NVA_RESTRICT
#endif

/* clang-format on */

#ifdef NVA_USE_INLINE

#define NVA_INLINE        inline
#define NVA_STATIC_INLINE static inline

#define NVA_INLINE_MODE   NVA_TRUE

#else /* NVA_USE_INLINE */

#define NVA_INLINE
#define NVA_STATIC_INLINE

#define NVA_INLINE_MODE NVA_FALSE

#endif /* NVA_USE_INLINE */

#if (defined(NVA_USE_INLINE) && defined(NVA_USE_CONSTEXPR))
#define NVA_CONSTEXPR constexpr
#else
#define NVA_CONSTEXPR
#endif

#ifndef NVA_DEFAULT_FMT_BUFFER_SIZE
#define NVA_DEFAULT_FMT_BUFFER_SIZE 64
#endif

/**
 * 状态码
 */
enum nva_ErrorCode_ {
    NVA_SUCCESS = 0,               /**< 成功 */
    NVA_PARAM_ERROR = -1,          /**< 参数错误 */
    NVA_FULL = -2,                 /**< 数据已满 */
    NVA_EMPTY = -3,                /**< 数据为空 */
    NVA_FAIL = -4                  /**< 失败 */
};
typedef signed char nva_ErrorCode; /**< 状态码类型 */

/**
 * 计算数组的元素个数
 * @param array 数组
 * @return 数组的元素个数
 */
#define NVA_COUNTOF(array)     (sizeof(array) / sizeof(array[0]))

/**
 * 获得整数类型的位数
 * @tparam int_type 整数类型
 * @return 位数
 */
#define NVA_INT_BITS(int_type) (sizeof(int_type) * 8U)

#endif /* !NVA_DEFINES_H */
