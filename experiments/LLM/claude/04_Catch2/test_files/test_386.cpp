#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include <gtest/gtest.h>
#include <string>

// We need to use concrete derived types from Clara to test ParserRefImpl.
// In Catch2's Clara, `Opt` and `Arg` derive from ParserRefImpl.
using namespace Catch::Clara;

class ParserRefImplTest_386 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that operator() sets description and returns reference to derived type (using Opt)
TEST_F(ParserRefImplTest_386, OperatorCallSetsDescription_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]["--flag"]("A boolean flag");
    // The fact that we can chain calls means operator() returns DerivedT&
    // We mainly verify it doesn't crash and the object is usable
    SUCCEED();
}

// Test that operator() works with empty description
TEST_F(ParserRefImplTest_386, OperatorCallWithEmptyDescription_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("");
    SUCCEED();
}

// Test isOptional returns true by default (Optionality::Optional is default)
TEST_F(ParserRefImplTest_386, IsOptionalByDefault_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("desc");
    EXPECT_TRUE(opt.isOptional());
}

// Test optional() makes it optional
TEST_F(ParserRefImplTest_386, OptionalSetsOptional_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("desc");
    opt.optional();
    EXPECT_TRUE(opt.isOptional());
}

// Test required() makes it required (not optional)
TEST_F(ParserRefImplTest_386, RequiredSetsRequired_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("desc");
    opt.required();
    EXPECT_FALSE(opt.isOptional());
}

// Test required then optional toggles back
TEST_F(ParserRefImplTest_386, RequiredThenOptionalToggles_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("desc");
    opt.required();
    EXPECT_FALSE(opt.isOptional());
    opt.optional();
    EXPECT_TRUE(opt.isOptional());
}

// Test hint() returns the hint string
TEST_F(ParserRefImplTest_386, HintReturnsCorrectValue_386) {
    std::string value;
    auto opt = Opt(value, "myHint")["-v"]("A value option");
    EXPECT_EQ(std::string(opt.hint()), "myHint");
}

// Test hint() with empty hint
TEST_F(ParserRefImplTest_386, HintReturnsEmptyWhenNotSet_386) {
    bool flag = false;
    auto opt = Opt(flag)["-f"]("desc");
    // Bool flags typically don't have hints, hint should be empty
    EXPECT_TRUE(opt.hint().empty());
}

// Test cardinality - for a single value ref, cardinality should be non-zero
TEST_F(ParserRefImplTest_386, CardinalityForSingleValue_386) {
    std::string value;
    auto opt = Opt(value, "val")["-v"]("desc");
    // A single-value option should have cardinality of 1
    EXPECT_EQ(opt.cardinality(), 1u);
}

// Test with lambda as ref
TEST_F(ParserRefImplTest_386, LambdaRefConstruction_386) {
    auto opt = Opt([](std::string const&) { return Catch::Clara::Detail::ParserResult::ok(Catch::Clara::Detail::ParseState::Matched); }, "val")["-v"]("Lambda option");
    EXPECT_EQ(std::string(opt.hint()), "val");
    EXPECT_TRUE(opt.isOptional());
}

// Test operator() returns reference allowing chaining
TEST_F(ParserRefImplTest_386, OperatorCallReturnsChainingReference_386) {
    std::string value;
    auto opt = Opt(value, "val")["-v"];
    auto& ref = opt("first description");
    // Should be able to call methods on returned reference
    ref.required();
    EXPECT_FALSE(opt.isOptional());
}

// Test with Arg (another derived class)
TEST_F(ParserRefImplTest_386, ArgIsOptionalByDefault_386) {
    std::string value;
    auto arg = Arg(value, "argHint")("An argument");
    EXPECT_TRUE(arg.isOptional());
}

// Test Arg hint
TEST_F(ParserRefImplTest_386, ArgHintReturnsCorrectValue_386) {
    std::string value;
    auto arg = Arg(value, "argHint")("An argument");
    EXPECT_EQ(std::string(arg.hint()), "argHint");
}

// Test Arg required
TEST_F(ParserRefImplTest_386, ArgRequiredSetsNotOptional_386) {
    std::string value;
    auto arg = Arg(value, "argHint")("An argument");
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}

// Test with int ref
TEST_F(ParserRefImplTest_386, IntRefConstruction_386) {
    int value = 0;
    auto opt = Opt(value, "num")["-n"]["--number"]("A number option");
    EXPECT_EQ(std::string(opt.hint()), "num");
    EXPECT_TRUE(opt.isOptional());
}

// Test operator() with StringRef from std::string
TEST_F(ParserRefImplTest_386, OperatorCallWithStdString_386) {
    bool flag = false;
    std::string desc = "description from string";
    auto opt = Opt(flag)["-f"](Catch::StringRef(desc));
    SUCCEED();
}

// Test optional returns DerivedT& for chaining
TEST_F(ParserRefImplTest_386, OptionalReturnsChainingReference_386) {
    std::string value;
    auto opt = Opt(value, "val")["-v"]("desc");
    auto& ref = opt.optional();
    // Verify the returned reference is the same object
    EXPECT_TRUE(ref.isOptional());
}

// Test required returns DerivedT& for chaining
TEST_F(ParserRefImplTest_386, RequiredReturnsChainingReference_386) {
    std::string value;
    auto opt = Opt(value, "val")["-v"]("desc");
    auto& ref = opt.required();
    EXPECT_FALSE(ref.isOptional());
}
