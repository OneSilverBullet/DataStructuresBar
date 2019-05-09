#pragma once

template<typename Object>
class Vector
{
public:
	enum {
		SPARSE_CAPACITY = 16
	};

	explicit Vector(int initsize = 0):size(initsize), capacity(initsize+SPARSE_CAPACITY){
		obj = new Object[capacity];
	}

	Vector(const Vector<Object>& rhs):obj(nullptr)
	{
		operator=(rhs);
	}

	Vector<Object>& operator=(const Vector<Object>& rhs)
	{
		if (&rhs != this)
		{
			delete[] obj;
			size = rhs.Size();
			capacity = rhs.Capacity();

			obj = new Object[capacity];
			for (int i = 0; i < Size(); ++i)
			{
				obj[i] = rhs.obj[i];
			}
		}
		return *this;
	}

	//vector�Ķ�̬�����ڴ�ԭ��˫��ԭ�ڴ�+1
	void Resize(int NewSize)
	{
		if (capacity <= NewSize)
		{
			Reserve(2 * NewSize + 1);
		}
		size = NewSize;
	}

	void Reserve(int NewCapacity)
	{
		if (NewCapacity < Size())
		{
			return;
		}

		Object* oldObj = obj;
		obj = new Object[NewCapacity];

		for (int i = 0; i < Size(); ++i)
		{
			obj[i] = oldObj[i];
		}
		capacity = NewCapacity;

		delete[] oldObj;
	}

	Object& operator[](int i)
	{
		return obj[i];
	}
	const Object& operator[](int i) const 
	{
		return obj[i];
	}

	int Capacity() const
	{
		return capacity;
	}

	int Size()const
	{
		return size;
	}

	bool Empty()const
	{
		return Size() == 0 ? true : false;
	}

	void Push_back(const Object& x)
	{
		if (size == capacity)
		{
			Reserve(size * 2 + 1);
		}
		obj[size++] = x;
	}

	void Pop_Back()
	{
		size--;
	}

	const Object& Back() const
	{
		return obj[size-1];
	}

	//ע���������ʹ�ã��䷵�ص������ã�
	typedef Object* iterator;
	typedef const Object* const_iterator;

	iterator Begin()
	{
		return &obj[0];
	}
	const_iterator Begin()const
	{
		return &obj[0];
	}
	iterator End()
	{
		return &obj[size];
	}
	const_iterator End()const 
	{
		return &obj[size];
	}

private:
	Object* obj;//������vector����һ����̬���飬�似��������һ������
	int size;
	int capacity;

};


