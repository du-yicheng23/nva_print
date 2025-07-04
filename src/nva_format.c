/**
 * @file nva_format.c
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串
 */

#include "nva/defines.h"
#include "nva/stack.h"

#if (NVA_DEFAULT_FMT_BUFFER_SIZE != 0)

static char nva_default_fmt_buffer[NVA_DEFAULT_FMT_BUFFER_SIZE] = {0};
static nva_Stack nva_default_fmt_stack = NVA_STACK_INIT_VALUE;

#endif

/* #if (!NVA_INLINE_MODE) */

#include "nva/define/format.cdef.h"

/* #endif */
