#pragma once

#include "container.hpp"
#include "forward_iterator.hpp"
#include <stdexcept>

namespace ctnr
{
  template <typename T>
    class ForwardList : public Container<iter::ForwardIterator<T>>
  {
    public:
      using base_type = Container<iter::ForwardIterator<T>>;
      using typename Container<iter::ForwardIterator<T>>::iterator_type;
      using typename Container<iter::ForwardIterator<T>>::size_type;
      using value_type = typename iterator_type::value_type;
      using node_type = node::ForwardNode<value_type>;
      using P = std::array<size_type, 2>;

      ForwardList();
      ~ForwardList();

      value_type &front();

      void push_front(value_type value);

      void pop_front();

      void assing(size_type count, const value_type &value);
      void assing(iterator_type first, iterator_type last);

      void resize(size_type count, const value_type &value);
      void resize(size_type count);

      iterator_type insert(unsigned int position, const value_type value_type);
      iterator_type erase(unsigned int position);

      void quickSort(const size_type &li, const size_type &ri);
      P splitting(const size_type &li, const size_type &ri);
      iterator_type at(size_type pos);
      void swap(value_type &l, value_type &r);

      void clear();
  };
}

  template <typename T>
ctnr::ForwardList<T>::ForwardList() : base_type::Container()
{
}

  template <typename T>
ctnr::ForwardList<T>::~ForwardList()
{
}

  template <typename T>
typename ctnr::ForwardList<T>::value_type &ctnr::ForwardList<T>::front()
{
  if (!this->empty())
    return *(this->_begin);
  else
    throw std::out_of_range("list is empty");
}

  template <typename T>
void ctnr::ForwardList<T>::push_front(const value_type value)
{
  auto temp = new typename iterator_type::node_type{.next = this->_begin->next};
  temp->value = *(this->_begin);
  *(this->_begin) = value;
  this->_begin->next = temp;
  ++this->_size;
}

  template <typename T>
void ctnr::ForwardList<T>::pop_front()
{
  if (!this->empty())
  {
    auto temp = this->_begin;
    ++this->_begin;
    delete temp.operator->();
    --this->_size;
  }
  else
  {
    throw std::out_of_range("list is empty");
  }
}

  template <typename T>
void ctnr::ForwardList<T>::assing(size_type count, const value_type &value)
{
  this->clear();
  for (unsigned int i = 0; i < count; ++i)
  {
    this->push_front(value);
  }
}

  template <typename T>
void ctnr::ForwardList<T>::assing(iterator_type first, iterator_type last)
{
  for (iterator_type temp = first; temp != last; ++temp)
  {
    temp->value = value_type();
  }
}

  template <typename T>
void ctnr::ForwardList<T>::resize(size_type count)
{
  while (count > this->size())
  {
    this->push_front(value_type());
  }
  while (count < this->size())
  {
    this->pop_front();
  }
}

  template <typename T>
void ctnr::ForwardList<T>::resize(size_type count, const value_type &value)
{
  while (count > this->size())
  {
    this->push_front(value);
  }
  while (count < this->size())
  {
    this->pop_front();
  }
}

  template <typename T>
void ctnr::ForwardList<T>::clear()
{
  for (size_type i = this->size(); i > 0; --i)
  {
    this->pop_front();
  }
}

  template <typename T>
typename ctnr::ForwardList<T>::iterator_type ctnr::ForwardList<T>::insert(unsigned int pos, const value_type value)
{
  if (pos <= this->size() && pos != 0)
  {
    auto temp = this->_begin;
    for (; pos > 1; --pos, ++temp) {}
    auto tmp = new typename iterator_type::node_type{.next = temp->next};
    tmp->value = value;
    temp->next = tmp;
    ++this->_size, ++temp;
    return temp;
  }
  else if (pos == 0)
  {
    this->push_front(value);
    return this->_begin;
  }
  else
  {
    throw std::length_error("List limit value");
  }
}

  template <typename T>
typename ctnr::ForwardList<T>::iterator_type ctnr::ForwardList<T>::erase(unsigned int pos)
{
  if (pos < this->size() && pos != 0)
  {
    auto temp = this->_begin;
    for (; pos > 1; --pos, ++temp) {}
    if (temp->next->next != nullptr)
    {
      node_type *die = temp->next;
      auto nextl = temp->next->next;
      delete die;
      temp->next = nextl;
      --this->_size, ++temp;
      return temp;
    }
    else
    {
      node_type *die = temp->next;
      delete die;
      temp->next = nullptr;
      --this->_size;
      return this->_end;
    }
  }
  else if (pos == 0)
  {
    this->pop_front();
    return this->_begin;
  }
  else
  {
    throw std::length_error("list limit value");
  }
}

  template <typename T>
typename ctnr::ForwardList<T>::iterator_type ctnr::ForwardList<T>::at(const size_type position)
{
  iterator_type temp = this->_begin;
  for (auto i = position; i > 0 ; --i, ++temp){}
  return temp;
}

  template <typename T>
void ctnr::ForwardList<T>::quickSort(const size_type &li, const size_type &ri)
{
  if (li < ri)
  {
    const P bi = this->splitting(li, ri);
    //const size_type lb = bi[0], rb = bi[0];
    this->quickSort(li, bi[0]);
    this->quickSort(bi[1], ri);
  }
}

  template <typename T>
void ctnr::ForwardList<T>::swap(value_type &l, value_type &r)
{
  value_type x = l;
  l = r;
  r = x;
}

  template <typename T>
typename ctnr::ForwardList<T>::P ctnr::ForwardList<T>::splitting(const size_type &li, const size_type &ri)
{
  const size_type pi = (li + ri) / 2;
  const value_type pv = this->at(pi)->value;
  this->swap(this->at(pi)->value, this->at(ri)->value);
  size_type i = li, j = ri - 1, p = li, q = j;
  while(true)
  {
    while (i <= j && this->at(i)->value <= pv)
    {
      if (this->at(i)->value == pv)
      {
        this->swap(this->at(i)->value, this->at(p++)->value);
      }
      ++i;
    }
    while (j > li && this->at(j)->value >= pv)
    {
      if (this->at(j)->value == pv)
      {
        this->swap(this->at(j)->value, this->at(q--)->value);
      }
      --j;
    }
    if (i < j)
    {
      this->swap(this->at(i)->value, this->at(j)->value);
    }
    else
    {
      for (size_type k = li; k < p && j >= p; k++, j--)
      {
        this->swap(this->at(k)->value, this->at(j)->value);
      }
      for (size_type k = ri; k > q && i <= q; k--, i++)
      {
        this->swap(this->at(k)->value, this->at(i)->value);
      }
    }
    return {j, i};
  }
}
