// Filename: parser_exename_operator_or_eq_394_tests.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::ExeName;

class ParserOperatorOrEqExeNameTest_394 : public ::testing::Test {};

// Verifies that operator|=(ExeName) returns a reference to *this.
TEST_F(ParserOperatorOrEqExeNameTest_394, ReturnsSelfReference_394) {
    Parser p;
    ExeName exe;
    Parser& ret = (p |= exe);
    EXPECT_EQ(&ret, &p);
}

// Verifies that the operator accepts a temporary ExeName object.
// (Const reference parameter should bind to a temporary safely during the call.)
TEST_F(ParserOperatorOrEqExeNameTest_394, AcceptsTemporaryExeName_394) {
    Parser p;
    Parser& ret = (p |= ExeName{});
    EXPECT_EQ(&ret, &p);
}

// Verifies the operator is chainable (returns Parser&).
TEST_F(ParserOperatorOrEqExeNameTest_394, SupportsChaining_394) {
    Parser p;
    ExeName exe1;
    ExeName exe2;
    Parser& ret = ((p |= exe1) |= exe2);
    EXPECT_EQ(&ret, &p);
}

// Applying the operator multiple times should not throw and should remain usable.
TEST_F(ParserOperatorOrEqExeNameTest_394, MultipleApplicationsNoThrow_394) {
    Parser p;
    ExeName exe1;
    ExeName exe2;
    EXPECT_NO_THROW({
        (p |= exe1);
        (p |= exe2);
    });
    // Still returns self after multiple applications
    Parser& ret = (p |= exe1);
    EXPECT_EQ(&ret, &p);
}
