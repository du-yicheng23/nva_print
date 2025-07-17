/**
 * @file stack.cdef.h
 * @author DuYicheng
 * @date 2025-06-29
 * @brief 栈 定义
 */

#ifndef NVA_STACK_CDEF_H
#define NVA_STACK_CDEF_H

#include "nva/defines.h"
#include "nva/declare/stack.cdecl.h"

NVA_EXTERN_C_BEGIN

/**
 * 栈初始化
 * @param stack 待初始化的栈的地址
 * @return nva_ErrorCode
 */
NVA_STATIC_INLINE NVA_CONSTEXPR nva_ErrorCode nva_stackInit(nva_Stack* NVA_RESTRICT stack) /* NOLINT */
{
    if (stack == NVA_NULL) {
        return NVA_PARAM_ERROR;
    }

    stack->type_top = 0U;
    stack->data_top = 0U;

    return NVA_SUCCESS;
}

NVA_EXTERN_C_END

#endif /* !NVA_STACK_CDEF_H */
