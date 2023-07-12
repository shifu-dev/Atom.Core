#pragma once
#include <mutex>

#include "Atom/Core.h"
#include "Atom/Exceptions.h"
#include "Atom/Memory/Lockable.h"

namespace Atom
{
    /// --------------------------------------------------------------------------------------------
    /// NullLockable is a stateless object that doesn't has any locking mechanism.
    /// It's used where a Lockable implementation is needed but thread-safety is not needed.
    /// 
    /// @TODO: Should we delete its constructors and operators to match {SimpleMutex}?
    /// --------------------------------------------------------------------------------------------
    class NullLockable
    {
    public:
        /// ----------------------------------------------------------------------------------------
        /// DefaultConstructor. Does nothing.
        /// ----------------------------------------------------------------------------------------
        constexpr ctor NullLockable() noex { }

        /// ----------------------------------------------------------------------------------------
        /// CopyConstructor is default.
        /// ----------------------------------------------------------------------------------------
        constexpr ctor NullLockable(const NullLockable& other) { }

        /// ----------------------------------------------------------------------------------------
        /// MoveConstructor is default.
        /// ----------------------------------------------------------------------------------------
        constexpr ctor NullLockable(NullLockable&& other) { }

        /// ----------------------------------------------------------------------------------------
        /// CopyOperator is default.
        /// ----------------------------------------------------------------------------------------
        constexpr fn operator = (const NullLockable& other) -> NullLockable& { return *this; }

        /// ----------------------------------------------------------------------------------------
        /// MoveOperator is default.
        /// ----------------------------------------------------------------------------------------
        constexpr fn operator = (NullLockable&& other) -> NullLockable& { return *this; }

        /// ----------------------------------------------------------------------------------------
        /// Destructor. Does nothing.
        /// ----------------------------------------------------------------------------------------
        constexpr dtor NullLockable() { }

    public:
        /// ----------------------------------------------------------------------------------------
        /// Does nothing.
        /// ----------------------------------------------------------------------------------------
        constexpr void Lock() { }

        /// ----------------------------------------------------------------------------------------
        /// Always returns true.
        /// ----------------------------------------------------------------------------------------
        constexpr bool TryLock() { return true; }

        /// ----------------------------------------------------------------------------------------
        /// Does nothing.
        /// ----------------------------------------------------------------------------------------
        constexpr void Unlock() { }
    };

    static_assert(RLockable<NullLockable>);

    /// --------------------------------------------------------------------------------------------
    /// Specialization for NullLockable to avoid any performance overhead.
    /// --------------------------------------------------------------------------------------------
    template <>
    class LockGuard <NullLockable>
    {
    public:
        /// ----------------------------------------------------------------------------------------
        /// Constructor. Does nothing.
        /// 
        /// @PARAM[IN] lock NullLockable reference. (UNUSED).
        /// ----------------------------------------------------------------------------------------
        constexpr ctor LockGuard(NullLockable& lock) noex { }

        /// ----------------------------------------------------------------------------------------
        /// Destructor. Does nothing.
        /// ----------------------------------------------------------------------------------------
        constexpr dtor LockGuard() { }
    };
}