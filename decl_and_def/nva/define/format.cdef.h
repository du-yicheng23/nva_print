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
#include "nva/string.h"

NVA_EXTERN_C_BEGIN

static nva_Stack nva_fmt_stack;

#define NVA_IS_TYPE_CHAR(ch)                                                                                  \
    ((ch) == 'a' || (ch) == 'A' || (ch) == 'b' || (ch) == 'B' || (ch) == 'c' || (ch) == 'd' || (ch) == 'e' || \
     (ch) == 'E' || (ch) == 'f' || (ch) == 'F' || (ch) == 'g' || (ch) == 'G' || (ch) == 'o' || (ch) == 'p' || \
     (ch) == 's' || (ch) == 'x' || (ch) == 'X')

nva_FmtStatus nva_int(const int value, const nva_FmtStatus status) /* NOLINT */
{
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_fmt_stack, &value, NVA_TYPEID_SINT) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
}

nva_FmtStatus nva_uint(const unsigned int uvalue, const nva_FmtStatus status) /* NOLINT */
{
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_fmt_stack, &uvalue, NVA_TYPEID_UINT) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
}

nva_FmtStatus nva_char(const char ch, const nva_FmtStatus status) /* NOLINT */
{
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_fmt_stack, &ch, NVA_TYPEID_CHAR) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
}

nva_FmtStatus nva_str(const char* const str, const nva_FmtStatus status) /* NOLINT */
{
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_fmt_stack, &str, NVA_TYPEID_STR) == NVA_SUCCESS) {
        return NVA_START;
    }

    return NVA_ERROR;
}

nva_ErrorCode nva_format(char* NVA_RESTRICT dest, /* NOLINT */
                         const char* NVA_RESTRICT format,
                         const nva_FmtStatus status)
{
    return NVA_SUCCESS;
}

static nva_ErrorCode nva_formatRecordStyle(char* NVA_RESTRICT dest, const char* const NVA_RESTRICT format)
{
    NVA_SIZE_T i;               /* for dest */
    NVA_SIZE_T j;               /* for format */

    NVA_SIZE_T formatting_head; /* 在格式化过程中的起点 */

    NVA_SIZE_T current_phase_value;

    unsigned int stack_index = 0U; /* 用到的存储在栈内的元素 id */

    unsigned int phasing_num_width;

    nva_FormatStyle style = {0};

    nva_TypeId type_id;

    NVA_BOOL in_formatting = NVA_FALSE;   /* 开始格式化其中一个{}了 */
    NVA_BOOL recording_arg_id = NVA_TRUE; /* 在格式化过程中，正在记录 arg_id */
    NVA_BOOL in_phasing = NVA_FALSE;      /* 在格式化过程中，已经扫描到 : 了，开始解析格式化选项 */

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

                /* get the value from stack */
                if (style.arg_id == -1) {
                    nva_stackPeek(&nva_fmt_stack, stack_index, &current_phase_value, &type_id);
                }
                else {
                    nva_stackPeek(&nva_fmt_stack, style.arg_id, &current_phase_value, &type_id);
                }



                in_formatting = NVA_FALSE;
                recording_arg_id = NVA_TRUE;
                in_phasing = NVA_FALSE;
                ++stack_index;
            }

            if (recording_arg_id && format[j] >= '0' && format[j] <= '9') {
                if (format[j + 1] != '}' || format[j + 1] != ':') {
                    return NVA_FORMAT_ERROR;
                }

                style.arg_id = (signed char)(format[j++] - '0');

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

                /* phase width and "0" */
                if (format[j] >= '0' && format[j] <= '9') {
                    do {
                        if (format[j] == '0') {
                            style.flag.zero = 1U;
                            ++j;

                            if (!(format[j] >= '0' && format[j] <= '9')) {
                                break;
                            }
                        }

                        style.width = (signed char)nva_atoi(format + j, &phasing_num_width);
                        j += phasing_num_width;
                    } while (0);
                }

                /* phase precision */
                if (format[j] == '.') {
                    ++j;
                    style.precision = (signed char)nva_atoi(format + j, &phasing_num_width);
                    j += phasing_num_width;
                }

                /* phase whether add number separator characters or not */
                if (format[j] == 'L') {
                    style.flag.L = 1U;
                    ++j;
                }

                /* phase type */
                if (NVA_IS_TYPE_CHAR(format[j])) {
                    style.type = format[j];
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
}

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDEF_H */
