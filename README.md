# JSON-Parser

一个 C++ 编写的简易的 JSON 解析器  
融入了 C++ 继承、多态、异常等机制，利用智能指针管理 JSON 对象

对外接口：  
>`parser()`：解析 JSON 文本返回管理对象的智能指针  
>`minify()`：压缩 JSON 文本，去除内部空白格  
>`operator <<()`：重载输出符便于 JSON 对象输出  

类结构：  
>CppJSON ：抽象基类  
>>CppJSON_Error ：异常处理类  
>>CppJSON_NULL ：null 类型  
>>CppJSON_Bool ：true 和 false 类型  
>>CppJSON_Number ：数字类型  
>>CppJSON_String ：字符串类型  
>>CppJSON_Array ：数组类型  
>>CppJSON_Object ：对象类型  

类对象支持操作：  
>`set_value()`：修改 JSON 对象内的各种值  
>`push_back()`：在对象类型或数组类型尾部插入新元素  
>`insert()`：在数组类型指定位置插入新元素  
>`split()`：分离对象类型或数组类型内的指定元素  
>`operator []()`：支持对象类型通过关键词访问元素，数组类型通过位置访问元素  

使用说明：直接将文件夹 CppJSON 下的 CppJSON.h 和 CppJSON.cpp 文件复制到程序文件夹下并 `#include "CppJSON.h"` 即可。
