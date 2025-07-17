/**
 * @file string.cdecl.h
 * @author DuYicheng
 * @date 2025-06-28
 * @brief nva 字符串相关声明头文件
 */

#ifndef NVA_STRING_CDECL_H
#define NVA_STRING_CDECL_H

#include "nva/defines.h"

NVA_EXTERN_C_BEGIN

/**
 * 数字转字符串的属性
 */
typedef struct nva_NumToStringAttr {
    unsigned char base;  /**< 基数 */
    NVA_BOOL upper_case; /**< 是否为大写 */
} nva_NumToStringAttr;

/**
 * 浮点转字符串的类型
 */
enum nva_FloatPointToStrType {
    NVA_FP_TO_STR_TYPE_F = 0U, /**< 定点数 */
    NVA_FP_TO_STR_TYPE_G,      /**< 常规 */
    NVA_FP_TO_STR_TYPE_E,      /**< 科学计数法 */
    NVA_FP_TO_STR_TYPE_A       /**< 十六进制 */
};

/**
 * 浮点转字符串的属性
 */
typedef struct nva_FloatPointToStrAttr {
    unsigned char base;      /**< 基数 */
    unsigned char precision; /**< 小数点后保留的位数或有效数字位数（与flag.type 的取值有关） */

    /**
     * 转化属性标志
     */
    struct nva_FpToStrFlag {
        unsigned char keep_decimal_point : 1; /**< 保留小数点 */
        unsigned char upper_case : 1;         /**< 是否为大写 */
        unsigned char type : 2;               /**< 类型 */
    } flag;
} nva_FloatPointToStrAttr;

extern const char nva_itoa_str_table[17];
extern const char nva_itoa_str_table_upper[17];

#if (!NVA_INLINE_MODE)

NVA_SIZE_T nva_strlen(const char* str);
char* nva_strcat(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src);
char* nva_strcpy(char* NVA_RESTRICT dest, const char* NVA_RESTRICT src);
int nva_strcmp(const char* lhs, const char* rhs);

#endif /* (!NVA_INLINE_MODE) */

#if (!(NVA__USE_STD_STRING && NVA_INLINE_MODE))

void* nva_memcpy(void* NVA_RESTRICT dest, const void* NVA_RESTRICT src, NVA_SIZE_T n);
void* nva_memmove(void* dest, const void* src, NVA_SIZE_T n);

#endif /* (!(NVA__USE_STD_STRING && NVA_INLINE_MODE)) */

int nva_atoi(const char* NVA_RESTRICT str, unsigned int* width_of_num);

char* nva_itoa(int value,
               char* NVA_RESTRICT str,
               const nva_NumToStringAttr* NVA_RESTRICT attr,
               unsigned int* width_of_num);
char* nva_uitoa(unsigned int uvalue,
                char* NVA_RESTRICT str,
                const nva_NumToStringAttr* NVA_RESTRICT attr,
                unsigned int* width_of_num);

char* nva_ltoa(long value,
               char* NVA_RESTRICT str,
               const nva_NumToStringAttr* NVA_RESTRICT attr,
               unsigned int* width_of_num);
char* nva_ultoa(unsigned long uvalue,
                char* NVA_RESTRICT str,
                const nva_NumToStringAttr* NVA_RESTRICT attr,
                unsigned int* width_of_num);

char* nva_lltoa(NVA_LONG_LONG value,
                char* NVA_RESTRICT str,
                const nva_NumToStringAttr* NVA_RESTRICT attr,
                unsigned int* width_of_num);
char* nva_ulltoa(unsigned NVA_LONG_LONG uvalue,
                 char* NVA_RESTRICT str,
                 const nva_NumToStringAttr* NVA_RESTRICT attr,
                 unsigned int* width_of_num);

char* nva_sizetoa(NVA_SIZE_T uvalue,
                  char* NVA_RESTRICT str,
                  const nva_NumToStringAttr* NVA_RESTRICT attr,
                  unsigned int* width_of_num);

unsigned int nva_fptoa(double value, char* NVA_RESTRICT dest, const nva_FloatPointToStrAttr* NVA_RESTRICT attr);

NVA_EXTERN_C_END

#endif  // !NVA_STRING_CDECL_H
