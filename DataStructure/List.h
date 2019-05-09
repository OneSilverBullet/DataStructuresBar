#pragma once

template<typename Object>
class List
{
private:
	struct Node
	{
		Object val;
		Node* next;
		Node* prev;
		Node(const Object& x = Object(),  Node* n = nullptr,  Node* p = nullptr) :
			val(x), next(n), prev(p) {}
	};

public:
	//常量迭代器，不能够依据该迭代器进行data修改
	class const_iterator
	{
	public:
		const_iterator():current(nullptr){}

		const Object& operator*()const
		{
			return Retrive();
		}

		const_iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator olditer = *this;
			++(*this);
			return olditer;
		}

		const_iterator& operator--()
		{
			current = current->prev;
			return *this;
		}

		const_iterator operator--(int)
		{
			const_iterator olditer = *this;
			--(*this);
			return olditer;
		}

		bool operator==(const const_iterator& rhs) const
		{
			return rhs.current == current;
		}
		bool operator!=(const const_iterator& rhs) const
		{
			return !(*this==rhs);
		}

	protected:
		Node* current;

		Object& Retrive()const
		{
			return current->val;
		}

		const_iterator(Node* r):current(r){}

		friend class List<Object>;//允许iterator访问非公有成员
	};

	//迭代器三大函数：==、*、++
	class iterator : public const_iterator
	{
	public:
		iterator() {}

		 Object& operator*()
		{
			return const_iterator::Retrive();
		}

		 const Object& operator*()const
		 {
			 return const_iterator::operator*();
		 }

		 iterator& operator++()
		 {
			 const_iterator::current = const_iterator::current->next;
			 return *this;
		 }

		 iterator operator++(int)
		 {
			 iterator olditer = *this;
			 ++(*this);
			 return olditer;
		 }

		 iterator& operator--()
		 {
			 const_iterator::current = const_iterator::current->prev;
			 return *this;
		 }

		 iterator operator--(int)
		 {
			 iterator olditer = *this;
			 --(*this);
			 return olditer;
		 }

		 bool operator==(const iterator& rhs)const 
		 {
			 return (const_iterator::current == rhs.current);
		 }

		 bool operator!=(const iterator& rhs)const 
		 {
			 return !(*this == rhs);

		 }

	protected:
		iterator(Node* p):const_iterator(p){}
		friend class List<Object>;//允许List访问iterator的非公有成员
	};

	//List基础函数
	List()
	{
		init();
	}

	List(const List& rhs)
	{
		init();
		*this = rhs;
	}

	~List() 
	{
		Clear();
		delete head;
		delete tail;
	}

	const List& operator=(const List& rhs)
	{
		if (&rhs == this)return *this;
		Clear();
		for (iterator iter = rhs.Begin(); iter != rhs.End(); ++iter)
		{
			Push_back(*iter);
		}
		return *this;
	}

	//List当中配合迭代器进行的操作
	iterator Begin()
	{
		return iterator(head->next);
	}

	const_iterator Begin() const
	{
		return const_iterator(head->next);
	}

	iterator End()
	{
		return iterator(tail);
	}

	const_iterator End() const
	{
		return const_iterator(tail);
	}

	Object& Front()
	{
		return *Begin();
	}

	const Object& Front() const
	{
		return *Begin();
	}

	Object& Back()
	{
		return *(--End());
	}

	const Object& Back() const
	{
		return *(--End());
	}

	//List的基础操作的封装
	void Push_front(const Object& x)
	{
		Insert(Begin(), x);
	}

	void Push_back(const Object& x)
	{
		Insert(End(), x);
	}

	void Pop_front()
	{
		Erase(Begin());
	}

	void Pop_back()
	{
		Erase(--End());
	}

	iterator Insert(iterator iter, const Object& x)
	{
		Node* p = iter.current;
		size++;
		Node* newnode = new Node(x, p, p->prev);
		p->prev->next = newnode;
		p->prev = newnode;
		return p->prev;
	}

	iterator Erase(iterator iter)
	{
		Node* p = iter.current;
		iterator retval(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		size--;
		delete p;
		return retval;
	}

	iterator Erase(iterator start, iterator end)
	{
		for (iterator x= start; x!=end;)
		{
			x = Erase(x);
		}
		return end;
	}
	
	//List基础功能
	int Size() const
	{
		return size;
	}

	bool Empty() const
	{
		return Size() == 0 ? true : false;
	}

	void Clear()
	{
		while (!Empty())
		{
			Pop_front();
		}
	}

private:
	int size;
	Node* head;
	Node* tail;

	void init()
	{
		size = 0;
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->prev = head;
	}
};
