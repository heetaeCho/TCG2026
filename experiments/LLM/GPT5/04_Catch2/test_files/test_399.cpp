// File: tests/parser_pipe_operator_tests_399.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the header that declares Catch::Clara::Parser and the friend operator|
#include "Catch2/src/catch2/internal/catch_clara.hpp"

//
// The tests treat Parser as a black box.
// To verify that the free friend operator| forwards to operator|= properly,
// we provide *external* collaborator types (Spy) along with *free* operator|=
// overloads defined in the Catch::Clara namespace. These do not access or
// depend on any Parser internals; they simply record that they were invoked,
// which is observable behavior suitable for testing the forwarding.
//

// A simple spy that counts how many times it was used with lvalue vs rvalue.
struct Spy {
    mutable int lvalue_calls = 0;
    mutable int rvalue_calls = 0;
};

// A second spy type to show ADL works for different RHS types as well.
struct Spy2 {
    mutable int calls = 0;
};

// Define operator|= overloads in Catch::Clara namespace so ADL finds them.
// They DO NOT touch Parser internals; they only update the spy and return p.
namespace Catch { namespace Clara {

    // Overload for lvalue Spy
    inline Parser& operator|=(Parser& p, Spy const& s) {
        ++s.lvalue_calls;
        return p;
    }

    // Overload for rvalue Spy
    inline Parser& operator|=(Parser& p, Spy&& s) {
        ++s.rvalue_calls;
        return p;
    }

    // Overload for Spy2 (lvalue only, to prove chaining & ADL with another type)
    inline Parser& operator|=(Parser& p, Spy2 const& s2) {
        ++s2.calls;
        return p;
    }

}} // namespace Catch::Clara

using Catch::Clara::Parser;

// ---------- Tests ----------

TEST(ParserPipeOperator_399, InvokesOperatorOrEqualsForLvalueRhs_399) {
    Parser p;
    Spy s;

    // friend operator| takes Parser&&, but inside it, `p` is a named rvalue ref,
    // which is an lvalue, so it binds to the (Parser&, Spy const&) overload.
    auto result = std::move(p) | s;

    EXPECT_EQ(s.lvalue_calls, 1);
    EXPECT_EQ(s.rvalue_calls, 0);

    // Also ensure the expression returns a Parser by value (compile-time check)
    static_assert(std::is_same<decltype(std::move(p) | s), Parser>::value,
                  "operator| must return Parser by value");
    (void)result; // silence unused variable warning
}

TEST(ParserPipeOperator_399, PerfectForwardsRvalueRhs_399) {
    Spy s;
    // Using rvalue Spy should hit the (Parser&, Spy&&) overload inside operator|=
    auto result = Parser{} | std::move(s);

    EXPECT_EQ(s.rvalue_calls, 1);
    EXPECT_EQ(s.lvalue_calls, 0);
    (void)result;
}

TEST(ParserPipeOperator_399, SupportsChainingMultipleRhs_399) {
    Spy a, b;

    // Each `|` should forward to the appropriate operator|= overload once.
    auto result = Parser{} | a | b;

    EXPECT_EQ(a.lvalue_calls, 1);
    EXPECT_EQ(b.lvalue_calls, 1);
    EXPECT_EQ(a.rvalue_calls, 0);
    EXPECT_EQ(b.rvalue_calls, 0);
    (void)result;
}

TEST(ParserPipeOperator_399, WorksWithDifferentRhsTypesViaADL_399) {
    Spy2 s2;

    // Demonstrates that operator| correctly forwards to a matching operator|=
    // overload for a *different* RHS type, discovered via ADL.
    auto result = Parser{} | s2;

    EXPECT_EQ(s2.calls, 1);
    (void)result;
}

TEST(ParserPipeOperator_399, ReturnTypeIsParserByValue_399) {
    // Compile-time verification that the friend operator| returns Parser by value
    using Ret = decltype(std::declval<Parser&&>() | std::declval<Spy&>());
    static_assert(std::is_same<Ret, Parser>::value,
                  "operator| should return Parser by value");
    SUCCEED(); // If it compiles and reaches here, the assertion above holds.
}

TEST(ParserPipeOperator_399, ChainingUsesLvalueParserInsidePipe_399) {
    // Even though the initial Parser is an rvalue, the named parameter `p`
    // inside operator| is an lvalue, so an operator|= requiring Parser& is usable.
    // We prove this by only providing a (Parser&, Spy2 const&) overload (above).
    Spy2 s2a, s2b;

    auto result = Parser{} | s2a | s2b;

    EXPECT_EQ(s2a.calls, 1);
    EXPECT_EQ(s2b.calls, 1);
    (void)result;
}
