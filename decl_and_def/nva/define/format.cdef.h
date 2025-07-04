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

NVA_EXTERN_C_BEGIN

nva_DefaultFmtStatus nva_int_default(int value, nva_DefaultFmtStatus status) /* NOLINT */
{
#if (NVA_DEFAULT_FMT_BUFFER_SIZE == 0)
    return NVA_ERROR;
#else

    return NVA_START;
#endif
}

NVA_EXTERN_C_END

#endif /* !NVA_FORMAT_CDEF_H */
