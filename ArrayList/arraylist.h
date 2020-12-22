#pragma once
#include <iostream>

using namespace std;

template <class T>
class TArrayListIterator;

template <class T>
class TArrayList
{
protected:
  T* data; // массив данных
  int* links; // массив ссылок
  int size;
  int count;
  int root;
public:
  TArrayList(int _size = 1); // конструктор по умолчанию
  TArrayList(const TArrayList<T>& _v); // конструктор копирования
  ~TArrayList();

  TArrayList<T>& operator =(const TArrayList<T>& _v); // оператор сравнения

  void InsFirst(T d); // запись элемента в стек
  void InsLast(T d);
  void Ins(TArrayListIterator<T>& e, T d);
  
  TArrayListIterator<T> begin();
  TArrayListIterator<T> end();
  
  void DelFirst();
  void DelLast();
  void Del(TArrayListIterator<T>& e);

  T GetFirst();
  T GetLast();

  bool IsFull() const;
  bool IsEmpty() const;
  int GetCount(); // количество элементов

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TArrayList<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TArrayList<T1> &A);

  template <class T1>
  friend class TArrayListIterator;
};

template <class T>
class TArrayListIterator // позволяет перемещаться по списку
{
protected:
  TArrayList<T>& list; // ссылка на список
  int index; // индекс, с помощью которого мы перемещается по списку
public:
  TArrayListIterator(TArrayList<T>& _list, int _index = -2);
  TArrayListIterator(TArrayListIterator<T>& _v);
  ~TArrayListIterator();

  bool IsGoNext(); // проверка индекса на неотрицательность
  void GoNext(); // передвижение итератора на следующую позицию

  T& operator * (int); // возвращение ссылки на данные
  T& operator * ();

  bool operator == (const TArrayListIterator<T>& _v);
  bool operator != (const TArrayListIterator<T>& _v);
  TArrayListIterator<T>& operator ++(); // возвращает себя после изменения (в отличие от GoNext)
  TArrayListIterator<T>& operator =(const TArrayListIterator<T>& _v);

  T GetData();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TArrayList<T1> &A)
{
  int end = A.root; // индекс как корень списка А
  while (A.links[end] != (-1)) // пока мы не дошли до конца списка
  {
    ostr << A.data[end]; // печатаем данные
    end = A.links[end]; // переход в следующую ячейку
  }
  ostr << A.data[end]; // последний не выводит, так как дальше элементов нет(-1)

  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TArrayList<T1> &A)
{
  int count;
  istr >> count;
  for (int i = 0; i < count; i++)
  {
    T1 d;
    istr >> d;
    A.InsLast(d);
  }
  return istr;
}

template<class T>
TArrayList<T>::TArrayList(int _size)
{
  if (_size <= 0)
    throw - 1;
  size = _size;

  data = new T[size];
  links = new int[size];
  count = 0;

  for (int i = 0; i < size; i++)
  {
    links[i] = -2; // значение по умолчанию (отличное от нуля)
  }

  root = -1; // изначально список пуст
}

template <class T>
TArrayList<T>::TArrayList(const TArrayList<T>& _v)
{
  count = _v.count;
  size = _v.size;
  root = _v.root;
  data = new T[size];
  links = new int[size];
  count = 0;

  for (int i = 0; i < size; i++)
  {
    links[i] = _v.links[i];// коретное значение, отличное от нуля
    data[i] = _v.data[i];
  }
}

template <class T>
TArrayList<T>::~TArrayList()
{
  if (data != nullptr)
  {
    delete[] data;
    delete[] links;
    data = nullptr;
    links = nullptr;
    count = 0;
    size = 0;
    root = -1;
  }
}

template <class T>
TArrayList<T>& TArrayList<T>::operator =(const TArrayList<T>& _v)
{
  if (this == &_v)
    return *this;

  if (size == _v.size)
  {
    delete[] data;
    delete[] links;

    data = new T[_v.size];
    links = new int[_v.size];
  }

  count = _v.count;
  size = _v.size;
  root = _v.root;

  for (int i = 0; i < size; i++)
  {
    links = _v.links[i];
    data[i] = _v.data[i];
  }

}

template<class T>
void TArrayList<T>::InsFirst(T d)
{
  if (this->IsFull())
    throw - 1;

  int i = 0; 
  for (i = 0; i < size; i++) // находим свободную ячейку, в которую можно что-то вставить
  {
    if (links[i] == -2)
      break;
  }

  data[i] = d; // добавили в свободную ячейку данные
  links[i] = root; // подставили индекс корня
  root = i; // переписали корень

  count++;
}

template<class T>
void TArrayList<T>::InsLast(T d)
{
  if (this->IsFull())
    throw - 1;

  if (this->IsEmpty())
  {
    root = 0;
    data[0] = d;
    links[0] = -1;
  }
  else
  {
    int i = 0;
    for (i = 0; i < size; i++) // находим свободную ячейку, в которую можно что-то вставить
    {
      if (links[i] == -2)
        break;
    }

    int end = root;
    while (links[end] != -1) //links[end] - значние. links[links[end]] - следующий элемент(аналогично GetNext)
      end = links[end];

    data[i] = d;
    links[i] = -1;
    links[end] = i;
  }
  count++;
}

template<class T>
void TArrayList<T>::Ins(TArrayListIterator<T>& e, T d)
{
}

template<class T>
TArrayListIterator<T> TArrayList<T>::begin()
{
  return TArrayListIterator<T>(*this, this->root);
}

template<class T>
TArrayListIterator<T> TArrayList<T>::end()
{
  return TArrayListIterator<T>(*this, -1);
}


template<class T>
void TArrayList<T>::DelFirst()
{
  if (this->IsEmpty())
    throw - 1;
  int i = root;
  root = links[root]; // корень - элемент за корнем
  links[i] = -2; // бывший корень

  count--;
}

template<class T>
void TArrayList<T>::DelLast()
{
  if (this->IsEmpty())
    throw - 1;

  if (links[root] == -1)
  {
    links[root] = -2;
    root = -1; // никуда не указывает
  }
  else // больше 1-го элемента
  {
    int pEnd = root;
    int end = links[root];

    while (links[end] != -1)
    {
      pEnd = end;
      end = links[end];
    }
    links[pEnd] = -1;
    links[end] = -2;
    
  }
 
  count--;
}

template<class T>
inline void TArrayList<T>::Del(TArrayListIterator<T>& e)
{
}

template<class T>
inline T TArrayList<T>::GetFirst()
{
  if (this->IsEmpty())
    throw - 1;
  return data[root];
}

template<class T>
inline T TArrayList<T>::GetLast()
{
  if (this->IsEmpty())
    throw - 1;

  int end = root;
  while (links[end] != -1)
    end = links[end];

  return data[end];
}

template<class T>
bool TArrayList<T>::IsFull() const
{
  return count >= size;
}

template<class T>
bool TArrayList<T>::IsEmpty() const
{
  return count == 0;
}

template<class T>
int TArrayList<T>::GetCount()
{
  return count;
}

template<class T>
TArrayListIterator<T>::TArrayListIterator(TArrayList<T>& _list, int _index) : list(_list)
{
  this->index = _index;
}

template<class T>
TArrayListIterator<T>::TArrayListIterator(TArrayListIterator<T>& _v) : list(_v.list), index(_v.index)
{

}

template<class T>
TArrayListIterator<T>::~TArrayListIterator()
{
  index = -2;
}

template<class T>
bool TArrayListIterator<T>::IsGoNext() 
{
  return (index >= 0);
}

template<class T>
void TArrayListIterator<T>::GoNext()
{
  if (IsGoNext())
    index = list.links[index]; // переходим к следующему элементу нашего списка
}

template<class T>
T& TArrayListIterator<T>::operator*(int)
{
  return list.data[index];
}

template<class T>
T& TArrayListIterator<T>::operator*()
{
  return list.data[index];
}

template<class T>
bool TArrayListIterator<T>::operator==(const TArrayListIterator<T>& _v)
{
  return (index == _v.index);
}

template<class T>
 bool TArrayListIterator<T>::operator!=(const TArrayListIterator<T>& _v)
{
   return !this->operator==(_v);
}

template<class T>
TArrayListIterator<T>& TArrayListIterator<T>::operator++()
{
  this->GoNext();
  return *this;
}

template<class T>
TArrayListIterator<T>& TArrayListIterator<T>::operator=(const TArrayListIterator<T>& _v)
{
  list = _v.list;
  index = _v.index;
}

template<class T>
T TArrayListIterator<T>::GetData()
{
  if (index < 0)
    throw - 1;
  return list.data[index];
}
