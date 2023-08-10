#pragma once
#include "Atom/Range.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    class _ArrViewStorage
    {
    public:
        using TElem = T;

    public:
        constexpr _ArrViewStorage(const T* arr, usize count)
            : _data{ arr }
            , _count{ count }
        {}

    public:
        constexpr auto getData() const -> const T*
        {
            return _data;
        }

        constexpr auto getData() -> T*
        {
            return _data;
        }

        constexpr auto setData(T* data)
        {
            _data = data;
        }

        constexpr auto getCount() const -> usize
        {
            return _count;
        }

        constexpr auto setCount(usize count)
        {
            _count = count;
        }

    protected:
        const T* _data;
        usize _count;
    };

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    class ArrView: public ArrRangeTrait<ArrView<T>>
    {
    private:
        friend class ArrRangeTraitImpl<ArrView<T>>;

    private:
        using This = ArrView;
        using _Storage = _ArrViewStorage<T>;

    public:
        using TElem = T;

    public:
        /// ----------------------------------------------------------------------------------------
        /// # Default Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr ArrView()
            : _storage(nullptr, 0)
        {}

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Copy Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr ArrView(const This& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Copy Operator
        /// ----------------------------------------------------------------------------------------
        constexpr ArrView& operator=(const This& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Move Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr ArrView(This&& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Move Operator
        /// ----------------------------------------------------------------------------------------
        constexpr ArrView& operator=(This&& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Arr Constructor
        /// ----------------------------------------------------------------------------------------
        template <usize count>
        constexpr ArrView(const T (&arr)[count])
            : _storage(arr, count)
        {}

        /// ----------------------------------------------------------------------------------------
        /// # Arr Operator
        /// ----------------------------------------------------------------------------------------
        template <usize count>
        constexpr ArrView& operator=(const T (&arr)[count])
        {
            _storage.setData(arr);
            _storage.setCount(count);
        }

        /// ----------------------------------------------------------------------------------------
        /// # Range Constructor
        /// ----------------------------------------------------------------------------------------
        template <typename TRange>
        constexpr ArrView(const TRange& range)
            requires(RArrRangeOf<TRange, T>)
            : _storage{ range.data(), range.count() }
        {}

        /// ----------------------------------------------------------------------------------------
        /// # Range Operator
        /// ----------------------------------------------------------------------------------------
        template <typename TRange>
        constexpr ArrView& operator=(const TRange& range)
            requires(RArrRangeOf<TRange, T>)
        {
            _storage.setData(range.data());
            _storage.setCount(range.count());
        }

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Destructor
        /// ----------------------------------------------------------------------------------------
        constexpr ~ArrView() = default;

    private:
        _Storage _storage;
    };

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    class ArrRangeTraitImpl<ArrView<T>>
    {
        using _Arr = ArrView<T>;
        using _Storage = _ArrViewStorage<T>;

    public:
        using TElem = T;

    public:
        constexpr auto getData() const -> const T*
        {
            return _storage().getData();
        }

        constexpr auto getCount() const -> usize
        {
            return _storage().getCount();
        }

    private:
        constexpr auto _storage() const -> const _Storage&
        {
            return reinterpret_cast<const _Arr&>(*this)._storage;
        }
    };
}
