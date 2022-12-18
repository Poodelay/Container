#pragma once

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <array>

namespace ctnr
{
  template <typename Iterator>
    class Container
    {
      public:
        using iterator_type = Iterator;
        using size_type = std::size_t;

        Container();
        ~Container();

        iterator_type begin() const;
        iterator_type end() const;

        size_type size() const;
        bool empty();

        void out();

        void swap(Container &other);

      protected:
        iterator_type _begin;
        iterator_type _end;
        size_type _size;
    };
}

// Container

template <typename Iterator>
ctnr::Container<Iterator>::Container() : _begin(), _end(_begin), _size{0}
{
}

template <typename Iterator>
typename ctnr::Container<Iterator>::iterator_type ctnr::Container<Iterator>::begin() const
{
  return this->_begin;
}

template <typename Iterator>
typename ctnr::Container<Iterator>::iterator_type ctnr::Container<Iterator>::end() const
{
  return this->_end;
}

template <typename Iterator>
typename ctnr::Container<Iterator>::size_type ctnr::Container<Iterator>::size() const
{
  return this->_size;
}

template <typename Iterator>
ctnr::Container<Iterator>::~Container()
{
}

  template <typename Iterator>
bool ctnr::Container<Iterator>::empty()
{
  if (this->_size == 0)
    return true;
  else
    return false;
}

  template <typename Iterator>
void ctnr::Container<Iterator>::out()
{
  size_type i = 0;
  for (auto temp = this->_begin; i < this->size(); ++i, ++temp)
  {
    std::cout << *(temp) << ' ';
  }
  std::cout << std::endl;
}

  template <typename Iterator>
void ctnr::Container<Iterator>::swap(Container &other)
{
  Container tmp = this->_begin;
  this->_begin = other->_begin;
  other->_begin = tmp;
  tmp = this->_end;
  this->_end = other->_end;
  other->_end = tmp;
  size_type tmps = this->_size;
  this->_size = other->_size;
  other->_size = tmps;
}
