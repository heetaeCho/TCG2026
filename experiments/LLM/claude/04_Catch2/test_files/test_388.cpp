#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>

// We need to use the concrete derived types that exist in the Clara framework.
// Typically, `Arg` and `Opt` are the derived types of `ParserRefImpl`.
// We'll use them to test the `ParserRefImpl` interface.

using namespace Catch::Clara;

class ParserRefImplTest_388 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that required() sets the optionality to Required (isOptional returns false)
TEST_F(ParserRefImplTest_388, RequiredMakesNotOptional_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}

// Test that optional() sets the optionality to Optional (isOptional returns true)
TEST_F(ParserRefImplTest_388, OptionalMakesOptional_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test that default optionality is Optional
TEST_F(ParserRefImplTest_388, DefaultIsOptional_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    EXPECT_TRUE(arg.isOptional());
}

// Test that required() returns a reference to the derived type (allows chaining)
TEST_F(ParserRefImplTest_388, RequiredReturnsDerivedReference_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    auto& result = arg.required();
    // The returned reference should refer to the same object
    EXPECT_EQ(&result, &arg);
    EXPECT_FALSE(result.isOptional());
}

// Test that optional() returns a reference to the derived type (allows chaining)
TEST_F(ParserRefImplTest_388, OptionalReturnsDerivedReference_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    auto& result = arg.optional();
    EXPECT_EQ(&result, &arg);
    EXPECT_TRUE(result.isOptional());
}

// Test hint() returns the hint that was set in construction
TEST_F(ParserRefImplTest_388, HintReturnsConstructedHint_388) {
    std::string value;
    auto arg = Arg(value, "my_hint");
    EXPECT_EQ(arg.hint(), "my_hint");
}

// Test that calling description via operator() works and is chainable
TEST_F(ParserRefImplTest_388, DescriptionOperatorChaining_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    auto& result = arg("some description");
    EXPECT_EQ(&result, &arg);
}

// Test toggling between required and optional multiple times
TEST_F(ParserRefImplTest_388, ToggleOptionalityMultipleTimes_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");

    EXPECT_TRUE(arg.isOptional());

    arg.required();
    EXPECT_FALSE(arg.isOptional());

    arg.optional();
    EXPECT_TRUE(arg.isOptional());

    arg.required();
    EXPECT_FALSE(arg.isOptional());

    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

// Test with Opt (another derived type of ParserRefImpl)
TEST_F(ParserRefImplTest_388, OptRequiredSetsNotOptional_388) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    // Default should be optional for Opt
    EXPECT_TRUE(opt.isOptional());
    opt.required();
    EXPECT_FALSE(opt.isOptional());
}

// Test with Opt optional returns to optional
TEST_F(ParserRefImplTest_388, OptOptionalSetsOptional_388) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A flag option");
    opt.required();
    EXPECT_FALSE(opt.isOptional());
    opt.optional();
    EXPECT_TRUE(opt.isOptional());
}

// Test cardinality with a simple value reference (should be 1)
TEST_F(ParserRefImplTest_388, CardinalityForSingleValue_388) {
    std::string value;
    auto arg = Arg(value, "test_hint");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// Test with lambda-based construction
TEST_F(ParserRefImplTest_388, LambdaConstructorRequiredOptional_388) {
    auto arg = Arg([](std::string const&) -> Detail::ParserResult {
        return Detail::ParserResult::ok(Detail::ParseResultType::Matched);
    }, "lambda_hint");
    
    EXPECT_TRUE(arg.isOptional());
    arg.required();
    EXPECT_FALSE(arg.isOptional());
    EXPECT_EQ(arg.hint(), "lambda_hint");
}

// Test with integer reference
TEST_F(ParserRefImplTest_388, IntRefHintAndOptionality_388) {
    int value = 0;
    auto arg = Arg(value, "int_hint");
    EXPECT_EQ(arg.hint(), "int_hint");
    EXPECT_TRUE(arg.isOptional());
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}

// Test chaining required() with description operator()
TEST_F(ParserRefImplTest_388, ChainingRequiredWithDescription_388) {
    std::string value;
    auto arg = Arg(value, "hint");
    arg.required()("This is required");
    EXPECT_FALSE(arg.isOptional());
}

// Test chaining optional() with description operator()
TEST_F(ParserRefImplTest_388, ChainingOptionalWithDescription_388) {
    std::string value;
    auto arg = Arg(value, "hint");
    arg.required();
    arg.optional()("This is optional");
    EXPECT_TRUE(arg.isOptional());
}

// Test empty hint string
TEST_F(ParserRefImplTest_388, EmptyHint_388) {
    std::string value;
    auto arg = Arg(value, "");
    EXPECT_EQ(arg.hint(), "");
}
