#include "node.hpp"

namespace node
{
  template <typename T>
    struct ForwardNode : Node<T>
  {
    ForwardNode *next = nullptr;
  };
}
