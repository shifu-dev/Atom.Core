#pragma once
#include "Atom/Memory/ObjectBox.h"
#include "Atom/Exceptions.h"
#include "Atom/TTI.h"
#include "Atom/Str.h"

#include "Atom/Invokable/Invokable.h"

namespace Atom
{
    namespace Private
    {
        class InvokableBoxIdentifier { };

        template <typename TResult, typename... TArgs>
        class Invoker
        {
            pub template <typename TInvokable>
            requires RInvokable<TInvokable, TResult(TArgs...)>
            fn Set()
            {
                _impl = [](void* obj, TResult& result, TArgs&&... args)
                {
                    TInvokable& invokable = *reinterpret_cast<TInvokable*>(obj);
                    new (&result) TResult(invokable(fwd(args)...));
                };
            }

            pub fn Invoke(void* invokable, TArgs&&... args) -> TResult
            {
                TResult result;
                _impl(invokable, result, fwd(args)...);

                return result;
            }

        protected:
            void (*_impl) (void* invokable, TResult& result, TArgs&&... args);
        };

        template <typename... TArgs>
        class Invoker <void, TArgs...>
        {
            pub template <RInvokable<void(TArgs...)> TInvokable>
            fn Set()
            {
                _impl = [](void* obj, TArgs&&... args)
                {
                    TInvokable& invokable = *reinterpret_cast<TInvokable*>(obj);
                    invokable(fwd(args)...);
                };
            }

            pub fn Invoke(void* invokable, TArgs&&... args)
            {
                _impl(invokable, fwd(args)...);
            }

        protected:
            void (*_impl) (void* invokable, TArgs&&... args);
        };
    }

    /// InvokableBox declaration.
    /// --------------------------------------------------------------------------------------------
    template <typename>
    class InvokableBox;

    /// 
    /// --------------------------------------------------------------------------------------------
    template <typename TResult, typename... TArgs>
    class InvokableBox <TResult(TArgs...)> extends
        ObjectBox<true, true, true, 50, DefaultMemAllocator>,
        public Private::InvokableBoxIdentifier
    {
        /// ----------------------------------------------------------------------------------------
        /// DefaultConstructor.
        /// ----------------------------------------------------------------------------------------
        pub constexpr ctor InvokableBox() { }

        /// ----------------------------------------------------------------------------------------
        /// NullConstructor.
        /// ----------------------------------------------------------------------------------------
        pub ctor InvokableBox(NullType null):
            ObjectBox(null) { }

        /// ----------------------------------------------------------------------------------------
        /// NullAssignmentOperator.
        /// ----------------------------------------------------------------------------------------
        pub fn op=(NullType null) -> InvokableBox&
        {
            ObjectBox::op=(null);
            return self;
        }

        /// ----------------------------------------------------------------------------------------
        /// NullEqualityOperator.
        /// ----------------------------------------------------------------------------------------
        pub fn op==(NullType null) const -> bool
        {
            return ObjectBox::op==(null);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub template <RInvokable<TResult(TArgs...)> TInvokable>
        requires RNotDerivedFrom<TInvokable, Private::InvokableBoxIdentifier>
        ctor InvokableBox(TInvokable&& invokable) :
            ObjectBox(fwd(invokable))
        {
            _SetInvoker<TInvokable>();
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub template <RInvokable<TResult(TArgs...)> TInvokable>
        requires RNotDerivedFrom<TInvokable, Private::InvokableBoxIdentifier>
        fn op=(TInvokable&& invokable) -> InvokableBox&
        {
            ObjectBox::op=(fwd(invokable));
            _SetInvoker<TInvokable>();
            return self;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub ctor InvokableBox(const InvokableBox& other) :
            ObjectBox(other) { }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub fn op=(const InvokableBox& other) -> InvokableBox&
        {
            ObjectBox::op=(other);
            return self;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub ctor InvokableBox(InvokableBox&& other) :
            ObjectBox(mov(other)) { }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub fn op=(InvokableBox&& other) -> InvokableBox&
        {
            ObjectBox::op=(mov(other));
            return self;
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub dtor InvokableBox() { }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub fn Invoke(TArgs&&... args) -> TResult
        {
            ATOM_ASSERT(ObjectBox::_HasObject()) << NullPointerException(
                "InvokableTarget is null.");

            return _invoker.Invoke(ObjectBox::_GetObject(), fwd(args)...);
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        pub fn op()(TArgs&&... args) -> TResult
        {
            return Invoke(fwd(args)...);
        }

        pub template <typename T>
        fn GetInvokable() -> T*
        {
            if (typeid(T) != GetInvokableType())
                return nullptr;

            return ObjectBox::_GetObject<T>();
        }

        pub fn GetInvokableType() const -> const TypeInfo&
        {
            return ObjectBox::_GetObjectType();
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        prot template <typename TInvokable>
        requires RInvokable<TInvokable, TResult(TArgs...)>
        fn _SetInvoker()
        {
            _invoker.template Set<TInvokable>();
        }

        /// ----------------------------------------------------------------------------------------
        /// 
        /// ----------------------------------------------------------------------------------------
        prot fn _InvokeInvokable(TArgs&&... args) -> TResult
        {
            return _invoker.Invoke(fwd(args)...);
        }

        prot using TInvoker = Private::Invoker<TResult, TArgs...>;

        prot TInvoker _invoker;
    };
}