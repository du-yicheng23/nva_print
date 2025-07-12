/**
 * @file cpp_api.hpp
 * @author DuYicheng
 * @date 2025-07-12
 * @brief C++ API
 */

#pragma once
#ifndef NVA_CPP_API_HPP
#define NVA_CPP_API_HPP

namespace nva {

inline nva_ErrorCode format(char* dest, const char* format, const nva_FmtStatus status)
{
    return nva_format(dest, format, status);
}

inline nva_FmtStatus add(const int value, const nva_FmtStatus status)
{
    return nva_int(value, status);
}

inline nva_FmtStatus add(const unsigned int value, const nva_FmtStatus status)
{
    return nva_uint(value, status);
}

inline nva_FmtStatus add(const char value, const nva_FmtStatus status)
{
    return nva_char(value, status);
}

inline nva_FmtStatus ptr(const void* ptr, const nva_FmtStatus status)
{
    return nva_ptr(ptr, status);
}

inline nva_FmtStatus add(const void* value, const nva_FmtStatus status)
{
    return ptr(value, status);
}

inline nva_FmtStatus str(const char* str, const nva_FmtStatus status)
{
    return nva_str(str, status);
}

inline nva_FmtStatus add(const char* value, const nva_FmtStatus status)
{
    return str(value, status);
}

}  // namespace nva

#endif /* !NVA_CPP_API_HPP */
