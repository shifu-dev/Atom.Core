#pragma once
#include "StdIterWrapForAtomIter.h"
#include "RangeReq.h"

#include <algorithm>

namespace Atom
{
    struct RangeHelper
    {
        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RRange<TRange>
        constexpr fn CanGetCount() const noex -> bool
        {
            return RFwdRange<TRange>;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RFwdRange<TRange>
        constexpr fn GetCount(const TRange& range) const noex -> usize
        {
            return _GetCount(range.Iter(), range.IterEnd());
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange, class T>
        requires RMutRange<TRange>
            and RAssignable<tname TRange::TElem, T>
        constexpr fn Fill(TRange&& range, T&& val) const -> void
        {
            _Fill(range.Iter(), range.IterEnd(), fwd(val));
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
    #pragma optimize("", off)
        template <class TRange, tname T>
        requires RMutRange<TRange>
            and RAssignable<tname TRange::TElem, T>
        constexpr fn FillExplicit(TRange&& range, T&& val) const -> void
        {
            _Fill(range.Iter(), range.IterEnd(), fwd(val));
        }
    #pragma optimize("", on)

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange1, class TRange2>
        requires RRange<TRange1>
            and RMutRange<TRange2>
            and RAssignable<tname TRange2::TElem, tname TRange1::TElem>
        constexpr fn FwdCopyTo(const TRange1& range1, TRange2&& range2) const -> void
        {
            _FwdCopy(range1.Iter(), range1.IterEnd(), range2.Iter(), range2.IterEnd());
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange1, class TRange2>
        requires RRange<TRange1>
            and RMutRange<TRange2>
            and RAssignable<tname TRange2::TElem, tname TRange1::TElem>
        constexpr fn BwdCopyTo(const TRange1& range1, TRange2&& range2) const -> void
        {
            _BwdCopy(range1.Iter(), range1.IterEnd(), range2.Iter(), range2.IterEnd());
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange1, class TRange2>
        requires RMutRange<TRange1>
            and RMutRange<TRange2>
            and RAssignable<tname TRange2::TElem, tname TRange1::TElem>
        constexpr fn FwdMoveTo(TRange1&& range1, TRange2&& range2) const -> void
        {
            _FwdMove(range1.Iter(), range1.IterEnd(), range2.Iter(), range2.IterEnd());
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange1, class TRange2>
        requires RMutRange<TRange1>
            and RMutRange<TRange2>
            and RAssignable<tname TRange2::TElem, tname TRange1::TElem>
        constexpr fn BwdMoveTo(TRange1&& range1, TRange2&& range2) const -> void
        {
            _BwdMove(range1.Iter(), range1.IterEnd(), range2.Iter(), range2.IterEnd());
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutFwdRange<TRange>
            and RMoveAssignable<tname TRange::TElem>
        constexpr fn ShiftFwd(TRange&& range, usize steps) const -> void
        {
            _FwdShift(range.Iter(), range.IterEnd(), steps);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutFwdRange<TRange>
            and RMoveAssignable<tname TRange::TElem>
        constexpr fn ShiftBwd(TRange&& range, usize steps) const -> void
        {
            _BwdShift(range.Iter(), range.IterEnd(), steps);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutFwdRange<TRange>
            and RSwappable<tname TRange::TElem>
        constexpr fn ShiftBy(TRange&& range, isize steps) const -> void
        {
            if (steps > 0)
            {
                _BwdShift(range.Iter(), range.IterEnd(), steps);
            }
            else
            {
                _FwdShift(range.Iter(), range.IterEnd(), -steps);
            }
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutRange<TRange>
            and RSwappable<tname TRange::TElem>
        constexpr fn RotateFwd(TRange&& range, usize steps) const -> void
        {
            _FwdRotate(range.Iter(), range.IterEnd(), steps);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutRange<TRange>
            and RSwappable<tname TRange::TElem>
        constexpr fn RotateBwd(TRange&& range, usize steps) const -> void
        {
            _BwdRotate(range.Iter(), range.IterEnd(), steps);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutRange<TRange>
            and RSwappable<tname TRange::TElem>
        constexpr fn RotateBy(TRange&& range, isize steps) const -> void
        {
            if (steps > 0)
            {
                _BwdRotate(range.Iter(), range.IterEnd(), steps);
            }
            else
            {
                _FwdRotate(range.Iter(), range.IterEnd(), -steps);
            }
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        template <class TRange>
        requires RMutRange<TRange>
            and RDestructible<tname TRange::TElem>
        constexpr fn Destruct(TRange&& range) const -> void
        {
            _Destruct(range.Iter(), range.IterEnd());
        }

    private:
        template <class TIter, class TIterEnd>
        constexpr fn _GetCount(TIter iter, TIterEnd iterEnd) const -> usize
        {
            if constexpr (RJumpIterPair<TIter, TIterEnd>)
            {
                return iterEnd - iter;
            }

            usize count = 0;
            for (; iter != iterEnd; iter++) count++;

            return count;
        }

        template <class TIter, class TIterEnd, tname T>
        constexpr fn _Fill(TIter iter, TIterEnd iterEnd, T&& val) const -> void
        {
            StdIterWrapForAtomIter stdIter{ iter };
            StdIterWrapForAtomIter stdIterEnd{ iterEnd };

            std::fill(stdIter, stdIterEnd, fwd(val));
        }

        template <class TIter1, class TIterEnd1, class TIter2, class TIterEnd2>
        constexpr fn _FwdCopy(const TIter1 iter1, const TIterEnd1 iterEnd1,
            TIter2 iter2, TIterEnd2 iterEnd2) const -> void
        {
            StdIterWrapForAtomIter stdIter1{ iter1 };
            StdIterWrapForAtomIter stdIterEnd1{ iterEnd1 };
            StdIterWrapForAtomIter stdIter2{ iter2 };

            std::copy(stdIter1, stdIterEnd1, stdIter2);
        }

        template <class TIter1, class TIterEnd1, class TIter2, class TIterEnd2>
        constexpr fn _BwdCopy(const TIter1 iter1, const TIterEnd1 iterEnd1,
            TIter2 iter2, TIterEnd2 iterEnd2) const -> void
        {
            StdIterWrapForAtomIter stdIter1{ iter1 };
            StdIterWrapForAtomIter stdIterEnd1{ iterEnd1 };
            StdIterWrapForAtomIter stdIter2{ iter2 };

            std::copy_backward(stdIter1, stdIterEnd1, stdIter2);
        }

        template <class TIter1, class TIterEnd1, class TIter2, class TIterEnd2>
        constexpr fn _FwdMove(TIter1 iter1, const TIterEnd1 iterEnd1,
            TIter2 iter2, TIterEnd2 iterEnd2) const -> void
        {
            StdIterWrapForAtomIter stdIter1{ iter1 };
            StdIterWrapForAtomIter stdIterEnd1{ iterEnd1 };
            StdIterWrapForAtomIter stdIter2{ iter2 };

            std::move(stdIter1, stdIterEnd1, stdIter2);
        }

        template <class TIter1, class TIterEnd1, class TIter2, class TIterEnd2>
        constexpr fn _BwdMove(TIter1 iter1, const TIterEnd1 iterEnd1,
            TIter2 iter2, TIterEnd2 iterEnd2) const -> void
        {
            StdIterWrapForAtomIter stdIter1{ iter1 };
            StdIterWrapForAtomIter stdIterEnd1{ iterEnd1 };
            StdIterWrapForAtomIter stdIter2{ iter2 };

            std::move_backward(stdIter1, stdIterEnd1, stdIter2);
        }

        template <class TIter, class TIterEnd>
        constexpr fn _FwdShift(TIter iter, TIterEnd iterEnd, usize steps) const -> void
        {
            if constexpr (RArrIterPair<TIter, TIterEnd>)
            {
                std::shift_right(&*iter, &*iterEnd, steps);
                return;
            }

            StdIterWrapForAtomIter stdIter{ iter };
            StdIterWrapForAtomIter stdIterEnd{ iterEnd };

            std::shift_right(stdIter, stdIterEnd, steps);
        }

        template <class TIter, class TIterEnd>
        constexpr fn _BwdShift(TIter iter, TIterEnd iterEnd, usize steps) const -> void
        {
            if constexpr (RArrIterPair<TIter, TIterEnd>)
            {
                std::shift_left(&*iter, &*iterEnd, steps);
                return;
            }

            StdIterWrapForAtomIter stdIter{ iter };
            StdIterWrapForAtomIter stdIterEnd{ iterEnd };

            std::shift_left(stdIter, stdIterEnd, steps);
        }

        template <class TIter, class TIterEnd>
        constexpr fn _BwdRotate(TIter iter, TIterEnd iterEnd, usize steps) const -> void
        {
            if constexpr (RArrIterPair<TIter, TIterEnd>)
            {
                std::rotate(&*iter, &*iter + steps, &*iterEnd);
                return;
            }

            StdIterWrapForAtomIter stdIter{ iter };
            StdIterWrapForAtomIter stdIterEnd{ iterEnd };

            std::rotate(stdIter, stdIter + steps, stdIterEnd);
        }

        template <class TIter, class TIterEnd>
        constexpr fn _FwdRotate(TIter iter, TIterEnd iterEnd, isize steps) const -> void
        {
            if constexpr (RArrIterPair<TIter, TIterEnd>)
            {
                std::rotate(&*iter, &*iterEnd - steps, &*iterEnd);
                return;
            }

            StdIterWrapForAtomIter stdIter{ iter };
            StdIterWrapForAtomIter stdIterEnd{ iterEnd };

            std::rotate(stdIter, stdIterEnd - steps, stdIterEnd);
        }

        template <class TIter, class TIterEnd>
        constexpr fn _Destruct(TIter iter, TIterEnd iterEnd) const -> void
        {
            if constexpr (RArrIterPair<TIter, TIterEnd>)
            {
                std::destroy(&*iter, &*iterEnd);
                return;
            }

            StdIterWrapForAtomIter stdIter{ iter };
            StdIterWrapForAtomIter stdIterEnd{ iterEnd };

            std::destroy(stdIter, stdIterEnd);
        }
    };
}