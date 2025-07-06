/**
 * @file nva_format.c
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串
 */

#include "nva/defines.h"
#include "nva/stack.h"

static nva_Stack nva_fmt_stack = NVA_STACK_INIT_VALUE;

/* #if (!NVA_INLINE_MODE) */

#include "nva/define/format.cdef.h"

/* #endif */
