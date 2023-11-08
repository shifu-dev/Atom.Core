#pragma once
#include "Atom/Core.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// ArrayIter iterates over raw arr.
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    requires(not RConst<T>)
    class ArrayIter
    {
    public:
        using TElem = T;

    public:
        /// ----------------------------------------------------------------------------------------
        /// # Default Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr ArrayIter()
            : _it{ nullptr } {}

        /// ----------------------------------------------------------------------------------------
        /// # Value Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr ArrayIter(ConstMemPtr<T> it)
            : _it{ it } {}

    public:
        /// ----------------------------------------------------------------------------------------
        /// Access value by ref.
        /// ----------------------------------------------------------------------------------------
        constexpr auto value() const -> const T&
        {
            return *_it;
        }

        /// ----------------------------------------------------------------------------------------
        /// Access value by ptr.
        /// ----------------------------------------------------------------------------------------
        constexpr auto data() const -> ConstMemPtr<T>
        {
            return this->_it;
        }

        /// ----------------------------------------------------------------------------------------
        /// Check if this iter is same as `that`. Used to compare wth end.
        /// ----------------------------------------------------------------------------------------
        constexpr auto equals(const ArrayIter& that) const -> bool
        {
            return this->_it == that._it;
        }

        /// ----------------------------------------------------------------------------------------
        /// Move fwd by `steps`.
        /// ----------------------------------------------------------------------------------------
        constexpr auto next(usize steps = 1) -> ArrayIter&
        {
            _it += steps.val();
            return *this;
        }

        /// ----------------------------------------------------------------------------------------
        /// Move bwd by `steps`.
        /// ----------------------------------------------------------------------------------------
        constexpr auto prev(usize steps = 1) -> ArrayIter&
        {
            _it -= steps.val();
            return *this;
        }

        /// ----------------------------------------------------------------------------------------
        /// Compares `this` data with `that` data.
        /// ----------------------------------------------------------------------------------------
        constexpr auto compare(const ArrayIter& that) const -> isize
        {
            return this->_it - that._it;
        }

    protected:
        ConstMemPtr<T> _it;
    };

    /// --------------------------------------------------------------------------------------------
    /// MutArrayIter iterates over mut raw arr.
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    requires(not RConst<T>)
    class MutArrayIter: public ArrayIter<T>
    {
        using Base = ArrayIter<T>;

    public:
        using TElem = T;

    public:
        /// ----------------------------------------------------------------------------------------
        /// # Default Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr MutArrayIter()
            : Base{ } {}

        /// ----------------------------------------------------------------------------------------
        /// # Value Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr MutArrayIter(MemPtr<T> it)
            : Base{ it } {}

    public:
        /// ----------------------------------------------------------------------------------------
        /// Access value by mut ref.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutValue() -> T&
        {
            return const_cast<T&>(Base::value());
        }

        /// ----------------------------------------------------------------------------------------
        /// Access value by mut ptr.
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutData() -> MemPtr<T>
        {
            return const_cast<MemPtr<T>>(Base::data());
        }

        /// ----------------------------------------------------------------------------------------
        /// Move fwd by `steps`.
        /// ----------------------------------------------------------------------------------------
        constexpr auto next(usize steps = 1) -> MutArrayIter&
        {
            Base::next(steps);
            return *this;
        }

        /// ----------------------------------------------------------------------------------------
        /// Move bwd by `steps`.
        /// ----------------------------------------------------------------------------------------
        constexpr auto prev(usize steps = 1) -> MutArrayIter&
        {
            Base::prev(steps);
            return *this;
        }
    };
}
