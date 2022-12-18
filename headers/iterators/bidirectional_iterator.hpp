#pragma once

#include "iterator.hpp"
#include "bidirectional_node.hpp"

namespace iter
{
  template <typename T>
    class BidirectionalIterator : public Iterator<node::BidirectionalNode<T>>
  {
    public:
      using node_type = node::BidirectionalNode<T>;
      using value_type = typename node_type::value_type;
      using base_type = Iterator<node::BidirectionalNode<T>>;

      BidirectionalIterator();
      BidirectionalIterator(const BidirectionalIterator &other);
      ~BidirectionalIterator();


      bool operator==(const BidirectionalIterator &other);
      bool operator!=(const BidirectionalIterator &other);

      BidirectionalIterator operator=(const BidirectionalIterator &other);

      BidirectionalIterator &operator++();
      BidirectionalIterator operator++(int);

      BidirectionalIterator &operator--();
      BidirectionalIterator operator--(int);

      value_type &operator*();
      node_type *operator->();
  };
}

  template <typename T>
iter::BidirectionalIterator<T>::BidirectionalIterator() : base_type::Iterator()
{
}

  template <typename T>
iter::BidirectionalIterator<T>::BidirectionalIterator(const BidirectionalIterator &other) : base_type::Iterator(other)
{
}

  template <typename T>
iter::BidirectionalIterator<T>::~BidirectionalIterator()
{
}

  template <typename T>
iter::BidirectionalIterator<T> iter::BidirectionalIterator<T>::operator=(const BidirectionalIterator &other)
{
  this->_node->next = other._node->next;
  this->_node->prev = other._node->prev;
  this->_node->value = other._node->value;
  return *this;
}

  template <typename T>
bool iter::BidirectionalIterator<T>::operator==(const BidirectionalIterator &other)
{
  if (this->_node->prev == other._node->prev && this->_node->next == other._node->next)
    return true;
  else
    return false;
}

  template <typename T>
bool iter::BidirectionalIterator<T>::operator!=(const BidirectionalIterator &other)
{
  if (this->_node == other._node)
    return false;
  else
    return true;
}

  template <typename T>
iter::BidirectionalIterator<T> &iter::BidirectionalIterator<T>::operator++()
{
  if (this->_node->next != nullptr) // curr_ can't be the nullptr
  {
    this->_node = this->_node->next;
    return *this;
  }
  else
  {
    throw std::out_of_range("iterator is empty");
  }
}

  template <typename T>
iter::BidirectionalIterator<T> iter::BidirectionalIterator<T>::operator++(int)
{
  if (this->_node->next != nullptr) // curr_ can't be the nullptr
  {
    BidirectionalIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  else
  {
    throw std::out_of_range("iterator is empty");
  }
}

  template <typename T>
iter::BidirectionalIterator<T> &iter::BidirectionalIterator<T>::operator--()
{
  if (this->_node->prev != nullptr) // curr_ can't be the nullptr
  {
    this->_node = this->_node->prev;
    return *this;
  }
  else
  {
    throw std::out_of_range("iterator is empty");
  }
}

  template <typename T>
iter::BidirectionalIterator<T> iter::BidirectionalIterator<T>::operator--(int)
{

  if (this->_node->prev != nullptr) // curr_ can't be the nullptr
  {
    BidirectionalIterator tmp(*this);
    --(*this);
    return tmp;
  }
  else
  {
    throw std::out_of_range("iterator is empty");
  }
}

  template <typename T>
typename iter::BidirectionalIterator<T>::value_type &iter::BidirectionalIterator<T>::operator*()
{
  if (this->_node != nullptr)
    return (*this)->value;
  else
    throw std::range_error("this node don't has value");
}

  template <typename T>
typename iter::BidirectionalIterator<T>::node_type *iter::BidirectionalIterator<T>::operator->()
{
  return this->_node;
}
