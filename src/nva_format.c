/**
 * @file nva_format.c
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串
 */

#include "nva/defines.h"
#include "nva/stack.h"

/**
 * 格式化所用的栈（用于保存待格式化的数据）
 */
static nva_Stack nva_fmt_stack = NVA_STACK_INIT_VALUE;

/* 此处不支持内联 */
/* #if (!NVA_INLINE_MODE) */

#include "nva/define/format.cdef.h"

/* #endif */
