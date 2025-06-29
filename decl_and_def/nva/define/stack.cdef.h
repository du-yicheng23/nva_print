/**
 * @file stack.cdef.h
 * @author DuYicheng
 * @date 2025-06-29
 * @brief 栈 定义
 */

#pragma once
#ifndef NVA_STACK_CDEF_H
#define NVA_STACK_CDEF_H

#include "nva/defines.h"
#include "nva/string.h"

NVA_EXTERN_C_BEGIN

/**
 * 获取栈的深度
 * @param stack 栈的地址
 * @return 栈的深度
 */
#define NVA_STACK_DEPTH(stack) (NVA_COUNTOF((stack)->data))

/**
 * 栈初始化
 * @param stack 待初始化的栈的地址
 * @return nva_StatusCode
 */
NVA_INLINE NVA_CONSTEXPR nva_StatusCode nva_stackInit(nva_Stack* stack) /* NOLINT */
{
    if (stack == NVA_NULL) {
        return NVA_PARAM_ERROR;
    }

    stack->type_top = 0U;
    stack->data_top = 0U;

    return NVA_SUCCESS;
}

/**
 * 向栈推送数据
 * @param stack 栈结构体地址
 * @param value 推送的值的地址
 * @param type_id 推送的值的类型ID
 * @return nva_StatusCode
 */
NVA_INLINE nva_StatusCode nva_stackPush(nva_Stack* stack, const void* value, const nva_TypeId type_id) /* NOLINT */
{
    if (NVA_STACK_DEPTH(stack) <= stack->data_top + NVA_TYPE_SIZE(type_id)) {
        return NVA_FULL;
    }

    nva_memcpy(&stack->data[stack->data_top], value, NVA_TYPE_SIZE(type_id));
    stack->data_top += NVA_TYPE_SIZE(type_id);

    stack->type[stack->type_top] = type_id;
    ++stack->type_top;

    return NVA_SUCCESS;
}

/**
 * 从栈中弹出数据
 * @param stack 栈结构体地址
 * @param[out] value 弹出的值的地址
 * @param[out] type_id 弹出的值的类型ID
 * @return nva_StatusCode
 */
NVA_INLINE nva_StatusCode nva_stackPop(nva_Stack* stack, void* value, nva_TypeId* type_id) /* NOLINT */
{
    const nva_TypeId top_type_id = stack->type[stack->type_top - 1];

    if (stack->data_top < NVA_TYPE_SIZE(top_type_id)) {
        return NVA_EMPTY;
    }

    *type_id = top_type_id;

    stack->data_top -= NVA_TYPE_SIZE(top_type_id);
    nva_memcpy(value, &stack->data[stack->data_top], NVA_TYPE_SIZE(top_type_id));

    --stack->type_top;

    return NVA_SUCCESS;
}

NVA_EXTERN_C_END

#endif /* !NVA_STACK_CDEF_H */
