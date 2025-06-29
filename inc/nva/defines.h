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

#define NVA_BOOL  (unsigned char)
#define NVA_FALSE (0)
#define NVA_TRUE  (!NVA_FALSE)

#endif /* (!defined(NVA_NO_STDBOOL_H) || !defined(__cplusplus) */

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
#define NVA_EXTERN_INLINE extern inline

#define NVA_INLINE_MODE   NVA_TRUE

#else /* NVA_USE_INLINE */

#define NVA_INLINE
#define NVA_STATIC_INLINE
#define NVA_EXTERN_INLINE

#define NVA_INLINE_MODE NVA_FALSE

#endif /* NVA_USE_INLINE */

#if (defined(NVA_USE_INLINE) && defined(NVA_USE_CONSTEXPR))
#define NVA_CONSTEXPR constexpr
#else
#define NVA_CONSTEXPR
#endif

#endif /* !NVA_DEFINES_H */
