// File: tests/ansi_skipping_string_iterator_test_37.cpp

#include <gtest/gtest.h>
#include <string>

// Header under test
#include "Catch2/src/catch2/internal/catch_textflow.hpp"

namespace {

using Iter = Catch::TextFlow::AnsiSkippingString::const_iterator;

// Helper to force the const overload of operator* (returns char)
// without relying on any internal state.
static char CurChar(const Iter& it_const) { return *it_const; }

class AnsiSkippingStringIteratorTest_37 : public ::testing::Test {
protected:
    std::string plain_ = "abc";
};

} // namespace

// Verifies pre-increment returns an lvalue reference to the same object.
TEST_F(AnsiSkippingStringIteratorTest_37, PreIncrement_ReturnsSelf_37) {
    Iter it{plain_};
    auto* before = &it;
    auto* after  = &(++it);     // must be the same address if operator++ returns *this
    EXPECT_EQ(before, after);
}

// Verifies pre-increment can be chained and still returns the same object reference.
TEST_F(AnsiSkippingStringIteratorTest_37, PreIncrement_ChainingReturnsSelf_37) {
    Iter it{plain_};
    auto* addr = &it;
    auto* chained = &(++(++it));
    EXPECT_EQ(addr, chained);
}

// Verifies observable position change using the public dereference (const) API.
// Uses a simple string with no ANSI sequences to avoid relying on any internal logic.
TEST_F(AnsiSkippingStringIteratorTest_37, PreIncrement_AdvancesObservablePosition_37) {
    Iter it{plain_};

    // Force const overload of operator* (char) to avoid ambiguity.
    const Iter& cit0 = it;
    EXPECT_EQ(CurChar(cit0), 'a');

    ++it;
    const Iter& cit1 = it;
    EXPECT_EQ(CurChar(cit1), 'b');
}

// Verifies postfix ++ returns the previous value (by value) and the iterator itself advances.
TEST_F(AnsiSkippingStringIteratorTest_37, PostIncrement_ReturnsOldValueAndAdvances_37) {
    Iter it{plain_};

    const Iter& cit0 = it;
    EXPECT_EQ(CurChar(cit0), 'a');

    Iter old = it++;            // old should represent position before increment
    const Iter& cold = old;
    EXPECT_EQ(CurChar(cold), 'a');  // returned value is old position

    const Iter& cit1 = it;
    EXPECT_EQ(CurChar(cit1), 'b');  // iterator advanced
}

// Verifies == and != reflect iterator position, without assuming any internal details.
TEST_F(AnsiSkippingStringIteratorTest_37, EqualityAndInequality_DependsOnPosition_37) {
    Iter it1{plain_};
    Iter it2{plain_};

    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);

    ++it1;
    EXPECT_FALSE(it1 == it2);
    EXPECT_TRUE(it1 != it2);

    ++it2;
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 != it2);
}

// Verifies <= provides a sensible ordering with respect to advancement.
TEST_F(AnsiSkippingStringIteratorTest_37, LessEqual_RespectsProgression_37) {
    Iter it1{plain_};
    Iter it2{plain_};

    EXPECT_TRUE(it1 <= it2); // same position

    ++it2;
    EXPECT_TRUE(it1 <= it2); // it1 is before it2

    ++it1;
    EXPECT_TRUE(it1 <= it2); // same position again
}

// Verifies oneBefore() reports the previous observable position.
TEST_F(AnsiSkippingStringIteratorTest_37, OneBefore_ReturnsPreviousPosition_37) {
    Iter it{plain_};

    ++it; // move to second character ('b')
    const Iter prev = it.oneBefore();

    const Iter& cprev = prev;
    const Iter& cit   = it;
    EXPECT_EQ(CurChar(cprev), 'a');
    EXPECT_EQ(CurChar(cit),   'b');
}

// (Optional lightweight compile-time check) Postfix ++ returns by value, not by reference.
TEST_F(AnsiSkippingStringIteratorTest_37, PostIncrement_ReturnType_ByValue_37) {
    Iter it{plain_};
    // decltype(it++) must be the iterator type (by value), not a reference.
    bool is_by_value = std::is_same<decltype(it++), Iter>::value;
    EXPECT_TRUE(is_by_value);
}
