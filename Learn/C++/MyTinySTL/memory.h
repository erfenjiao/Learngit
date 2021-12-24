#ifndef MEMORY_H_
#define MEMORY_H_

// 这个头文件负责更高级的动态内存管理
// 包含一些基本函数、空间配置器、未初始化的储存空间管理，以及一个模板类 auto_ptr

#include<cstddef>
#include<cstdlib>
#include<climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"


#endif

/**
 * 一般而言，我们所习惯的 C++ 内存配置操作是这样的：
 * class Foo　{...}
 * Foo * pf = new Foo;   //配置内存，然后构造对象 
 * delete pf;            //将对象析构，然后释放内存
 * 为了精密分工，STl allocator 决定将这两阶段操作分开，
 * 配置内存：alloc::allocate() 　 构造对象：::construct()
 * 释放内存：alloc::allocate()    对象析构： ::destroy()
 * 
 * #include "uninitialized.h" 定义一些全局函数，用来填充或复制大块的内存
 */