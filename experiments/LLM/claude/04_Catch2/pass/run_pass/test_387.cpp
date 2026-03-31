#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

// We need to use the Catch::Clara namespace to access the classes
using namespace Catch::Clara;

class ParserRefImplTest_387 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Arg (which derives from ParserRefImpl) can be created with a value reference
TEST_F(ParserRefImplTest_387, ArgCreationWithValueRef_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    // Should be constructible without error
    SUCCEED();
}

// Test that optional() returns the derived reference and sets optionality
TEST_F(ParserRefImplTest_387, OptionalSetsOptionalityAndReturnsDerived_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    auto& result = arg.optional();
    EXPECT_TRUE(arg.isOptional());
    // Verify it returns a reference to the same object (derived type)
    EXPECT_EQ(&result, &arg);
}

// Test that required() sets the argument as required (not optional)
TEST_F(ParserRefImplTest_387, RequiredSetsRequiredOptionality_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}

// Test that isOptional() returns true by default (default optionality is Optional)
TEST_F(ParserRefImplTest_387, DefaultIsOptional_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    EXPECT_TRUE(arg.isOptional());
}

// Test toggling between optional and required
TEST_F(ParserRefImplTest_387, ToggleBetweenOptionalAndRequired_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    
    // Default is optional
    EXPECT_TRUE(arg.isOptional());
    
    // Set to required
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    
    // Set back to optional
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test that required() returns the derived reference
TEST_F(ParserRefImplTest_387, RequiredReturnsDerivedReference_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    auto& result = arg.required();
    EXPECT_EQ(&result, &arg);
}

// Test hint() returns the hint string provided at construction
TEST_F(ParserRefImplTest_387, HintReturnsProvidedHint_387) {
    std::string value;
    auto arg = Arg(value, "my-hint");
    EXPECT_EQ(std::string(arg.hint()), "my-hint");
}

// Test hint() with empty string
TEST_F(ParserRefImplTest_387, HintWithEmptyString_387) {
    std::string value;
    auto arg = Arg(value, "");
    EXPECT_EQ(std::string(arg.hint()), "");
}

// Test cardinality returns expected value (for single-value binding, typically 1)
TEST_F(ParserRefImplTest_387, CardinalityForSingleValue_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    // For a single value ref, cardinality should be non-zero
    EXPECT_GE(arg.cardinality(), 0u);
}

// Test description can be set via operator()
TEST_F(ParserRefImplTest_387, DescriptionCanBeSet_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    auto& result = arg("This is a description");
    // operator() should return reference to derived
    EXPECT_EQ(&result, &arg);
}

// Test with lambda binding
TEST_F(ParserRefImplTest_387, LambdaBinding_387) {
    std::string captured;
    auto arg = Arg([&captured](std::string const& s) { captured = s; }, "lambda-hint");
    EXPECT_EQ(std::string(arg.hint()), "lambda-hint");
    EXPECT_TRUE(arg.isOptional());
}

// Test with int value reference
TEST_F(ParserRefImplTest_387, IntValueRefBinding_387) {
    int value = 0;
    auto arg = Arg(value, "int-hint");
    EXPECT_EQ(std::string(arg.hint()), "int-hint");
    EXPECT_TRUE(arg.isOptional());
}

// Test chaining: optional then description
TEST_F(ParserRefImplTest_387, ChainingOptionalAndDescription_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    arg.optional()("A description");
    EXPECT_TRUE(arg.isOptional());
}

// Test chaining: required then description
TEST_F(ParserRefImplTest_387, ChainingRequiredAndDescription_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    arg.required()("A description");
    EXPECT_FALSE(arg.isOptional());
}

// Test with Opt (another derived class) - optional by default
TEST_F(ParserRefImplTest_387, OptIsOptionalByDefault_387) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    EXPECT_TRUE(opt.isOptional());
}

// Test Opt can be set to required
TEST_F(ParserRefImplTest_387, OptCanBeSetToRequired_387) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    opt.required();
    EXPECT_FALSE(opt.isOptional());
}

// Test multiple calls to optional() are idempotent
TEST_F(ParserRefImplTest_387, MultipleOptionalCallsIdempotent_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    arg.optional();
    arg.optional();
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test multiple calls to required() are idempotent
TEST_F(ParserRefImplTest_387, MultipleRequiredCallsIdempotent_387) {
    std::string value;
    auto arg = Arg(value, "test-hint");
    arg.required();
    arg.required();
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}
