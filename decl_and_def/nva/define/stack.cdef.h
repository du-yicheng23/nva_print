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
#include "nva/declare/stack.cdecl.h"
#include "nva/string.h"

NVA_EXTERN_C_BEGIN

/**
 * 获取栈的深度
 * @param stack 栈的地址
 * @return 栈的深度
 */
#define NVA_STACK_DEPTH(stack) (NVA_COUNTOF((stack)->data_store))

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

/**
 * 向栈推送数据
 * @param stack 栈结构体地址
 * @param value 推送的值的地址
 * @param type_id 推送的值的类型ID
 * @return nva_ErrorCode
 */
NVA_STATIC_INLINE nva_ErrorCode nva_stackPush(nva_Stack* NVA_RESTRICT stack, /* NOLINT */
                                              const void* NVA_RESTRICT value,
                                              const nva_TypeId type_id)
{
    if (NVA_STACK_DEPTH(stack) <= stack->data_top + NVA_TYPE_SIZE(type_id)) {
        return NVA_FULL;
    }

    nva_memcpy(&stack->data_store[stack->data_top], value, NVA_TYPE_SIZE(type_id));
    stack->place[stack->type_top] = stack->data_top;
    stack->data_top += NVA_TYPE_SIZE(type_id);

    stack->type[stack->type_top] = type_id;
    ++stack->type_top;

    return NVA_SUCCESS;
}

/**
 * 查看栈内数据（不退栈）
 * @param stack 栈结构体地址
 * @param i 从栈顶到栈底的第几个元素
 * @param[out] value 值的地址
 * @param[out] type_id 类型ID
 * @return nva_ErrorCode
 */
NVA_STATIC_INLINE nva_ErrorCode nva_stackPeek(const nva_Stack* NVA_RESTRICT stack, /* NOLINT */
                                              const NVA_SIZE_T i,
                                              void* NVA_RESTRICT value,
                                              nva_TypeId* NVA_RESTRICT type_id)
{
    if (stack->type_top - 1 < i) {
        return NVA_EMPTY;
    }

    *type_id = stack->type[stack->type_top - 1 - i];

    nva_memcpy(value, &stack->data_store[stack->place[stack->type_top - 1 - i]], NVA_TYPE_SIZE(*type_id));

    return NVA_SUCCESS;
}

/**
 * 从栈中弹出数据
 * @param stack 栈结构体地址
 * @param[out] value 弹出的值的地址
 * @param[out] type_id 弹出的值的类型ID
 * @return nva_ErrorCode
 */
NVA_STATIC_INLINE nva_ErrorCode nva_stackPop(nva_Stack* NVA_RESTRICT stack, /* NOLINT */
                                             void* NVA_RESTRICT value,
                                             nva_TypeId* NVA_RESTRICT type_id)
{
    const nva_TypeId top_type_id = stack->type[stack->type_top - 1];

    if (stack->data_top < NVA_TYPE_SIZE(top_type_id)) {
        return NVA_EMPTY;
    }

    *type_id = top_type_id;

    stack->data_top -= NVA_TYPE_SIZE(top_type_id);
    nva_memcpy(value, &stack->data_store[stack->data_top], NVA_TYPE_SIZE(top_type_id));

    --stack->type_top;

    return NVA_SUCCESS;
}

NVA_EXTERN_C_END

#endif /* !NVA_STACK_CDEF_H */
