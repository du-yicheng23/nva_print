# nva_print

[en_US](./README.md) | zh_CN

---

NVA: None Variadic Arguments。一个类似于 [{fmt}](https://github.com/fmtlib/fmt) 的格式化字符串解析库。
但不使用可变参，适用于嵌入式系统。

## Todo
- [] 完善浮点类型的通用类型、科学计数法、十六进制的格式化支持
  - [] 科学计数法
  - [] 通用类型
  - [] 十六进制
- [] 对数值类型插入数字分隔符的格式化选项
- [] 完善英文注释与文档

## 特点

* 纯 C 语言，兼容 C89 等较旧的标准。
* 无依赖项，甚至不需要C语言标准库（但也可以通过宏配置以使用C语言标准库）。
* 支持格式化字符串解析和打印，格式化模式类似于 [{fmt}](https://github.com/fmtlib/fmt) 库。
* 不使用可变参，通过函数嵌套调用实现参数传递。
* 无动态内存分配，适用于嵌入式系统。

### 使用示例

```C
#include "nva/print.h"  // requires

nva_print("Hello, {}!\n", nva_str("World", NVA_START));
// output: "Hello, World!"

char dest[64];
nva_format(dest, "Hello, {}!\n", nva_str("World", NVA_START));
// will format in dest: "Hello, World!"

nva_print("Number: {1}, Hex: {0:x}, FloatPoint: {2:.2f}\n", nva_int(0xFF, nva_int(42, nva_float(3.14159f, NVA_START))));
// output: "Number: 42, Hex: ff, FloatPoint: 3.14\n"
```

对于 C11 及以上版本，可以使用宏 nva_add 以自动推导参数类型：
```C
#include "nva/print.h"  // requires

nva_print("Number: {1}, Hex: {0:x}, FloatPoint: {2:.2f}\n", nva_add(0xFF, nva_add(42, nva_add(3.14159f, NVA_START))));
// output: "Number: 42, Hex: ff, FloatPoint: 3.14\n"
```

对于 C++，可以使用 C++ API：
```C++
#include "nva/print.h"  // requires

nva::print("Number: {1}, Hex: {0:x}, FloatPoint: {2:.2f}\n", nva::add(0xFF, nva::add(42, nva::add(3.14159f, NVA_START))));
// output: "Number: 42, Hex: ff, FloatPoint: 3.14\n"

char dest[64];
nva::format(dest, "Hello, {}!\n", nva::add("World", NVA_START));
// will format in dest: "Hello, World!"
```

### 不支持的特性

* 不支持设置格式化类型为 '?'。
* 不支持范围格式规格。
* 暂时不支持格式化时间类型。
* 暂时不支持自定义类型的格式化。

## 构建

使用 `git clone` 或 `git submodule add`（推荐）将本仓库克隆到您的项目中，
然后根据您的构建系统添加 `nva_print` 目录。

### 使用 CMake 构建：

```CMake
cmake_minimum_required(VERSION 3.27)

add_subdirectory(
    # path to nva_print
)

target_link_libraries(
    # your_target_name
    # PUBLIC / PRIVATE / INTERFACE
    nva_print
)
```

### 其他构建系统：

将 `nva_print` 下的路径 `src` 中的所有源文件添加到您的项目中，
将 `inc` 和 `decl_and_def` 目录添加到头文件搜索路径中即可。

## 配置并使用

您还需要自行实现一个 `nva_putchar` 函数，例如：
```C
#include <stdio.h>
int nva_putchar(char c)
{
    putchar(c);  // print a char to stdout
}
```

对于嵌入式系统，您可以通过实现这个函数来将字符输出到串口或其他设备，例如：
```C
#include "your_serial.h"
int nva_putchar(char c)
{
    serial_write(c);  // transmit a char to your serial device
}
```

### 预定义宏

可以通过预定义宏来设置某些特性。

| 前置条件                     | 预定义宏                     | 预定义这个宏之后的效果                                        |
|--------------------------|--------------------------|----------------------------------------------------|
| 无                        | `NVA_NO_STDDEF_H`        | 禁用 `stddef.h` 的包含                                  |
| 预定义了 `NVA_NO_STDDEF_H` 宏 | `NVA_SIZE_T`             | 指定 `size_t` 的类型                                    |
| 无                        | `NVA_NO_STDBOOL_H`       | 禁用 `stdbool.h` 的包含                                 |
| 无                        | `NVA_NO_LONG_LONG_TYPE`  | 当前平台不支持 `long long` 类型，将被替换成 `long`                |
| 无                        | `NVA_NO_RESTRICT`        | 不支持 `restrict` 关键字，将被禁用                            |
| 无                        | `NVA_USE_INLINE`         | 启用内联函数的支持                                          |
| 无                        | `NVA_NO_STRING_H`        | 禁用 `string.h` 的包含                                  |
| 无                        | `NVA_NO_INF_AND_NAN`     | 禁用 `inf` 和 `nan` 的支持，并且将把 `-0.0` 当作 `+0.0`         |
| 无                        | `NVA_STACK_DEFAULT_SIZE` | 指定栈的大小（以字节为单位），默认为 `32`。栈的大小取决于你能传递多大的参数           |
| 无                        | `NVA_PRINT_BUFFER_SIZE`  | 指定打印缓冲区的大小（以字节为单位），默认为 `128`。**如果缓冲区不够大，可能导致程序崩溃** |
| 无                        | `NVA_ADD_USER_OPTIONS`   | 增加用户自定义配置的头文件，详见下一节                                |

#### NVA_ADD_USER_OPTIONS 宏

当您预定义了宏 `NVA_ADD_USER_OPTIONS` 后，您需要新建一个名称为 `nva_user_options.h` 的头文件，
然后将这个头文件所在的路径添加到头文件搜索路径中。

CMake 配置示例：
```CMake
# in your CMakeLists.txt

add_subdirectory(
    # path to nva_print
)
target_compile_definitions(nva_print INTERFACE -DNVA_ADD_USER_OPTIONS)
target_include_directories(nva_print INTERFACE
    # path to your nva_user_options.h file
)

target_link_libraries(
    # your_target_name
    # PUBLIC / PRIVATE / INTERFACE
    nva_print
)
```

## 测试

本仓库不包含测试代码。测试代码在仓库 [nva_print_test](https://github.com/du-yicheng23/nva_print_test) 中。

## 贡献

由于本仓库不包含测试代码，直接在这个仓库内进行修改不便于构建。请参考
[nva_print_test](https://github.com/du-yicheng23/nva_print_test) 中的贡献指南。

## 许可证

[MIT LICENSE](./LICENSE)
