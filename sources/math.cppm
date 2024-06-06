export module atom.core:math;

import std;

export namespace atom::math
{
    template <typename num_type>
    constexpr auto min() -> num_type
    {
        return std::numeric_limits<num_type>::min();
    }

    template <typename num_type>
    constexpr auto max() -> num_type
    {
        return std::numeric_limits<num_type>::max();
    }

    template <typename num_type>
    constexpr auto abs(num_type num) -> num_type
    {
        return std::abs(num);
    }

    template <typename num_type>
    constexpr auto clamp(num_type num, num_type low, num_type high) -> num_type
    {
        return std::clamp(num, low, high);
    }

    template <typename num_type>
    constexpr auto min_of(num_type num0, num_type num1) -> num_type
    {
        return num0 < num1 ? num0 : num1;
    }

    template <typename num_type>
    constexpr auto max_of(num_type num0, num_type num1) -> num_type
    {
        return num0 > num1 ? num0 : num1;
    }
}
