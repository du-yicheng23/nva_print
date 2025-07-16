/**
 * @file print.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief 打印相关功能实现
 */

#ifndef NVA_PRINT_H
#define NVA_PRINT_H

#include "nva/defines.h"
#include "nva/format.h"

NVA_EXTERN_C_BEGIN

/**
 * 用户自行实现的字符打印函数
 * @param c 待打印的字符
 * @retval 1 成功打印一个字符
 * @retval 其他 打印失败
 */
int nva_putchar(char c);

nva_ErrorCode nva_print(const char* NVA_RESTRICT format, nva_FmtStatus status);

NVA_EXTERN_C_END

#endif  // !NVA_PRINT_H
