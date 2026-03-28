#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

// We need to use the actual Clara types from Catch2
// ParserRefImpl is a CRTP base; Arg and Opt derive from it.
// We'll test through the concrete derived classes.

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// ============================================================
// Test fixture
// ============================================================
class ParserRefImplTest_391 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ------------------------------------------------------------
// Tests using Arg (which derives from ParserRefImpl<Arg>)
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, HintReturnsProvidedHint_391) {
    std::string value;
    Arg arg(value, "my_hint");
    EXPECT_EQ(std::string(arg.hint()), "my_hint");
}

TEST_F(ParserRefImplTest_391, HintReturnsEmptyWhenEmptyHint_391) {
    std::string value;
    Arg arg(value, "");
    EXPECT_EQ(std::string(arg.hint()), "");
}

TEST_F(ParserRefImplTest_391, IsOptionalByDefault_391) {
    std::string value;
    Arg arg(value, "hint");
    EXPECT_TRUE(arg.isOptional());
}

TEST_F(ParserRefImplTest_391, RequiredMakesNotOptional_391) {
    std::string value;
    Arg arg = Arg(value, "hint").required();
    EXPECT_FALSE(arg.isOptional());
}

TEST_F(ParserRefImplTest_391, OptionalMakesOptional_391) {
    std::string value;
    Arg arg = Arg(value, "hint").required();
    EXPECT_FALSE(arg.isOptional());
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}

TEST_F(ParserRefImplTest_391, CardinalityReturnsOne_391) {
    std::string value;
    Arg arg(value, "hint");
    EXPECT_EQ(arg.cardinality(), 1u);
}

TEST_F(ParserRefImplTest_391, DescriptionOperatorReturnsRef_391) {
    std::string value;
    Arg arg(value, "hint");
    auto& ref = arg("some description");
    // Should return reference to itself (same address)
    EXPECT_EQ(&ref, &arg);
}

// ------------------------------------------------------------
// Tests using Opt (which also derives from ParserRefImpl<Opt>)
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, OptHintReturnsProvidedHint_391) {
    std::string value;
    Opt opt(value, "opt_hint");
    EXPECT_EQ(std::string(opt.hint()), "opt_hint");
}

TEST_F(ParserRefImplTest_391, OptIsOptionalByDefault_391) {
    std::string value;
    Opt opt(value, "hint");
    EXPECT_TRUE(opt.isOptional());
}

TEST_F(ParserRefImplTest_391, OptRequiredThenOptional_391) {
    std::string value;
    Opt opt(value, "hint");
    opt.required();
    EXPECT_FALSE(opt.isOptional());
    opt.optional();
    EXPECT_TRUE(opt.isOptional());
}

TEST_F(ParserRefImplTest_391, OptCardinalityIsOne_391) {
    std::string value;
    Opt opt(value, "hint");
    EXPECT_EQ(opt.cardinality(), 1u);
}

// ------------------------------------------------------------
// Tests with lambda-based construction
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, LambdaArgHint_391) {
    Arg arg([](std::string const&) {}, "lambda_hint");
    EXPECT_EQ(std::string(arg.hint()), "lambda_hint");
}

TEST_F(ParserRefImplTest_391, LambdaOptHint_391) {
    Opt opt([](std::string const&) {}, "lambda_opt_hint");
    EXPECT_EQ(std::string(opt.hint()), "lambda_opt_hint");
}

TEST_F(ParserRefImplTest_391, LambdaArgIsOptionalByDefault_391) {
    Arg arg([](std::string const&) {}, "hint");
    EXPECT_TRUE(arg.isOptional());
}

// ------------------------------------------------------------
// Tests with accept_many_t (vector binding)
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, AcceptManyArgHint_391) {
    std::vector<std::string> values;
    Arg arg(accept_many, [&values](std::string const& v) { values.push_back(v); }, "many_hint");
    EXPECT_EQ(std::string(arg.hint()), "many_hint");
}

TEST_F(ParserRefImplTest_391, AcceptManyArgCardinality_391) {
    std::vector<std::string> values;
    Arg arg(accept_many, [&values](std::string const& v) { values.push_back(v); }, "many_hint");
    // accept_many should indicate cardinality of 0 (unbounded) typically
    // We just check it returns a value; the exact value depends on implementation
    size_t c = arg.cardinality();
    // For accept_many, cardinality is expected to be 0 (meaning unbounded)
    EXPECT_EQ(c, 0u);
}

// ------------------------------------------------------------
// Tests with integer ref
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, IntRefArgHint_391) {
    int value = 0;
    Arg arg(value, "int_hint");
    EXPECT_EQ(std::string(arg.hint()), "int_hint");
    EXPECT_EQ(arg.cardinality(), 1u);
}

// ------------------------------------------------------------
// Boundary: very long hint
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, VeryLongHint_391) {
    std::string value;
    std::string longHint(1000, 'x');
    Arg arg(value, StringRef(longHint));
    EXPECT_EQ(std::string(arg.hint()), longHint);
}

// ------------------------------------------------------------
// Required then required is idempotent
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, RequiredIdempotent_391) {
    std::string value;
    Arg arg(value, "hint");
    arg.required();
    arg.required();
    EXPECT_FALSE(arg.isOptional());
}

// ------------------------------------------------------------
// Optional then optional is idempotent
// ------------------------------------------------------------

TEST_F(ParserRefImplTest_391, OptionalIdempotent_391) {
    std::string value;
    Arg arg(value, "hint");
    arg.optional();
    arg.optional();
    EXPECT_TRUE(arg.isOptional());
}
