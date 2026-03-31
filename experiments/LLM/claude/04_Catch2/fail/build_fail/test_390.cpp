#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <vector>

// We need to use the concrete derived types (Arg and Opt) that derive from ParserRefImpl
// Since ParserRefImpl is a CRTP template, we need actual derived classes to test it.

using namespace Catch::Clara;

class ParserRefImplTest_390 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test cardinality returns 1 for a non-container (scalar) bound reference
TEST_F(ParserRefImplTest_390, CardinalityReturnsOneForScalarRef_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test cardinality returns 0 for a container (accept_many) bound reference
TEST_F(ParserRefImplTest_390, CardinalityReturnsZeroForContainerRef_390) {
    std::vector<std::string> values;
    auto arg = Detail::Arg(Detail::accept_many, [&values](std::string const& v) {
        values.push_back(v);
    }, "values");
    EXPECT_EQ(arg.cardinality(), 0u);
}

// Test isOptional returns true by default
TEST_F(ParserRefImplTest_390, IsOptionalByDefault_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value");
    EXPECT_TRUE(arg.isOptional());
}

// Test required() makes isOptional return false
TEST_F(ParserRefImplTest_390, RequiredMakesIsOptionalFalse_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value").required();
    EXPECT_FALSE(arg.isOptional());
}

// Test optional() makes isOptional return true (after required)
TEST_F(ParserRefImplTest_390, OptionalMakesIsOptionalTrue_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value").required().optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test hint() returns the hint string that was passed in
TEST_F(ParserRefImplTest_390, HintReturnsProvidedHint_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "my_hint");
    EXPECT_EQ(arg.hint(), "my_hint");
}

// Test hint with empty string
TEST_F(ParserRefImplTest_390, HintReturnsEmptyStringWhenEmpty_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "");
    EXPECT_EQ(arg.hint(), "");
}

// Test operator() sets description and returns reference for chaining
TEST_F(ParserRefImplTest_390, OperatorParenSetsDescription_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value")("This is a description");
    // The description is set; we can verify via the interface if available.
    // At minimum, verify the object is still valid and cardinality works.
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test with string type bound reference
TEST_F(ParserRefImplTest_390, CardinalityReturnsOneForStringRef_390) {
    std::string value;
    auto arg = Detail::Arg(value, "str_value");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test with bool type bound reference (Opt)
TEST_F(ParserRefImplTest_390, CardinalityReturnsOneForBoolOpt_390) {
    bool flag = false;
    auto opt = Detail::Opt(flag)["-f"]["--flag"]("A flag option");
    EXPECT_EQ(opt.cardinality(), 1u);
}

// Test with lambda bound reference
TEST_F(ParserRefImplTest_390, CardinalityReturnsOneForLambdaRef_390) {
    int captured = 0;
    auto arg = Detail::Arg([&captured](int v) { captured = v; }, "lambda_value");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test chaining required() returns the correct type for further chaining
TEST_F(ParserRefImplTest_390, RequiredReturnsDerivedTypeForChaining_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value").required();
    EXPECT_FALSE(arg.isOptional());
    EXPECT_EQ(arg.cardinality(), 1u);
    EXPECT_EQ(arg.hint(), "value");
}

// Test chaining optional() returns the correct type for further chaining
TEST_F(ParserRefImplTest_390, OptionalReturnsDerivedTypeForChaining_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value").optional();
    EXPECT_TRUE(arg.isOptional());
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test container with vector<int>
TEST_F(ParserRefImplTest_390, CardinalityReturnsZeroForVectorContainer_390) {
    std::vector<int> values;
    auto arg = Detail::Arg(Detail::accept_many, [&values](int v) {
        values.push_back(v);
    }, "int_values");
    EXPECT_EQ(arg.cardinality(), 0u);
}

// Test double type reference
TEST_F(ParserRefImplTest_390, CardinalityReturnsOneForDoubleRef_390) {
    double value = 0.0;
    auto arg = Detail::Arg(value, "double_value");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test Opt with non-flag option
TEST_F(ParserRefImplTest_390, OptWithValueCardinalityIsOne_390) {
    int value = 0;
    auto opt = Detail::Opt(value, "num")["-n"]["--number"]("A number option");
    EXPECT_EQ(opt.cardinality(), 1u);
}

// Test that optional/required toggling works correctly
TEST_F(ParserRefImplTest_390, ToggleOptionalRequired_390) {
    int value = 0;
    auto arg = Detail::Arg(value, "value");
    
    EXPECT_TRUE(arg.isOptional());
    
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
    
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}
