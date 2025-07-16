/**
 * @file format.cdef.h
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串 定义
 */

#pragma once
#ifndef NVA_FORMAT_CDEF_H
#define NVA_FORMAT_CDEF_H

#include "nva/defines.h"
#include "nva/declare/format.cdecl.h"
#include "nva/stack.h"

#ifndef NVA_NO_INF_AND_NAN

#include "math.h"

#define NVA__DETECT_INF_AND_NAN NVA_TRUE

#else /* !NVA_NO_INF_AND_NAN */

#define NVA__DETECT_INF_AND_NAN NVA_FALSE

#endif /* !NVA_NO_INF_AND_NAN */

NVA_EXTERN_C_BEGIN

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDEF_H */
