#pragma once
#include "Atom/Range.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    template <typename TElem_>
    class BasicArrayView
    {
        using This = BasicArrayView;

    public:
        using TElem = TElem_;
        using TIter = ArrayIter<TElem>;
        using TIterEnd = TIter;
        using TMutIter = MutArrayIter<TElem>;
        using TMutIterEnd = TMutIter;

    public:
        /// ----------------------------------------------------------------------------------------
        /// # Default Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr BasicArrayView():
            _data{ nullptr }, _count{ 0 }
        {}

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Copy Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr BasicArrayView(const This& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Copy Operator
        /// ----------------------------------------------------------------------------------------
        constexpr BasicArrayView& operator=(const This& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Move Constructor
        /// ----------------------------------------------------------------------------------------
        constexpr BasicArrayView(This&& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Move Operator
        /// ----------------------------------------------------------------------------------------
        constexpr BasicArrayView& operator=(This&& that) = default;

        /// ----------------------------------------------------------------------------------------
        /// # Array Constructor
        /// ----------------------------------------------------------------------------------------
        template <usize count>
        constexpr BasicArrayView(const TElem (&arr)[count]):
            _data{ arr }, _count{ count }
        {}

        /// ----------------------------------------------------------------------------------------
        /// # Array Operator
        /// ----------------------------------------------------------------------------------------
        template <usize count>
        constexpr BasicArrayView& operator=(const TElem (&arr)[count])
        {
            _data = arr;
            _count = count;
        }

        /// ----------------------------------------------------------------------------------------
        /// # Range Constructor
        /// ----------------------------------------------------------------------------------------
        template <typename TRange>
        constexpr BasicArrayView(const TRange& range)
            requires(RArrayRangeOf<TRange, TElem>)
            :
            _data{ range.data() }, _count{ range.count() }
        {}

        /// ----------------------------------------------------------------------------------------
        /// # Range Operator
        /// ----------------------------------------------------------------------------------------
        template <typename TRange>
        constexpr BasicArrayView& operator=(const TRange& range)
            requires(RArrayRangeOf<TRange, TElem>)
        {
            _data = range.data();
            _count = range.count();
        }

        /// ----------------------------------------------------------------------------------------
        /// # Trivial Destructor
        /// ----------------------------------------------------------------------------------------
        constexpr ~BasicArrayView() = default;

    public:
        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto data() const -> const TElem*
        {
            return _data;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutData() -> TElem*
        {
            return _data;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto count() const -> usize
        {
            return _count;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto iter() const -> TIter
        {
            return TIter(_data);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto iterEnd() const -> TIterEnd
        {
            return TIterEnd(_data + _count);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutIter() -> TMutIter
        {
            return TMutIter(_data);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        constexpr auto mutIterEnd() -> TMutIterEnd
        {
            return TMutIterEnd(_data + _count);
        }

    private:
        const TElem* _data;
        usize _count;
    };

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    template <typename TElem>
    class ArrayView: public ArrayRangeExtensions<BasicArrayView<TElem>>
    {
        using Base = ArrayRangeExtensions<BasicArrayView<TElem>>;

    public:
        using Base::Base;
        using Base::operator=;
    };
}
