#pragma once

namespace node
{
    template <typename T>
    struct Node
    {
        using value_type = T;
        value_type value = value_type();
    };
}
