#ifndef ALGOBASE_H_
#define ALGOBASE_H_

// 这个头文件包含了 mystl 的基本算法

#include <cstring>
#include <cstdio>
#include <iostream>

#include "iterator.h"
#include "util.h"

namespace mystl
{
    #ifdef max
    #pragma message("#undefing marco max")
    #undef max
    #endif

    #ifdef min
    #pragma message("#undefing marco min")
    #undef min
    #endif

    /**
     * max
     * 返回两者中的较大值，语义相等时返回第一个
     */
    template<class T>
    const T& max(const T& lhs , const T&rhs)
    {
        return 
    }

} // namespace mystl



#endif