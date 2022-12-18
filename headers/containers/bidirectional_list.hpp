#pragma once

#include "container.hpp"
#include "bidirectional_iterator.hpp"

namespace ctnr
{
  template <typename T>
    class BidirectionalList : public Container<iter::BidirectionalIterator<T>>
  {
    public:
      using base_type = Container<iter::BidirectionalIterator<T>>;
      using typename Container<iter::BidirectionalIterator<T>>::iterator_type;
      using typename Container<iter::BidirectionalIterator<T>>::size_type;
      using value_type = typename iterator_type::value_type;
      using node_type = node::BidirectionalNode<value_type>;
      using P = std::array<size_type, 2>;


      BidirectionalList();
      BidirectionalList(std::initializer_list<value_type> ilist);
      BidirectionalList(const BidirectionalList &other);
      BidirectionalList(BidirectionalList &&other);
      ~BidirectionalList();

      value_type &front();
      value_type &back();

      void push_front(const value_type value);
      void push_back(const value_type value);

      void pop_front();
      void pop_back();

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
ctnr::BidirectionalList<T>::BidirectionalList() : base_type::Container()
{
}

  template <typename T>
ctnr::BidirectionalList<T>::BidirectionalList(std::initializer_list<value_type> il)
{
  for (const auto &i : il)
  {
    this->push_back(i);
  }
}

  template <typename T>
ctnr::BidirectionalList<T>::BidirectionalList(const BidirectionalList &other)
{
  for (const auto &i : other)
  {
    this->push_back(i->value);
  }
}

  template <typename T>
ctnr::BidirectionalList<T>::BidirectionalList(BidirectionalList &&other)
{
  this->clear();
  this->swap(other);
}

  template <typename T>
ctnr::BidirectionalList<T>::~BidirectionalList()
{
}

  template <typename T>
typename ctnr::BidirectionalList<T>::value_type &ctnr::BidirectionalList<T>::front()
{
  if (!this->empty())
    return *(this->_begin);
  else
    throw std::out_of_range("list is empty");
}

  template <typename T>
typename ctnr::BidirectionalList<T>::value_type &ctnr::BidirectionalList<T>::back()
{
  if (!this->empty())
    return this->_end->prev->value;
  else
    throw std::out_of_range("list is empty");
}

  template <typename T>
void ctnr::BidirectionalList<T>::push_front(const value_type value)
{
  auto first{this->_begin.operator->()};
  first->prev = new typename iterator_type::node_type{.prev = nullptr, .next = first};
  first->prev->value = value;
  --this->_begin, ++this->_size;
}

  template <typename T>
void ctnr::BidirectionalList<T>::push_back(const value_type value)
{
  auto last{this->_end.operator->()};
  last->value = value;
  last->next = new typename iterator_type::node_type{.prev = last};
  ++this->_end, ++this->_size;
}

  template <typename T>
void ctnr::BidirectionalList<T>::pop_front()
{
  if (!this->empty())
  {
    ++this->_begin, --this->_size;
    delete this->_begin->prev;
  }
  else
  {
    throw std::out_of_range("list is empty pop_front");
  }
}

  template <typename T>
void ctnr::BidirectionalList<T>::pop_back()
{
  if (!this->empty())
  {
    --this->_end, --this->_size;
    delete this->_end->next;
  }
  else
  {
    throw std::out_of_range("list is empty pop_back");
  }
}

  template <typename T>
void ctnr::BidirectionalList<T>::assing(size_type count, const value_type &value)
{
  this->clear();
  for (size_type i = 0; i < count; ++i)
  {
    this->push_front(value);
  }
}

  template <typename T>
void ctnr::BidirectionalList<T>::assing(iterator_type first, iterator_type last)
{
  for (auto temp = first; temp != last; ++temp)
  {
    temp->value = value_type();
  }
}

  template <typename T>
void ctnr::BidirectionalList<T>::resize(size_type count)
{
  if (this->size() < count)
  {
    while (this->size() < count)
    {
      this->push_back(value_type());
    }
  }
  else
  {
    while (this->size() > count)
    {
      this->pop_back();
    }
  }
}

  template <typename T>
void ctnr::BidirectionalList<T>::resize(size_type count, const value_type &value)
{
  while (count > this->size())
  {
    this->push_back(value);
  }
  while (count < this->size())
  {
    this->pop_back();
  }
}

  template <typename T>
void ctnr::BidirectionalList<T>::clear()
{
  for (size_type i = this->size(); i > 0; --i)
  {
    this->pop_front();
  }
}

  template <typename T>
typename ctnr::BidirectionalList<T>::iterator_type ctnr::BidirectionalList<T>::insert(unsigned int pos, const value_type value)
{
  if (pos > this->size())
  {
    throw std::length_error("size limit value");
  }
  else if (pos != 0)
  {
    auto temp = this->_begin;
    for (; pos > 1; --pos, ++temp) {}
    auto tmp = new typename iterator_type::node_type{.prev = temp.operator->(),
                                                     .next = temp->next};
    tmp->value = value;
    tmp->next->prev = tmp;
    temp->next = tmp;
    ++this->_size;
    return ++temp;
  }
  else
  {
    this->push_front(value);
    return this->_begin;
  }
}

  template <typename T>
typename ctnr::BidirectionalList<T>::iterator_type ctnr::BidirectionalList<T>::erase(unsigned int pos)
{
  if (pos >= this->size())
  {
    throw std::length_error("size limit value");
  }
  else if (pos != 0)
  {
    auto temp = this->_begin;
    for (; pos > 0; --pos, ++temp) {}
    node_type *prevl = temp->prev, *nextl = temp->next;
    delete temp.operator->();
    prevl->next = nextl;
    nextl->prev = prevl;
    --this->_size;
    return ++temp;
  }
  else
  {
    this->pop_front();
    return this->_begin;
  }
}

  template <typename T>
typename ctnr::BidirectionalList<T>::iterator_type ctnr::BidirectionalList<T>::at(const size_type position)
{
  iterator_type temp = this->_begin;
  for (auto i = position; i > 0 ; --i, ++temp){}
  return temp;
}

  template <typename T>
void ctnr::BidirectionalList<T>::quickSort(const size_type &li, const size_type &ri)
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
void ctnr::BidirectionalList<T>::swap(value_type &l, value_type &r)
{
  value_type x = l;
  l = r;
  r = x;
}

  template <typename T>
typename ctnr::BidirectionalList<T>::P ctnr::BidirectionalList<T>::splitting(const size_type &li, const size_type &ri)
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
