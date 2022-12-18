#pragma once

#include "node.hpp"

#include <stdexcept> // std::range_error, std::out_of_range

namespace iter
{
  template <typename Node>
    class Iterator
    {
      public:
        using node_type = Node;
        using value_type = typename node_type::value_type;

        Iterator();
        Iterator(const Iterator &other);
        ~Iterator();

      protected:
        node_type *_node;
    };
}

template <typename T>
iter::Iterator<T>::Iterator() : _node{new node_type{}}
{
}

  template <typename T>
iter::Iterator<T>::Iterator(const Iterator &other) : _node(other._node)
{
}

  template <typename T>
iter::Iterator<T>::~Iterator()
{
}
