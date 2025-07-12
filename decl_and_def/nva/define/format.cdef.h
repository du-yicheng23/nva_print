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

/**
 * 栈的数据
 */
typedef union nva_StackData {
    NVA_SIZE_T generic_v;

    int int_v;
    unsigned int uint_v;

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

static nva_Stack nva_fmt_stack; /* declare */

/* clang-format off */

/**
 * 根据类型ID获得栈的整数类型数据
 * @param data_info 栈数据的信息（取结构体 nva_StackDataInfo 的变量）
 */
#define NVA_STACK_GET_INTEGER(data_info)                                                                \
           (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_SINT ? (((data_info).stack_data)->int_v)  \
         : (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_UINT ? (((data_info).stack_data)->uint_v) \
         : (((nva_TypeId)((data_info).type_id)) == NVA_TYPEID_CHAR ? (((data_info).stack_data)->char_v) \
         : 0)))

/* clang-format on */

/**
 * 判断一个字符是否表示 types
 * @param ch 待判断的字符
 */
#define NVA_IS_TYPE_CHAR(ch)                                                                                  \
    ((ch) == 'a' || (ch) == 'A' || (ch) == 'b' || (ch) == 'B' || (ch) == 'c' || (ch) == 'd' || (ch) == 'e' || \
     (ch) == 'E' || (ch) == 'f' || (ch) == 'F' || (ch) == 'g' || (ch) == 'G' || (ch) == 'o' || (ch) == 'p' || \
     (ch) == 's' || (ch) == 'x' || (ch) == 'X')

static nva_ErrorCode nva_formatProcess(char* NVA_RESTRICT dest, const char* NVA_RESTRICT format);
static nva_ErrorCode nva_processInteger(char* NVA_RESTRICT dest,
                                        nva_FormatStyle* NVA_RESTRICT style,
                                        const nva_StackDataInfo* NVA_RESTRICT data_info,
                                        unsigned int* width_of_process);

/**
 * @defgroup nva_ParamFunctions
 * @brief 用于“传参”的函数
 * @{
 */

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

nva_FmtStatus nva_ptr(const void* ptr, const nva_FmtStatus status) /* NOLINT */
{
    if (status.status != NVA_START.status) {
        return NVA_ERROR;
    }

    if (nva_stackPush(&nva_fmt_stack, &ptr, NVA_TYPEID_PTR) == NVA_SUCCESS) {
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

/**
 * @}
 */

/**
 * 格式化
 * @param dest 承接格式化字符串的内存
 * @param format 格式化字符串
 * @param status 格式化状态
 * @return nva_ErrorCode
 */
nva_ErrorCode nva_format(char* NVA_RESTRICT dest, /* NOLINT */
                         const char* NVA_RESTRICT format,
                         const nva_FmtStatus status)
{
    nva_ErrorCode error_code;

    if (dest == NVA_NULL || format == NVA_NULL) {
        return NVA_PARAM_ERROR;
    }

    if (status.status != NVA_START.status) {
        return NVA_FAIL;
    }

    error_code = nva_formatProcess(dest, format);

    nva_fmt_stack.data_top = 0U;
    nva_fmt_stack.type_top = 0U;

    return error_code;
}

static nva_ErrorCode nva_processInteger(char* const NVA_RESTRICT dest,
                                        nva_FormatStyle* const NVA_RESTRICT style,
                                        const nva_StackDataInfo* const NVA_RESTRICT data_info,
                                        unsigned int* width_of_process)
{
    unsigned char i = 0U;
    unsigned int width_of_num;
    nva_NumToStringAttr num_to_string_attr = {.base = 10, .upper_case = NVA_FALSE};

    if (style->flag.align == NVA_FMT_FLG_ALIGN_DEFAULT) {
        style->flag.align = NVA_FMT_FLG_ALIGN_RIGHT;
    }

    if (style->type == '\0') {
        style->type = 'd';
    }

    switch (style->type) {
    case 'b':
    case 'B':
        num_to_string_attr.base = 2;
        break;

    case 'd':
        break;

    case 'o':
        num_to_string_attr.base = 8;
        break;

    case 'x':
    case 'X':
        num_to_string_attr.base = 16;
        break;

    default:
        break;
    }

    if (style->type >= 'A' && style->type <= 'Z') {
        num_to_string_attr.upper_case = NVA_TRUE;
    }

    if (style->flag.prefix) {
        switch (style->type) {
        case 'b':
            nva_strcat(dest, "0b");
            goto end_of_style_check;
        case 'B':
            nva_strcat(dest, "0B");
            goto end_of_style_check;

        case 'x':
            nva_strcat(dest, "0x");
            goto end_of_style_check;
        case 'X':
            nva_strcat(dest, "0X");
            goto end_of_style_check;

        end_of_style_check:
            i += 2;
            break;

        default:
            break;
        }
    }

    if (data_info->type_id == NVA_TYPEID_CHAR || style->type == 'c') {
        dest[i] = data_info->stack_data->char_v;
        width_of_num = 1U;
    }
    else if (NVA_IS_SIGNED(data_info->type_id)) {
        nva_itoa(NVA_STACK_GET_INTEGER(*data_info), dest + i, &num_to_string_attr, &width_of_num);
    }
    else {
        nva_uitoa(NVA_STACK_GET_INTEGER(*data_info), dest + i, &num_to_string_attr, &width_of_num);
    }
    i += width_of_num;

    switch (style->flag.align) {
    case NVA_FMT_FLG_ALIGN_LEFT:
        for (; i < style->width; ++i) {
            dest[i] = style->filler;
        }
        break;

    default:
        break;
    }

    *width_of_process = i;

    return NVA_SUCCESS;
}

static nva_ErrorCode nva_formatProcess(char* const NVA_RESTRICT dest, const char* const NVA_RESTRICT format)
{
    NVA_SIZE_T i; /* for dest */
    NVA_SIZE_T j; /* for format */

    nva_StackData current_phase_value;
    nva_StackDataInfo current_phase_data_info;

    unsigned int stack_index = 0U; /* 用到的存储在栈内的元素 id */

    unsigned int phasing_num_width;

    nva_FormatStyle style = {0};

    nva_TypeId type_id;

    nva_ErrorCode error_code;

    NVA_BOOL in_formatting = NVA_FALSE;   /* 开始格式化其中一个{}了 */
    NVA_BOOL recording_arg_id = NVA_TRUE; /* 在格式化过程中，正在记录 arg_id */
    NVA_BOOL in_phasing = NVA_FALSE;      /* 在格式化过程中，已经扫描到 : 了，开始解析格式化选项 */
    NVA_BOOL have_phased;

    for (i = 0U, j = 0U; format[j] != '\0';) {
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
                ++j;
                continue;
            }

            in_formatting = NVA_TRUE;
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
                    error_code = nva_stackPeek(&nva_fmt_stack, stack_index, &current_phase_value.generic_v, &type_id);
                }
                else {
                    error_code = nva_stackPeek(&nva_fmt_stack, style.arg_id, &current_phase_value.generic_v, &type_id);
                }

                if (error_code != NVA_SUCCESS) {
                    return NVA_FAIL;
                }

                current_phase_data_info = (nva_StackDataInfo){.stack_data = &current_phase_value, .type_id = type_id};

                switch (type_id) {
                case NVA_TYPEID_SCHAR:
                case NVA_TYPEID_UCHAR:
                case NVA_TYPEID_SSHORT:
                case NVA_TYPEID_USHORT:
                case NVA_TYPEID_SINT:
                case NVA_TYPEID_UINT:
                    error_code = nva_processInteger(dest + i, &style, &current_phase_data_info, &phasing_num_width);
                    break;

                case NVA_TYPEID_PTR:
                    break;

                case NVA_TYPEID_CHAR:
                    break;

                case NVA_TYPEID_STR:
                    break;

                default:
                    break;
                }
                i += phasing_num_width;

                if (error_code != NVA_SUCCESS) {
                    return NVA_FAIL;
                }

                in_formatting = NVA_FALSE;
                recording_arg_id = NVA_TRUE;
                in_phasing = NVA_FALSE;
                ++stack_index;

                ++j;
                continue;
            }

            if (recording_arg_id && format[j] >= '0' && format[j] <= '9') {
                if (format[j + 1] != '}' && format[j + 1] != ':') {
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
                have_phased = NVA_FALSE;

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
                        style.filler = format[j - 1];
                    }
                    else {
                        if (format[j - 2] == ':') {
                            style.filler = ':'; /* eg: "{::<}" : 用 ':' 填充 */
                        }
                    }

                    ++j;
                    have_phased = NVA_TRUE;

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
                    have_phased = NVA_TRUE;

                    break;

                default:
                    break;
                }

                /* phase use prefix or not */
                if (format[j] == '#') {
                    style.flag.prefix = 1U;
                    ++j;
                    have_phased = NVA_TRUE;
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
                    have_phased = NVA_TRUE;
                }

                /* phase precision */
                if (format[j] == '.') {
                    ++j;
                    style.precision = (signed char)nva_atoi(format + j, &phasing_num_width);
                    j += phasing_num_width;
                    have_phased = NVA_TRUE;
                }

                /* phase whether add number separator characters or not */
                if (format[j] == 'L') {
                    style.flag.L = 1U;
                    ++j;
                    have_phased = NVA_TRUE;
                }

                /* phase type */
                if (NVA_IS_TYPE_CHAR(format[j])) {
                    style.type = format[j++];
                    have_phased = NVA_TRUE;
                }

                if (!have_phased) {
                    ++j;
                }
            }
        }
        else {
            if (format[j] == '}' && format[j + 1] == '}') {
                dest[i++] = format[j++];
                ++j;
            }
            else {
                dest[i++] = format[j++];
            }
        }
    }

    dest[i] = '\0';

    return NVA_SUCCESS;
}

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDEF_H */
