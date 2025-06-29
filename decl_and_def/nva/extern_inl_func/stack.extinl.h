/**
 * @file stack.extinl.h
 * @author DuYicheng
 * @date 2025-06-29
 * @brief 栈 extern inline 函数
 */
 
#pragma once
#ifndef NVA_STACK_EXTINL_H
#define NVA_STACK_EXTINL_H

NVA_EXTERN_INLINE NVA_CONSTEXPR nva_StatusCode nva_stackInit(nva_Stack* stack);
NVA_EXTERN_INLINE nva_StatusCode nva_stackPush(nva_Stack* stack, const void* value, nva_TypeId type_id);
NVA_EXTERN_INLINE nva_StatusCode nva_stackPop(nva_Stack* stack, void* value, nva_TypeId* type_id);

#endif /* !NVA_STACK_EXTINL_H */
