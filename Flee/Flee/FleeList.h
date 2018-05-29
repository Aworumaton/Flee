#ifndef FleeList_H
#define FleeList_H

template <class T>
class FleeList
{
public:
	FleeList() : FleeList(0) {};

	FleeList(int capacity)
	{
		_size = 0;
		if (capacity < 1)
		{
			capacity = 1;
		}
		_capacity = capacity;
		_items = new T[capacity];
	};

	~FleeList()
	{
		//delete(_items);
	};

	void Add(T item)
	{
		InsertAt(_size, item);
	};

	bool InsertAt(int index, T item)
	{
		if (index < 0 || index > _size)
		{
			return false;
		}
		
		if (_size == _capacity)
		{
			_capacity = _capacity * 2;
			T* newitems = new T[_capacity];
			for (int i = 0; i < index; i++)
			{
				newitems[i] = _items[i];
			}

			newitems[index] = item;

			for (int i = index; i < _size; i++)
			{
				newitems[i+1] = _items[i];
			}
			//delete(_items);
			_items = newitems;
		}
		else
		{
			for (int i = _size; i > index; i--)
			{
				_items[i] = _items[i - 1];
			}
			_items[index] = item;
		}

		_size++;

		return true;
	};

	bool Remove(T item)
	{
		int index = IndexOf(item);
		return RemoveAt(index);
	};

	bool RemoveAt(int index)
	{
		if (index < 0 || index >= _size)
		{
			return false;
		}


		_size--;

		for (int i = index; i < _size; i++)
		{
			_items[i] = _items[i + 1];
		}

		
		return true;
	};

	int IndexOf(T item)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_items[i] == item)
			{
				return i;
			}
		}

		return -1;
	};

	T ItemAt(int index)
	{
		if (index < 0 || index >= _size)
		{
			return T();
		}

		return _items[index];
	};

	int Size()
	{
		return _size;
	};

	void TrimExcess()
	{
		if (_capacity == _size)
		{
			return;
		}

		_capacity = _size;
		T* newitems = new T[_capacity];
		for (int i = 0; i < _size; i++)
		{
			newitems[i] = _items[i];
		}
		delete(_items);
		_items = newitems;
	};

	void Clear()
	{

	};

private:
	T * _items;
	int _size;
	int _capacity;
};



#endif

