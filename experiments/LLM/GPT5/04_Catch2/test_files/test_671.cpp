// File: tests/parser_validate_671_tests.cpp

#include <gtest/gtest.h>

// Include the public headers that declare Parser/Result.
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Parser;
using Catch::Clara::Detail::Result;

class ParserValidateTest_671 : public ::testing::Test {};

// [671] Empty parser: validate() should succeed (ok result, truthy)
TEST_F(ParserValidateTest_671, EmptyParserValidateOk_671) {
    Parser p;

    Result r = p.validate();

    EXPECT_TRUE(static_cast<bool>(r)) << "Expected validate() on empty parser to be ok";
    // We only assert truthiness; we do not assume specific error messages/types.
}

// [671] Composition of two empty parsers with operator|=: validate still ok
TEST_F(ParserValidateTest_671, ComposedEmptyParsersValidateOk_671) {
    Parser p1;
    Parser p2;

    p1 |= p2;  // public API for composition

    Result r = p1.validate();

    EXPECT_TRUE(static_cast<bool>(r)) << "Expected composed empty parsers to validate ok";
}

// [671] Idempotent composition: repeatedly composing empty parsers doesn't break validate
TEST_F(ParserValidateTest_671, RepeatedComposeEmptyParsersValidateOk_671) {
    Parser base;
    Parser emptyA;
    Parser emptyB;

    base |= emptyA;
    base |= emptyB;
    base |= Parser{};  // compose with another temporary empty parser

    Result r = base.validate();

    EXPECT_TRUE(static_cast<bool>(r)) << "Expected validate() to remain ok after repeated compositions";
}

// [671] Validate can be called multiple times and remains stable on unchanged parser
TEST_F(ParserValidateTest_671, MultipleValidateCallsStable_671) {
    Parser p;

    Result r1 = p.validate();
    Result r2 = p.validate();  // call again without mutation

    EXPECT_TRUE(static_cast<bool>(r1));
    EXPECT_TRUE(static_cast<bool>(r2));
}
