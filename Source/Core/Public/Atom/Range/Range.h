#pragma once
#include "RangeReq.h"
#include "ArrIter.h"
#include "InitList.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <typename... TArgs>
    class Range;

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <typename _TIter, typename _TIterEnd>
    requires(RIterPair<_TIter, _TIterEnd>)
    class Range<_TIter, _TIterEnd>
    {
    public:
        using TElem = typename _TIter::TElem;
        using TMutIter = _TIter;
        using TMutIterEnd = _TIterEnd;
        using TIter = _TIter;
        using TIterEnd = _TIterEnd;

    public:
        constexpr ctor Range(TIter iter, TIterEnd end):
            _iter{ iter }, _end{ end } { }

    public:
        constexpr fn iter() const -> TIter
            requires(RIterPair<TIter, TIterEnd>)
        {
            return TIter{ _iter };
        }

        constexpr fn iterEnd() const -> TIterEnd
            requires(RIterPair<TIter, TIterEnd>)
        {
            return TIterEnd{ _end };
        }

        constexpr fn mutIter() -> TMutIter
            requires(RMutIterPair<TMutIter, TMutIterEnd>)
        {
            return _iter;
        }

        constexpr fn mutIterEnd() -> TMutIterEnd
            requires(RMutIterPair<TMutIter, TMutIterEnd>)
        {
            return _end;
        }

        constexpr fn count() const -> usize
            requires(RJumpIterPair<TIter, TIterEnd>)
        {
            return _end - _iter;
        }

        constexpr fn data() const -> const TElem*
            requires(RArrIterPair<TIter, TIterEnd>)
        {
            return &*_iter;
        }

        constexpr fn data() -> TElem*
            requires(RMutArrIterPair<TIter, TIterEnd>)
        {
            return &*_iter;
        }

    protected:
        TIter _iter;
        TIterEnd _end;
    };

    template <typename TIter, typename TIterEnd>
    requires(RIterPair<TIter, TIterEnd>)
    Range(TIter iter, TIterEnd end) -> Range<TIter, TIterEnd>;

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    class Range<const T*, const T*> : public Range<ArrIter<T>, ArrIter<T>>
    {
    public:
        using Base = Range<ArrIter<T>, ArrIter<T>>;

    public:
        constexpr ctor Range(const T* arr, const T* end):
            Base{ arr, end } { }

        constexpr ctor Range(const T* arr, usize count):
            Base{ arr, arr + count } { }

        template <usize count>
        constexpr ctor Range(const T(&arr)[count]):
            Base{ arr, arr + count } { }
    };

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    class Range<T*, T*> : public Range<MutArrIter<T>, MutArrIter<T>>
    {
    public:
        using Base = Range<MutArrIter<T>, MutArrIter<T>>;

    public:
        constexpr ctor Range(T* arr, T* end):
            Base{ arr, end } { }

        constexpr ctor Range(T* arr, usize count):
            Base{ arr, arr + count } { }

        template <usize count>
        constexpr ctor Range(T(&arr)[count]):
            Base{ arr, arr + count } { }
    };

    template <typename T>
    Range(T* iter, T* end) -> Range<T*, T*>;

    template <typename T>
    Range(T* iter, usize count) -> Range<T*, T*>;

    template <typename T, usize count>
    Range(T(&arr)[count]) -> Range<T*, T*>;

    /// --------------------------------------------------------------------------------------------
    /// 
    /// --------------------------------------------------------------------------------------------
    template <typename T>
    class Range<InitList<T>> : public Range<const T*, const T*>
    {
    public:
        using Base = Range<const T*, const T*>;

    public:
        constexpr ctor Range(const InitList<T>& init):
            Base{ init.begin(), init.end() } { }
    };

    template <typename T>
    Range(const InitList<T>& init) -> Range<InitList<T>>;
}