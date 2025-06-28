/**
 * @file string.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief nva 字符串相关
 */
 
#pragma once
#ifndef NVA_STRING_H
#define NVA_STRING_H

#include "nva/defines.h"

#if (NVA_INLINE_MODE)

#include "nva/define/string.cdef.h"

#else

#include "nva/declare/string.cdecl.h"

#endif

#endif // !NVA_STRING_H
