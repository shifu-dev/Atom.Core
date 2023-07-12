#pragma once
#include "Atom/Exceptions/Exceptions.h"
#include "Atom/Exceptions/Assertions.decl.h"

namespace Atom
{
    inline ctor AssertException::AssertException(Str msg, StrView assertExpr) noex:
        assertExpr{ assertExpr }, Exception(MOVE(msg)) { }
}