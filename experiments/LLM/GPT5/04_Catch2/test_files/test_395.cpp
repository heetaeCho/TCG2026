// File: tests/parser_operator_or_equals_arg_395.cpp
#include <gtest/gtest.h>

// Include the provided header with the operator|=(Arg const&) implementation
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::Arg;

// We keep tests minimal and interface-driven: verify the returned reference,
// chainability, and that common usages do not throw. We do NOT inspect any
// private state (e.g., internal arg storage).

// TEST_ID: 395
TEST(ParserOperatorOrEquals_395, ReturnsSelfReference_395) {
    Parser p;
    Arg a{}; // Construct via public interface only
    Parser& ref = (p |= a);
    // The operator should return a reference to the same object
    EXPECT_EQ(&ref, &p);
}

// TEST_ID: 395
TEST(ParserOperatorOrEquals_395, SupportsChainingWithMultipleArgs_395) {
    Parser p;
    Arg a1{};
    Arg a2{};

    // Verify that chaining is supported and still returns self reference
    Parser& ref = ((p |= a1) |= a2);
    EXPECT_EQ(&ref, &p);
}

// TEST_ID: 395
TEST(ParserOperatorOrEquals_395, AcceptsConstLvalueArg_395) {
    Parser p;
    const Arg a{};
    // Using a const lvalue should compile and not throw; also return self
    EXPECT_NO_THROW({
        Parser& ref = (p |= a);
        EXPECT_EQ(&ref, &p);
    });
}

// TEST_ID: 395
TEST(ParserOperatorOrEquals_395, MultipleAddsAreExceptionSafe_395) {
    Parser p;
    Arg a1{};
    Arg a2{};
    Arg a3{};

    // We don't assume anything about internal storage or counts.
    // We just assert that repeated, valid usage does not throw.
    EXPECT_NO_THROW({
        (void)(p |= a1);
        (void)(p |= a2);
        (void)(p |= a3);
    });
}
