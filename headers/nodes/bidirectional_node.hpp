#include "node.hpp"

namespace node
{
  template <typename T>
    struct BidirectionalNode : Node<T>
  {
    BidirectionalNode *prev = nullptr;
    BidirectionalNode *next = nullptr;
  };
}
