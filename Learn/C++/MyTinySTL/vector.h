#ifndef VECTOR_H_
#define VECTOR_H_

// 这个头文件包含一个模板类 vector
// vector : 向量

#include<initializer_list>

#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "exceptdef.h"

namespace mystl
{
    #ifdef max
    #pragma message("#undefing marco max")
    #undef max
    #endif // max

    #ifdef min
    #pragma message("#undefing marco min")
    #undef min
    #endif // min

    /*
        vector
    */
   template<class T>
   class vector
   {
       static_assert(!std::is_same<bool, T>::value, "vector<bool> is abandoned in mystl");
       public:
            typedef mystl::allocator<T>   allocator_type;
            typedef mystl::allocator<T>   data_allocator;

            typedef typename allocator_type::value           value_type;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;

            typedef value_type*         iterator;
            typedef const value_type*   const_iterator;
            typedef mystl::reverse_iterator<iterator>   reverse_iterator;
            typedef mystl::reverse_iterator<const_iterator>   const_reverse_iterator;
            allocator_type get_allocator
            {
                return data_allocator;
            }

        private:
            iterator g;
            iterator begin_;
            iterator end_;
            iterator cap_;
        public:
            // 构造、复制、移动、析构函数
            vector() noexcept
            {
                try_init();
            }

            explicit vector(size_type n)
            {
                fill_init(n , value_type());
            }

            vector(size_type n , const value_type& value)
            {
                fill_init(n , value);
            }

            template <class Iter, typename std::enable_if<
            mystl::is_input_iterator<Iter>::value, int>::type = 0>
            vector(Iter first , Iter last)
            {
                MYSTL_DEBUG(!(last < first));
                range_init(first , last);
            }

            vector(const vector& rhs)
            {
                range_init(rhs.begin_ , rhs.end_);
            }

            vector(vector& rhs )noexcept:
            begin_(rhs.begin_) , end_(rhs.end_) , cap_(rhs.cap_)
            {
                rhs.begin_ = nullptr;
                rhs.end_ = nullptr;
                rhs.cap_ = nullptr;
            }
            vector(std::initializer_list<value_type> ilist)
            {
                range_init(ilist.begin(), ilist.end());
            }

            vector& operator=(const vector& rhs);
            vector& operator=(vector& rhs) noexcept;

            vector& operator=(std::initializer_list<value_type> ilist)
            {
                vector tmp(ilist.begin , ilist.end);
                swap(tmp);
                return *this;
            }

            ~vector()
            { 
                destroy_and_recover(begin_, end_, cap_ - begin_);
                begin_ = end_ = cap_ = nullptr;
            } 

            public:

            // 迭代器相关操作
            iterator               begin()         noexcept 
            { 
                return begin_; 
            }
            const_iterator         begin()   const noexcept
            { 
                return begin_; 
            }
            iterator               end()           noexcept
            { 
                return end_; 
            }
            const_iterator         end()     const noexcept 
            { 
                return end_; 
            }

            reverse_iterator       rbegin()        noexcept 
            { 
                return reverse_iterator(end()); 
            }
            const_reverse_iterator rbegin()  const noexcept
            { 
                return const_reverse_iterator(end()); 
            }
            reverse_iterator       rend()          noexcept
            { 
                return reverse_iterator(begin()); 
            }
            const_reverse_iterator rend()    const noexcept 
            { 
                return const_reverse_iterator(begin()); 
            }

            const_iterator         cbegin()  const noexcept 
            { 
                return begin(); 
            }
            const_iterator         cend()    const noexcept
            { 
                return end(); 
            }
            const_reverse_iterator crbegin() const noexcept
            { 
                return rbegin(); 
            }
            const_reverse_iterator crend()   const noexcept
            { 
                return rend(); 
            }

            // 容量相关操作
            bool    empty()     const noexcept
            {
                return begin_ == end_;
            }

            size_type size()    const noexcept
            {
                return static_cast<value_type>(end_ - begin_);
            }

            size_type max_size() const noexcept
            { 
                return static_cast<size_type>(-1) / sizeof(T); 
            }
            size_type capacity() const noexcept
            { 
                return static_cast<size_type>(cap_ - begin_); 
            }
            void      reserve(size_type n);
            void      shrink_to_fit();

            // 访问元素相关操作
            reference operator[] (size_type n)
            {
                MYSTL_DEBUG(n < size());
                return *(begin_ + n);               
            }
            const reference operator[](size_type n) const
            {
                MYSTL_DEBUG(n < size());
                return *(begin_ + n);
            }
            reference at(size_type n)
            {
                THROW_OUT_OF_RANGE_IF(!(n < size()) , "vector<T>::at() subscript out of range");
                return (*this)[n];
            }
            const_reference at(size_type n) const
            {
                THROW_OUT_OF_RANGE_IF(!(n < size()) , "vector<T>::at() subscript out of range");
                return (*this)[n];
            }
            reference front()
            {
                MYSTL_DEBUG(!empty());
                return *begin_;
            }
            const_reference front() const
            {
                MYSTL_DEBUG(!empty());
                return *begin_;
            }
            reference back()
            {
                MYSTL_DEBUG(!empty());
                return *(end_ - 1);
            }
            const_reference back() const
            {
                MYSTL_DEBUG(!empty());
                return *(end_ - 1);
            }
            pointer data()  noexcept
            {
                return begin_;
            }
            const_pointer data() noexcept
            {
                return begin_;
            }

            // 修改容器相关操作 assgin
            void assgin(size_type n , const value_type & value)
            {
                fill_assgin(n , value);
            }
            template <class Iter , typename std::enable_if
            <mystl::is_input_iterator<Iter>::value , int>::type = 0>
            void assgin(Iter first , Iter last)
            {
                MYSTL_DEBUG(!(last < first));
                copy_assgin(first , last , iterator_category(first));
            }
            void assgin(std::initializer_list<value_type> il)
            {
                copy_assgin(il.begin() , il.end() , mystl::forward_iterator_tag{});
            }

            // emplace / emplace_back
            template <class... Args>
            iterator emplace(const_iterator pos , Args&& ...args);

            template<class... Args>
            void emplace_back(Args&& ...args);

            // push_back / pop_back
            void push_back(const value_type& value);
            void push_back(const value_type&& value)
            {
                emplace_back(mystl::move(value));
            }

            void pop_back();

            //insert
            iterator insert(const_iterator pos , const value_type& value);
            iterator insert(const_iterator pos , value_type&& value)
            {
                return emplace(pos , mytsl::move(value));
            }

            iterator insert(const_iterator pos , size_type n , const value_type& value)
            {
                MYSTL_DEBUG(pos >= begin() && pos <= end());
                return fill_insert(const_cast<iterator>(pos) ,  n , value);
            }

            template<class Iter , typename std::enable_if<
                mystl::is_input_iterator<Iter>::value , int>::type = 0>
            void insert(const_iterator pos , Iter first , Iter last)
            {
                MYTSTL_DEBUG((pos >= begin() && pos <= end()) && !(last < first));
                copy_insert(const_cast<iterator>(pos) , first , last);
            }

            // erase / clear
            iterator erase(const_iterator pos);
            iterator erase(const_iterator first , const_iterator last);
            void clear()
            {
                erase(begin() , end());
            }

            // resize / reverse
            void resize(size_type new_size)
            {
                return resize(new_size , value_type);
            }
            void resize(size_type new_size , const value_type& value);
            
            void reverse()
            {
                mystl::reverse(begin() , end());
            }

            // swap
            void swap(vector& rhs) noexcept;

        private:
        // helper functions

        // initialize / destroy
            void try_init() noexcept;

            void init_space(size_type size , size_type cap);

            void fill_init(size_type n , const value_type& value);

            template<class Iter>
            void range_init(Iter first , Iter last);

            void destroy_and_recover(iterator first , iterator last , size_type n);

            // calculate the growth size
            size_type get_new_cap(size_type add_size);

            //assgin
            void fill_assgin(size_type n , const value_type& value);

            template<class IIter>
            void copy_assgin(IIter first , IIter last , input_iterator_tag);

            template<class FIter>
            void copy_assgin(FIter first , FIter last , forward_iterator_tag);

            //reallocate
            template<class.. Args>
            void reallocate_emplace(iterator pos , Args&&... args);
            void reallocate_insert(iterator pos , const value_type& value);

            //insert
            iterator fill_insert(iterator pos , size_type n , value_type& value);

            template<class IIter>
            vois copy_insert(iterator pos , IIter first , IIter last);

            //shrin_to_fit
            void reinsert(size_type size);
   }; //class vector

   //----------------------------------------------------------------------------
   //复制赋值操作符
   template<class T>
   vector<T>& vector<T>::operator=(const vector& rhs)
   {
       if(this != &rhs)
       {
           const auto len = rhs.size();
           if(len > capacity())
           {
               swap(tmp);
           }
           else if(size() >= len)
           {
               auto i = mystl::copy(rhs.begin() , rhs.end() , begin());
               data_allocator::destroy(i , end_);
               end_ = begin_ + len;
           }
           else
           {
                mystl::copy(rhs.begin(), rhs.begin() + size(), begin_);
                mystl::uninitialized_copy(rhs.begin() + size(), rhs.end(), end_);
                cap_ = end_ = begin_ + len;
           }
       }
   }


}



#endif