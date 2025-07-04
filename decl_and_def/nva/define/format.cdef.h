/**
 * @file format.cdef.h
 * @author DuYicheng
 * @date 2025-07-04
 * @brief 格式化字符串 定义
 */

#pragma once
#ifndef NVA_FORMAT_CDEF_H
#define NVA_FORMAT_CDEF_H

#include "nva/defines.h"
#include "nva/declare/format.cdecl.h"
#include "nva/stack.h"

NVA_EXTERN_C_BEGIN

static char nva_default_fmt_buffer[NVA_DEFAULT_FMT_BUFFER_SIZE];
static nva_Stack nva_default_fmt_stack;

nva_DefaultFmtStatus nva_int_default(const int value, const nva_DefaultFmtStatus status) /* NOLINT */
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_ERROR;
#else
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_default_fmt_stack, &value, NVA_TYPEID_SINT) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
#endif
}

nva_DefaultFmtStatus nva_uint_default(const unsigned int uvalue, const nva_DefaultFmtStatus status) /* NOLINT */
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_ERROR;
#else
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_default_fmt_stack, &uvalue, NVA_TYPEID_UINT) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
#endif
}

nva_DefaultFmtStatus nva_char_default(const char ch, const nva_DefaultFmtStatus status) /* NOLINT */
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_ERROR;
#else
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_default_fmt_stack, &ch, NVA_TYPEID_CHAR) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
#endif
}

nva_DefaultFmtStatus nva_str_default(const char* const str, const nva_DefaultFmtStatus status) /* NOLINT */
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_ERROR;
#else
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_default_fmt_stack, &str, NVA_TYPEID_STR) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
#endif
}

nva_ErrorCode nva_format_default(char* NVA_RESTRICT dest, const char* NVA_RESTRICT format, const nva_DefaultFmtStatus status)
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_FAIL;
#else
    if (status.status != NVA_START.status) {
        return NVA_FAIL;
    }
    if (dest == NVA_NULL || format == NVA_NULL) {
        return NVA_PARAM_ERROR;
    }
#endif
}

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDEF_H */
