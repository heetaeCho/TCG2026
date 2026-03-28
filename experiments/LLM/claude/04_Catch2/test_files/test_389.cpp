#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>
#include <memory>

// We need to work with concrete derived types that exist in Clara.
// In Catch2's Clara, `Arg` and `Opt` are the concrete derived classes of ParserRefImpl.
// Let's use them to test ParserRefImpl's interface.

using namespace Catch::Clara;

class ParserRefImplTest_389 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed Arg (bound to a value) is optional by default
TEST_F(ParserRefImplTest_389, DefaultOptionalityIsOptional_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    EXPECT_TRUE(arg.isOptional());
}

// Test that calling required() makes it non-optional
TEST_F(ParserRefImplTest_389, RequiredMakesNonOptional_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}

// Test that calling optional() after required() restores optionality
TEST_F(ParserRefImplTest_389, OptionalAfterRequiredRestoresOptional_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test that calling optional() on already optional stays optional
TEST_F(ParserRefImplTest_389, OptionalOnAlreadyOptionalRemainsOptional_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test that hint returns the hint provided at construction
TEST_F(ParserRefImplTest_389, HintReturnsConstructedHint_389) {
    std::string value;
    Detail::Arg arg(value, "my-hint");
    EXPECT_EQ(std::string(arg.hint()), "my-hint");
}

// Test that hint returns empty when constructed with empty hint
TEST_F(ParserRefImplTest_389, HintReturnsEmptyWhenEmpty_389) {
    std::string value;
    Detail::Arg arg(value, "");
    EXPECT_EQ(std::string(arg.hint()), "");
}

// Test cardinality for a simple value ref (should be 1)
TEST_F(ParserRefImplTest_389, CardinalityForValueRefIsOne_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test cardinality for a lambda ref (should be 1)
TEST_F(ParserRefImplTest_389, CardinalityForLambdaRefIsOne_389) {
    auto lambda = [](std::string const&) -> Catch::Clara::Detail::ParserResult {
        return Detail::ParserResult::ok(Detail::ParseResultType::Matched);
    };
    Detail::Arg arg(lambda, "test-hint");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test cardinality for accept_many (should be 0, meaning unbounded)
TEST_F(ParserRefImplTest_389, CardinalityForAcceptManyIsZero_389) {
    auto lambda = [](std::string const&) -> Catch::Clara::Detail::ParserResult {
        return Detail::ParserResult::ok(Detail::ParseResultType::Matched);
    };
    Detail::Arg arg(Detail::accept_many, lambda, "test-hint");
    EXPECT_EQ(arg.cardinality(), 0u);
}

// Test description setter via operator()
TEST_F(ParserRefImplTest_389, OperatorParenSetsDescription_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    // operator() returns a reference to derived, so it should be chainable
    auto& ref = arg("This is a description");
    // Verify it returns a reference to the same object
    EXPECT_EQ(&ref, &arg);
}

// Test required() returns reference to self for chaining
TEST_F(ParserRefImplTest_389, RequiredReturnsSelfReference_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    auto& ref = arg.required();
    EXPECT_EQ(&ref, &arg);
}

// Test optional() returns reference to self for chaining
TEST_F(ParserRefImplTest_389, OptionalReturnsSelfReference_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    auto& ref = arg.optional();
    EXPECT_EQ(&ref, &arg);
}

// Test with Opt type - default is optional
TEST_F(ParserRefImplTest_389, OptDefaultIsOptional_389) {
    bool flag = false;
    Detail::Opt opt(flag, "flag-hint");
    EXPECT_TRUE(opt.isOptional());
}

// Test with Opt type - required makes non-optional
TEST_F(ParserRefImplTest_389, OptRequiredMakesNonOptional_389) {
    bool flag = false;
    Detail::Opt opt(flag, "flag-hint");
    opt.required();
    EXPECT_FALSE(opt.isOptional());
}

// Test multiple toggles between required and optional
TEST_F(ParserRefImplTest_389, MultipleTogglesBetweenRequiredAndOptional_389) {
    std::string value;
    Detail::Arg arg(value, "test-hint");
    
    EXPECT_TRUE(arg.isOptional());
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test with int type binding
TEST_F(ParserRefImplTest_389, IntValueRefWorks_389) {
    int value = 0;
    Detail::Arg arg(value, "number");
    EXPECT_TRUE(arg.isOptional());
    EXPECT_EQ(std::string(arg.hint()), "number");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test with double type binding
TEST_F(ParserRefImplTest_389, DoubleValueRefWorks_389) {
    double value = 0.0;
    Detail::Arg arg(value, "decimal");
    EXPECT_TRUE(arg.isOptional());
    EXPECT_EQ(std::string(arg.hint()), "decimal");
}
