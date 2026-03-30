// File: parser_base_validate_tests_385.cpp
#include <gtest/gtest.h>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
using Catch::Clara::Detail::ParserBase;
using Catch::Clara::Detail::Result;

// A minimal derived class we can instantiate without touching internals.
// We don't override anything; this is just to ensure we can create an instance
// even if the real base grows more virtuals later.
class StubParser_385 : public ParserBase {};

// A derived class that overrides validate() to return an error Result.
// This tests virtual dispatch + observable error surface only.
class ErrorParser_385 : public ParserBase {
public:
    auto validate() const -> Result override {
        // We rely solely on the public factory on Result.
        return Result::runtimeError(std::string("intentional error 385"));
    }
};
} // namespace

// ---- Tests ----

// [Normal operation] Default validate() should report success.
TEST(ParserBaseValidateTest_385, DefaultValidateReturnsOk_385) {
    StubParser_385 parser;
    auto res = parser.validate();

    // Observable behavior: successful Result converts to true.
    EXPECT_TRUE(static_cast<bool>(res));
}

// [Boundary-ish] validate() can be called repeatedly; observable outcome stays the same.
TEST(ParserBaseValidateTest_385, ValidateIsIdempotentOnSuccess_385) {
    StubParser_385 parser;

    auto first = parser.validate();
    auto second = parser.validate();

    EXPECT_TRUE(static_cast<bool>(first));
    EXPECT_TRUE(static_cast<bool>(second));
}

// [External interaction via virtual dispatch] Overridden validate() is honored polymorphically.
TEST(ParserBaseValidateTest_385, OverriddenValidateIsUsedViaBaseRef_385) {
    ErrorParser_385 derived;
    ParserBase& baseRef = derived;

    auto res = baseRef.validate();

    EXPECT_FALSE(static_cast<bool>(res));  // observable failure
    // If error message is part of the public API (it is in BasicResult-like types),
    // verify it without assuming any internal formatting.
    EXPECT_EQ(res.errorMessage(), "intentional error 385");
}

// [Exceptional/error case] Overridden validate() returns a runtime error result.
TEST(ParserBaseValidateTest_385, OverriddenValidateReturnsRuntimeError_385) {
    ErrorParser_385 parser;
    auto res = parser.validate();

    EXPECT_FALSE(static_cast<bool>(res));
    EXPECT_EQ(res.errorMessage(), "intentional error 385");
}
