#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;

// Test fixture for Parser and Opt interaction
class ParserOptTest_397 : public ::testing::Test {
protected:
    Parser parser;
};

// Normal operation: Adding an Opt to a Parser using operator|=
TEST_F(ParserOptTest_397, AddOptToParser_397) {
    bool flag = false;
    Opt opt(flag);

    Parser& result = (parser |= std::move(opt));

    // Verify that operator|= returns the same parser reference
    EXPECT_EQ(&result, &parser);
}

// Boundary condition: Adding multiple Opt objects to a Parser
TEST_F(ParserOptTest_397, AddMultipleOptsToParser_397) {
    bool flag1 = false;
    bool flag2 = false;
    Opt opt1(flag1);
    Opt opt2(flag2);

    parser |= std::move(opt1);
    parser |= std::move(opt2);

    // Just ensure parser reference remains valid and chaining works
    Parser& result = (parser |= Opt(flag1));
    EXPECT_EQ(&result, &parser);
}

// Exceptional/edge case: Ensure operator|= handles Opt with same reference without error
TEST_F(ParserOptTest_397, AddSameOptMultipleTimes_397) {
    bool flag = false;
    Opt opt(flag);

    parser |= std::move(opt);
    parser |= Opt(flag); // add another with same underlying reference

    // Still should return parser itself
    Parser& result = (parser |= Opt(flag));
    EXPECT_EQ(&result, &parser);
}

// Interaction test: Ensure chaining operator|= works naturally
TEST_F(ParserOptTest_397, OperatorChainingWorks_397) {
    bool flag1 = false;
    bool flag2 = false;

    Parser& result = (parser |= Opt(flag1)) |= Opt(flag2);

    EXPECT_EQ(&result, &parser);
}
