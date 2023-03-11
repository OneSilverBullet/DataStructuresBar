#pragma once

#include <iostream>
#include <memory>

//����ָ�룺shared_ptr
//ʹ�����ü�����ʹ��һ�������������+1
template<typename T>
class SmartPointer
{
private:
	//ע�����Ƕ���ָ�룬Ҳ�������е�SmartPointer����ָͬ��ͬһ��T��size_t���ڴ�
	//���ڹ���T���ڴ��ָ��
	T* _ptr;
	//������
	size_t* _count;
public:
	//���ptr��Ϊnullptr��ô_count������Ϊ1
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

	//���ڿ������캯����SmartPointer����
	SmartPointer(const SmartPointer& ptr)
	{
		if (this != &ptr)
		{
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++; //ע�����_count�ڴ�++
		}
	}

	//��ֵ����
	SmartPointer& operator=(const SmartPointer& ptr)
	{
		//����ֵ�Լ���ʱ��ֱ�ӷ���
		if (this->_ptr == ptr._ptr)
		{
			return *this;
		}

		//����ǰ����ָ�벻Ϊ�գ���ô��ԭ��ָ����ڴ洦���
		if (this->_ptr)
		{
			(*this->_count)--;
			if (this->_count == 0)
			{
				delete this->_ptr;
				delete this->_count;
			}
		}

		//��ָ�����
		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++; //���Ӽ�����
		return *this;
	}

	//Smart Pointer
	T& operator*()
	{
		assert(this->_ptr == nullptr);
		return *(this->_ptr);
	}

	//��������
	~SmartPointer()
	{
		(*this->_count)--;
		if (*this->_count == 0)
		{
			delete this->_ptr;
			delete this->_count;
		}
	}

	//�������е����ø���
	size_t use_count()
	{
		return *this->_count;
	}

};