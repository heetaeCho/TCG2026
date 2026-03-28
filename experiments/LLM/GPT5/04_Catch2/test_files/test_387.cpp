#include <gtest/gtest.h>
#include <memory>
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// A simple concrete type to use with ParserRefImpl
class DummyParser : public ParserRefImpl<DummyParser> {
public:
    using ParserRefImpl::ParserRefImpl;
};

class ParserRefImplTest_387 : public ::testing::Test {};

// Test that optional() returns a reference to DerivedT
TEST_F(ParserRefImplTest_387, OptionalReturnsSelfReference_387) {
    int value = 0;
    DummyParser parser(value, "hint");

    DummyParser& ref = parser.optional();

    EXPECT_EQ(&ref, &parser);  // Should return same object reference
}

// Test that calling optional() multiple times consistently returns self
TEST_F(ParserRefImplTest_387, OptionalCalledMultipleTimes_387) {
    int value = 0;
    DummyParser parser(value, "hint");

    DummyParser& ref1 = parser.optional();
    DummyParser& ref2 = parser.optional();

    EXPECT_EQ(&ref1, &parser);
    EXPECT_EQ(&ref2, &parser);
    EXPECT_EQ(&ref1, &ref2);
}

// Test interaction: optional() followed by isOptional() should reflect Optional
TEST_F(ParserRefImplTest_387, OptionalSetsIsOptionalTrue_387) {
    int value = 0;
    DummyParser parser(value, "hint");

    parser.optional();

    EXPECT_TRUE(parser.isOptional());
}

// Test boundary: ensure required() overrides optional()
TEST_F(ParserRefImplTest_387, RequiredOverridesOptional_387) {
    int value = 0;
    DummyParser parser(value, "hint");

    parser.optional();
    parser.required();

    EXPECT_FALSE(parser.isOptional());  // Required should negate Optional
}

// Test: optional() does not change hint
TEST_F(ParserRefImplTest_387, OptionalDoesNotAffectHint_387) {
    int value = 0;
    DummyParser parser(value, "expected_hint");

    parser.optional();

    EXPECT_EQ(parser.hint(), "expected_hint");
}
