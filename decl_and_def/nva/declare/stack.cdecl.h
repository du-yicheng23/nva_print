/**
 * @file stack.cdecl.h
 * @author DuYicheng
 * @date 2025-06-29
 * @brief 栈 声明
 */

#pragma once
#ifndef NVA_STACK_CDECL_H
#define NVA_STACK_CDECL_H

#include "nva/defines.h"

NVA_EXTERN_C_BEGIN

#ifndef NVA_STACK_DEFAULT_SIZE
#define NVA_STACK_DEFAULT_SIZE 40
#endif

/**
 * 基本类型ID
 */
enum nva_TypeId_ {
    NVA_TYPEID_CHAR = 0x01,       /**< 字符类型 */
    NVA_TYPEID_SCHAR = 0x11,      /**< 有符号字符类型 */
    NVA_TYPEID_UCHAR = 0x21,      /**< 无符号字符类型 */

    NVA_TYPEID_SSHORT = 0x12,     /**< 有符号短整型 */
    NVA_TYPEID_USHORT = 0x22,     /**< 无符号短整型 */

    NVA_TYPEID_SINT = 0x13,       /**< 有符号整型 */
    NVA_TYPEID_UINT = 0x23,       /**< 无符号整型 */

    NVA_TYPEID_SLONG = 0x14,      /**< 有符号长整型 */
    NVA_TYPEID_ULONG = 0x24,      /**< 无符号长整型 */

    NVA_TYPEID_SLLONG = 0x15,     /**< 有符号长长整型 */
    NVA_TYPEID_ULLONG = 0x25,     /**< 无符号长长整型 */

    NVA_TYPEID_PTR = 0x26,        /**< 指针类型 */

    NVA_TYPEID_FLOAT = 0x17,      /**< 浮点类型 */
    NVA_TYPEID_DOUBLE = 0x18,     /**< 双精度浮点类型 */

    NVA_TYPEID_STR = 0x36         /**< 字符串类型 */
};
typedef unsigned char nva_TypeId; /**< 类型ID类型 */

/**
 * 是否为有符号类型
 * @param type_id 类型ID
 */
#define NVA_IS_SIGNED(type_id) \
    (((nva_TypeId)(type_id)) != NVA_TYPEID_CHAR && ((((nva_TypeId)(type_id)) & 0xF0) == 0x10))

/**
 * 是否为无符号类型
 * @param type_id 类型ID
 */
#define NVA_IS_UNSIGNED(type_id) \
    (((nva_TypeId)(type_id)) != NVA_TYPEID_CHAR && ((((nva_TypeId)(type_id)) & 0xF0) == 0x20))

/**
 * 根据类型ID获取类型的大小
 * @param type_id 类型ID
 */
#define NVA_TYPE_SIZE(type_id)                                                                                        \
    (((type_id) == NVA_TYPEID_CHAR || (type_id) == NVA_TYPEID_SCHAR || (type_id) == NVA_TYPEID_UCHAR) ? sizeof(char)  \
     : ((type_id) == NVA_TYPEID_SSHORT || (type_id) == NVA_TYPEID_USHORT)                             ? sizeof(short) \
     : ((type_id) == NVA_TYPEID_SINT || (type_id) == NVA_TYPEID_UINT)                                 ? sizeof(int)   \
     : ((type_id) == NVA_TYPEID_SLONG || (type_id) == NVA_TYPEID_ULONG)                               ? sizeof(long)  \
     : ((type_id) == NVA_TYPEID_SLLONG || (type_id) == NVA_TYPEID_ULLONG) ? sizeof(long long)                         \
     : ((type_id) == NVA_TYPEID_PTR || (type_id) == NVA_TYPEID_STR)       ? sizeof(void*)                             \
     : ((type_id) == NVA_TYPEID_FLOAT)                                    ? sizeof(float)                             \
     : ((type_id) == NVA_TYPEID_DOUBLE)                                   ? sizeof(double)                            \
                                                                          : 0U)

/**
 * 栈结构体
 */
typedef struct nva_Stack {
    NVA_SIZE_T type_top;                        /**< 类型栈顶元素的索引 */
    NVA_SIZE_T data_top;                        /**< 数据栈顶元素的索引 */

    nva_TypeId type[NVA_STACK_DEFAULT_SIZE];    /**< 栈的类型存储 */
    unsigned char data[NVA_STACK_DEFAULT_SIZE]; /**< 栈的数据存储 */
} nva_Stack;

/**
 * 栈的初始化值
 * @note 该宏仅用于栈的初始化
 */
#define NVA_STACK_INIT_VALUE {0}

#if (!NVA_INLINE_MODE)
#include "nva/extern_inl_func/stack.extinl.h"
#endif

NVA_EXTERN_C_END

#endif /* !NVA_STACK_CDECL_H */
