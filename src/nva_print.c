/**
 * @file nva_print.c
 * @author DuYicheng
 * @date 2025-06-28
 * @brief 打印相关功能实现
 */

#include "nva/defines.h"
#include "nva/print.h"
#include "nva/format.h"

#ifndef NVA_PRINT_BUFFER_SIZE
#define NVA_BUFFER_SIZE 128
#endif

/**
 * 打印字符串的缓冲区
 */
static char nva__print_buffer[NVA_BUFFER_SIZE];

/**
 * 格式化并打印字符串
 * @param format 格式化字符串
 * @param status 格式化状态
 * @return nva_ErrorCode
 */
nva_ErrorCode nva_print(const char* NVA_RESTRICT format, const nva_FmtStatus status)
{
    const nva_ErrorCode ret = nva_format(nva__print_buffer, format, status);
    NVA_SIZE_T i;

    for (i = 0U; i < NVA_COUNTOF(nva__print_buffer) && nva__print_buffer[i] != '\0'; ++i) {
        if (nva_putchar(nva__print_buffer[i]) != 1) {
            return NVA_FAIL;
        }
    }

    return ret;
}
