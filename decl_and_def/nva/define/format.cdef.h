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

nva_ErrorCode nva_format_default(char* NVA_RESTRICT dest, /* NOLINT */
                                 const char* NVA_RESTRICT format,
                                 const nva_DefaultFmtStatus status)
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_FAIL;
#else
    NVA_SIZE_T i;                  /* for dest */
    NVA_SIZE_T j;                  /* for format */

    NVA_SIZE_T formatting_head;    /* 在格式化过程中的起点 */

    unsigned int stack_index = 0U; /* 用到的存储在栈内的元素 id */

    nva_FormatStyle style;

    NVA_BOOL in_formatting = NVA_FALSE;   /* 开始格式化其中一个{}了 */
    NVA_BOOL recording_arg_id = NVA_TRUE; /* 在格式化过程中，正在记录 arg_id */
    NVA_BOOL in_phasing = NVA_FALSE;      /* 在格式化过程中，已经扫描到 : 了，开始解析格式化选项 */

    if (status.status != NVA_START.status) {
        return NVA_FAIL;
    }
    if (dest == NVA_NULL || format == NVA_NULL) {
        return NVA_PARAM_ERROR;
    }

    for (i = 0U, j = 0U; format[j] != '\0'; ++j) {
        if (format[j] == '{') {
            if (in_formatting) {
                return NVA_FORMAT_ERROR;
            }

            if (format[j + 1] == '\0') {
                dest[i] = format[j];
                dest[i + 1] = format[j + 1];
                break;
            }

            if (format[j + 1] == '{') {
                dest[i++] = format[j++];
                continue;
            }

            in_formatting = NVA_TRUE;
            formatting_head = j;
            ++j;

            style = (nva_FormatStyle){.arg_id = -1,
                                      .filler = ' ',
                                      .width = -1,
                                      .precision = -1,
                                      .type = '\0',
                                      .flag = {.align = NVA_FMT_FLG_ALIGN_DEFAULT,
                                               .sign = NVA_FMT_FLG_SIGN_NEGATIVE_ONLY,
                                               .prefix = 0U,
                                               .zero = 0U,
                                               .L = 0U}};
        }

        if (in_formatting) {
            if (format[j] == '}') {
                /* formatting here... */

                in_formatting = NVA_FALSE;
                recording_arg_id = NVA_TRUE;
                in_phasing = NVA_FALSE;
                ++stack_index;
            }

            if (recording_arg_id && format[j] >= '0' && format[j] <= '9') {
                if (format[j + 1] != '}' || format[j + 1] != ':') {
                    return NVA_FORMAT_ERROR;
                }

                style.arg_id = format[j++] - '0';

                recording_arg_id = NVA_FALSE;
            }

            if (!in_phasing && format[j] == ':') {
                in_phasing = NVA_TRUE;
                ++j;
            }

            if (in_phasing) {
                /* phase align */
                switch (format[j]) {
                case '<':
                    style.flag.align = NVA_FMT_FLG_ALIGN_LEFT;
                    goto phase_filler;

                case '>':
                    style.flag.align = NVA_FMT_FLG_ALIGN_RIGHT;
                    goto phase_filler;

                case '^':
                    style.flag.align = NVA_FMT_FLG_ALIGN_CENTER;
                    goto phase_filler;

                phase_filler:
                    if (format[j - 1] != ':') {
                        style.filler = format[j];
                    }
                    else {
                        if (format[j - 2] == ':') {
                            style.filler = ':'; /* eg: "{::<}" : 用 ':' 填充 */
                        }
                    }

                    ++j;

                    break;

                default:
                    break;
                }

                /* phase sign */
                switch (format[j]) {
                case ' ':
                    style.flag.sign = NVA_FMT_FLG_SIGN_SPACE_POSITIVE;
                    goto phase_sign_end;

                case '+':
                    style.flag.sign = NVA_FMT_FLG_SIGN_EXPLICITLY_POSITIVE;
                    goto phase_sign_end;

                case '-':
                    style.flag.sign = NVA_FMT_FLG_SIGN_NEGATIVE_ONLY;
                    goto phase_sign_end;

                phase_sign_end:
                    ++j;

                    break;

                default:
                    break;
                }

                /* phase use prefix or not */
                if (format[j] == '#') {
                    style.flag.prefix = 1U;
                    ++j;
                }
            }
        }
        else {
            if (format[j] == '}' && format[j + 1] == '}') {
                dest[i++] = format[j++];
            }
            else {
                dest[i++] = format[j];
            }
        }
    }

    return NVA_SUCCESS;
#endif
}

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDEF_H */
