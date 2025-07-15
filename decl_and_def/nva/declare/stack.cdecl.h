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
     : ((type_id) == NVA_TYPEID_SLLONG || (type_id) == NVA_TYPEID_ULLONG) ? sizeof(NVA_LONG_LONG)                     \
     : ((type_id) == NVA_TYPEID_PTR || (type_id) == NVA_TYPEID_STR)       ? sizeof(void*)                             \
     : ((type_id) == NVA_TYPEID_FLOAT)                                    ? sizeof(float)                             \
     : ((type_id) == NVA_TYPEID_DOUBLE)                                   ? sizeof(double)                            \
                                                                          : 0U)

/**
 * 栈结构体
 */
typedef struct nva_Stack {
    unsigned int type_top;                            /**< 类型栈顶元素的索引 */
    unsigned int data_top;                            /**< 数据栈顶元素的索引 */

    unsigned int place[NVA_STACK_DEFAULT_SIZE];       /**< 栈的每一份数据存储的位置 */
    nva_TypeId type[NVA_STACK_DEFAULT_SIZE];          /**< 栈的类型存储 */
    unsigned char data_store[NVA_STACK_DEFAULT_SIZE]; /**< 栈的数据存储 */
} nva_Stack;

/**
 * 栈的初始化值
 * @note 该宏仅用于栈的初始化
 */
#define NVA_STACK_INIT_VALUE {0}

/**
 * 栈的数据
 */
typedef union nva_StackData {
    NVA_SIZE_T generic_v;

    signed char schar_v;
    unsigned char uchar_v;

    short short_v;
    unsigned short ushort_v;

    int int_v;
    unsigned int uint_v;

    long long_v;
    unsigned long ulong_v;

    NVA_LONG_LONG llong_v;
    unsigned NVA_LONG_LONG ullong_v;

    void* ptr_v;

    char char_v;
    const char* str_v;
} nva_StackData;

/**
 * 栈数据的信息
 */
typedef struct nva_StackDataInfo {
    nva_StackData* stack_data; /**< 栈原本的数据 */
    nva_TypeId type_id;        /**< 数据的类型ID */
} nva_StackDataInfo;

/* clang-format off */

/**
 * 根据类型ID获得栈的有符号整数类型（不包含长整型与超长整形）数据
 * @param data_info 栈数据的信息（取结构体 nva_StackDataInfo 的变量）
 */
#define NVA_STACK_GET_SINTEGER(data_info)                                                             \
      (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_SINT ? (((data_info).stack_data)->int_v)     \
    : (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_SCHAR ? (((data_info).stack_data)->schar_v)  \
    : (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_SSHORT ? (((data_info).stack_data)->short_v) \
    : 0)))

/**
 * 根据类型ID获得栈的无符号整数类型（不包含长整型与超长整形）数据
 * @param data_info 栈数据的信息（取结构体 nva_StackDataInfo 的变量）
 */
#define NVA_STACK_GET_UINTEGER(data_info)                                                              \
      (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_UINT ? (((data_info).stack_data)->uint_v)     \
    : (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_UCHAR ? (((data_info).stack_data)->uchar_v)   \
    : (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_USHORT ? (((data_info).stack_data)->ushort_v) \
    : 0)))

/* clang-format on */

#if (!NVA_INLINE_MODE)
nva_ErrorCode nva_stackInit(nva_Stack* NVA_RESTRICT stack);
#endif /* (!NVA_INLINE_MODE) */

nva_ErrorCode nva_stackPush(nva_Stack* NVA_RESTRICT stack, const void* NVA_RESTRICT value, nva_TypeId type_id);
nva_ErrorCode nva_stackPeek(const nva_Stack* NVA_RESTRICT stack,
                            unsigned int i,
                            void* NVA_RESTRICT value,
                            nva_TypeId* NVA_RESTRICT type_id);
nva_ErrorCode nva_stackPop(nva_Stack* NVA_RESTRICT stack, void* NVA_RESTRICT value, nva_TypeId* NVA_RESTRICT type_id);

NVA_EXTERN_C_END

#endif /* !NVA_STACK_CDECL_H */
