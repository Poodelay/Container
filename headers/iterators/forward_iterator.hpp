#pragma once

#include "iterator.hpp"
#include "forward_node.hpp"

namespace iter
{
  template <typename T>
    class ForwardIterator : public Iterator<node::ForwardNode<T>>
  {
    public:
      using node_type = node::ForwardNode<T>;
      using value_type = typename node_type::value_type;
      using base_type = Iterator<node::ForwardNode<T>>;

      ForwardIterator();
      ForwardIterator(const ForwardIterator &other);
      ~ForwardIterator();

      bool operator==(const ForwardIterator &other);
      bool operator!=(const ForwardIterator &other);

      ForwardIterator operator=(const ForwardIterator &other);

      ForwardIterator &operator++();
      ForwardIterator operator++(int);

      value_type &operator*();
      node_type *operator->();
  };
}

  template <typename T>
iter::ForwardIterator<T>::ForwardIterator() : base_type::Iterator()
{
}

  template <typename T>
iter::ForwardIterator<T>::ForwardIterator(const ForwardIterator &other) : base_type::Iterator(other)
{
}

  template <typename T>
iter::ForwardIterator<T>::~ForwardIterator()
{
}

  template <typename T>
iter::ForwardIterator<T> iter::ForwardIterator<T>::operator=(const ForwardIterator &other)
{
  this->_node->next = other->_node->next;
  this->_node->value = other->_node->value;
  return this;
}

  template <typename T>
bool iter::ForwardIterator<T>::operator==(const ForwardIterator &other)
{
  if (this->_node->next == other._node->next && this->_node->value == other._node->value)
    return true;
  else
    return false;
}

  template <typename T>
bool iter::ForwardIterator<T>::operator!=(const ForwardIterator &other)
{
  if (this->_node->next == other._node->next && this->_node->value == other._node->value)
    return false;
  else
    return true;
}

  template <typename T>
iter::ForwardIterator<T> &iter::ForwardIterator<T>::operator++()
{
  if (this->_node->next != nullptr) // curr_ can't be the nullptr
  {
    this->_node = this->_node->next;
    return *this;
  }
  else
    throw std::out_of_range("iterator is empty");
}

  template <typename T>
iter::ForwardIterator<T> iter::ForwardIterator<T>::operator++(int)
{
  if (this->_node->next != nullptr) // curr_ can't be the nullptr
  {
    ForwardIterator tmp(*this);
    ++(*this);
    return tmp;
  }
  else
  {
    throw std::out_of_range("iterator is empty");
  }
}

  template <typename T>
typename iter::ForwardIterator<T>::value_type &iter::ForwardIterator<T>::operator*()
{
  if (this->_node != nullptr)
    return (*this)->value;
  else
    throw std::range_error("this node don't has value");
}

  template <typename T>
typename iter::ForwardIterator<T>::node_type *iter::ForwardIterator<T>::operator->()
{
  return this->_node;
}


