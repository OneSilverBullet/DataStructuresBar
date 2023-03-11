#pragma once

#include <iostream>
#include <memory>

//智能指针：shared_ptr
//使用引用计数：使用一次则计数器计数+1
template<typename T>
class SmartPointer
{
private:
	//注意他们都是指针，也就是所有的SmartPointer对象共同指向同一个T与size_t的内存
	//用于管理T的内存的指针
	T* _ptr;
	//计数器
	size_t* _count;
public:
	//如果ptr不为nullptr那么_count计数器为1
	SmartPointer(T* ptr = nullptr) :_ptr(ptr)
	{
		if (_ptr)
		{
			_count = new size_t(1);
		}
		else
		{
			_count = new size_t(0);
		}
	}

	//用于拷贝构造函数的SmartPointer函数
	SmartPointer(const SmartPointer& ptr)
	{
		if (this != &ptr)
		{
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++; //注意访问_count内存++
		}
	}

	//赋值函数
	SmartPointer& operator=(const SmartPointer& ptr)
	{
		//当赋值自己的时候直接返回
		if (this->_ptr == ptr._ptr)
		{
			return *this;
		}

		//当当前智能指针不为空，那么将原来指向的内存处理掉
		if (this->_ptr)
		{
			(*this->_count)--;
			if (this->_count == 0)
			{
				delete this->_ptr;
				delete this->_count;
			}
		}

		//将指针更新
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++; //增加计数器
		return *this;
	}

	//Smart Pointer
	T& operator*()
	{
		assert(this->_ptr == nullptr);
		return *(this->_ptr);
	}

	//析构函数
	~SmartPointer()
	{
		(*this->_count)--;
		if (*this->_count == 0)
		{
			delete this->_ptr;
			delete this->_count;
		}
	}

	//访问其中的引用个数
	size_t use_count()
	{
		return *this->_count;
	}

};